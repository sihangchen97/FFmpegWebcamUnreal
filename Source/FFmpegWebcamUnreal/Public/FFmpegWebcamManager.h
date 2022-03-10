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

/**
 * 
 */
UCLASS(Blueprintable)
class FFMPEGWEBCAMUNREAL_API UFFmpegWebcamManager : public UDataAsset
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category="FFmpeg Webcam Testing", meta=(ExpandBoolAsExecs = status))
	void OpenCamera(bool &status);

	UFUNCTION(BlueprintCallable, Category="FFmpeg Webcam Testing")
	void CloseCamera();

	UFUNCTION(BlueprintCallable, Category="FFmpeg Webcam Testing", meta=(ExpandBoolAsExecs = status))
	void ReadFrame(bool &status);

	UFUNCTION(BlueprintCallable, Category="FFmpeg Webcam Testing")
	void DrawToCanvas(UCanvas* canvas);

	UPROPERTY(EditAnywhere)
	FString inputFormat;
	
	UPROPERTY(EditAnywhere)
	FString cameraName;

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
