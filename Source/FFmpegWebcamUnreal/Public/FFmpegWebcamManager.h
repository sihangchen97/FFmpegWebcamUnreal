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

UCLASS()
class FFMPEGWEBCAMUNREAL_API AFFmpegWebcamManagerDaemon : public AActor
{
	GENERATED_BODY()
protected:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
public:
	AVFormatContext* pFormatContext;
	AVCodecContext* pCodecContext;
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

	static void GetCameraList(TArray<FString> &list);

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	
	UPROPERTY(EditDefaultsOnly, Category="Webcam Info")
	bool updateCamera;
	
	UPROPERTY(VisibleAnywhere, Category="Webcam Info",Meta=(ShowOnlyInnerProperties)) 
	TArray<FString> cameraList;
	
	UPROPERTY(EditAnywhere, Category="Webcam Config", meta=(ArrayClamp=cameraList))
	int32 cameraIndex = -1;
	
	UPROPERTY(VisibleAnywhere, Category="Webcam Config", meta=(ArrayClamp=cameraList))
	FString cameraName = "--No Webcam--";

	UPROPERTY(EditAnywhere, Category="Webcam Config", BlueprintReadOnly)
	FIntPoint videoSize;
	
	UPROPERTY(EditAnywhere, Category="Webcam Config")
	float frameRate;
	
	UPROPERTY(EditAnywhere, Category="Webcam Config")
	bool useVcodec;
	
	UPROPERTY(EditAnywhere, Category="Webcam Config", meta=(EditCondition="!useVcodec", EditConditionHides))
	FString pixelFormat;
	
	UPROPERTY(EditAnywhere, Category="Webcam Config", meta=(EditCondition="useVcodec", EditConditionHides))
	FString vcodec;

	UPROPERTY(BlueprintReadOnly, Category="Image Buffer")
	TArray<int32> imageBufferBRGA;

private:
	AVFormatContext* pFormatContext;
	AVStream* videoStream;
	AVCodec* pCodec;
	AVCodecContext* pCodecContext;
	AVPacket* packet;
	AVFrame* frame;
	
	AVFrame* frame_bgra;
	SwsContext* swsContext_bgra;

	AFFmpegWebcamManagerDaemon* daemonActor;

	bool CheckValid();
};
