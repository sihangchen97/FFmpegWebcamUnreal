// Copyright Epic Games, Inc. All Rights Reserved.

#include "FFmpegWebcamUnreal.h"

#define LOCTEXT_NAMESPACE "FFFmpegWebcamUnrealModule"

void FFFmpegWebcamUnrealModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	av_log_set_callback(&FFMPEG_LogCallback);
}

void FFFmpegWebcamUnrealModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

void FFMPEG_LogCallback(void* ptr, int level, const char* fmt, va_list vl)
{
	if (FFMPEG_IsSaveToArray)
	{
		char buffer[1024];
		vsprintf(buffer, fmt, vl);
		FFMPEG_LogArray.Add(buffer);
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FFFmpegWebcamUnrealModule, FFmpegWebcamUnreal)