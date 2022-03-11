// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavdevice/avdevice.h>
#include <libavutil/imgutils.h>
};

#include "FFmpegWebcamManager.generated.h"

UENUM()
enum EFFMPEG_Platform
{
	FFMPEG_WINDOWS     UMETA(DisplayName = "Windows"),
	FFMPEG_MAC   UMETA(DisplayName = "Mac"),
};

/**
 * 
 */
UCLASS(Blueprintable)
class FFMPEGWEBCAMUNREAL_API UFFmpegWebcamManager : public UDataAsset
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category="FFmpeg Webcam", meta=(ExpandBoolAsExecs = status))
	void OpenCamera(bool &status);

	UFUNCTION(BlueprintCallable, Category="FFmpeg Webcam")
	void CloseCamera();

	UFUNCTION(BlueprintCallable, Category="FFmpeg Webcam", meta=(ExpandBoolAsExecs = status))
	void ReadFrame(bool &status);

	UFUNCTION(BlueprintCallable, Category="FFmpeg Webcam")
	void DrawToCanvas(UCanvas* canvas);

	UPROPERTY(EditAnywhere)
	TEnumAsByte<EFFMPEG_Platform> platform;
	
	UPROPERTY(EditAnywhere, meta=(EditCondition="platform==EFFMPEG_Platform::FFMPEG_WINDOWS", EditConditionHides))
	FString cameraName;

	UPROPERTY(EditAnywhere, meta=(EditCondition="platform==EFFMPEG_Platform::FFMPEG_MAC", EditConditionHides))
	FString cameraIndex;

	UPROPERTY(EditAnywhere)
	FIntPoint videoSize;
	
	UPROPERTY(EditAnywhere)
	float frameRate;
	
	UPROPERTY(EditAnywhere)
	FString pixelFormat;
	
	int bufSize_bgra;
	uint8_t* buffer_bgra;

private:
	AVFormatContext* pFormatContext;
	AVStream* videoStream;
	AVCodec* pCodec;
	AVCodecContext* pCodecContext;
	AVPacket* packet;
	AVFrame* frame;
	
	
	AVFrame* frame_bgra;
	SwsContext* swsContext_bgra;

	bool isOpen=false;
};
