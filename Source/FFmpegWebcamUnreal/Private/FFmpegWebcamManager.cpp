// Fill out your copyright notice in the Description page of Project Settings.

#include "FFmpegWebcamManager.h"
#include "Engine/Canvas.h"

void UFFmpegWebcamManager::OpenCamera(bool &status)
{
	status = false;

	avdevice_register_all();
	pFormatContext = avformat_alloc_context();
	AVInputFormat *ifmt=NULL;
#if PLATFORM_WINDOWS
	ifmt = av_find_input_format("dshow");
#elif PLATFORM_MAC
	ifmt = av_find_input_format("avfoundation");
#endif
	if(ifmt == NULL){
		UE_LOG(LogTemp, Warning, TEXT("Input Format Error"));
		return;
	}
	
	AVDictionary* options = NULL;
	av_dict_set(&options, "video_size", TCHAR_TO_ANSI(*(FString::FromInt(videoSize.X)+"x"+FString::FromInt(videoSize.Y))), 0);
	av_dict_set(&options, "framerate", TCHAR_TO_ANSI(*(FString::FromInt(frameRate))), 0);

	if(useVcodec)
		av_dict_set(&options, "vcodec", TCHAR_TO_ANSI(*vcodec), 0);
	else
		av_dict_set(&options, "pixel_format", TCHAR_TO_ANSI(*pixelFormat), 0);
	

#if PLATFORM_WINDOWS
	if(avformat_open_input(&pFormatContext, TCHAR_TO_ANSI(*(FString("video=")+cameraName)), ifmt, &options) !=0)
#elif PLATFORM_MAC
	if(avformat_open_input(&pFormatContext, TCHAR_TO_ANSI(*cameraIndex), ifmt, &options) !=0)
#endif
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to Open Camera"));
		return;
	}
	
	if(avformat_find_stream_info(pFormatContext, NULL)<0){
		UE_LOG(LogTemp, Warning, TEXT("Cannot find any stream"));
		return;
	}
	
	videoStream = NULL;
	UE_LOG(LogTemp, Warning, TEXT("Find %d Stream"),pFormatContext->nb_streams);
	
	for(uint8 i=0;i < pFormatContext->nb_streams;i++){
		if(pFormatContext->streams[i]->codecpar->codec_type==AVMEDIA_TYPE_VIDEO){
			videoStream = pFormatContext->streams[i];
			break;
		}
	}
	
	if(videoStream == NULL){
		UE_LOG(LogTemp, Warning, TEXT("Cannot find any video stream"));
		return;
	}
	
	pCodec = avcodec_find_decoder(videoStream->codecpar->codec_id);
	if(pCodec==NULL){
		UE_LOG(LogTemp, Warning, TEXT("Cannot Find Any Decoder"));
		return;
	}

	pCodecContext = avcodec_alloc_context3(pCodec);
	avcodec_parameters_to_context(pCodecContext, videoStream->codecpar);

	if(avcodec_open2(pCodecContext, pCodec, NULL)!=0){
		UE_LOG(LogTemp, Warning, TEXT("Cannot Open Decoder"));
		return;
	}

	videoSize.X = pCodecContext->width;
	videoSize.Y = pCodecContext->height;
	
	packet = av_packet_alloc();
	frame = av_frame_alloc();
	frame_bgra = av_frame_alloc();
	
	bufSize_bgra = av_image_get_buffer_size(AV_PIX_FMT_BGRA, videoSize.X, videoSize.Y, 1);
	buffer_bgra = (uint8_t*)av_malloc(bufSize_bgra);
	av_image_fill_arrays(frame_bgra->data, frame_bgra->linesize, buffer_bgra, AV_PIX_FMT_BGRA, videoSize.X, videoSize.Y, 1);
	frame_bgra->format = AV_PIX_FMT_BGRA;

	swsContext_bgra = sws_getContext(videoSize.X, videoSize.Y, pCodecContext->pix_fmt,
									   videoSize.X, videoSize.Y, AV_PIX_FMT_BGRA, SWS_BICUBIC, NULL, NULL, NULL);

	if(swsContext_bgra==NULL){
		UE_LOG(LogTemp, Warning, TEXT("Cannot Get swsContent_brga"));
		return;
	}
	status = true;
	isOpen = true;
}

void UFFmpegWebcamManager::CloseCamera()
{
	avcodec_close(pCodecContext);
	avformat_close_input(&pFormatContext);
}


void UFFmpegWebcamManager::ReadFrame(bool &status)
{
	status = false;
	if(!isOpen)return;
	
	av_packet_unref(packet);
	if(av_read_frame(pFormatContext, packet)<0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot Read Frame"));
		return;
	}
	int ret = avcodec_send_packet(pCodecContext, packet);
	if(ret!=0){
		UE_LOG(LogTemp, Warning, TEXT("Cannot Decode Packet"));
		return;
	}
	if(avcodec_receive_frame(pCodecContext, frame)>=0){
		sws_scale(swsContext_bgra, (const uint8_t* const*)frame->data , frame->linesize, 0, videoSize.Y, frame_bgra->data, frame_bgra->linesize);
		status = true;
	}
}

void UFFmpegWebcamManager::DrawToCanvas(UCanvas* canvas)
{
	UTexture2D* Pointer = UTexture2D::CreateTransient(videoSize.X, videoSize.Y, PF_B8G8R8A8);
	uint8* MipData = static_cast<uint8*>(Pointer->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE));
	FMemory::Memcpy(MipData, buffer_bgra, videoSize.X * videoSize.Y * 4);
	Pointer->PlatformData->Mips[0].BulkData.Unlock();
	Pointer->UpdateResource();
	canvas->K2_DrawTexture(Pointer,FVector2D(0,0),FVector2D(canvas->SizeX,canvas->SizeY),FVector2D(0,0));
	Pointer->MarkPendingKill();
}
