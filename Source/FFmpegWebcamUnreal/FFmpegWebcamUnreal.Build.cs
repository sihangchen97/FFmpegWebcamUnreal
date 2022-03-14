// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class FFmpegWebcamUnreal : ModuleRules
{
	private string ModulePath { get { return ModuleDirectory; } }
	private string ThirdPartyPath { get { return Path.GetFullPath(Path.Combine(ModulePath,"../../ThirdParty/")); } }
	
	public bool LoadffmpegLib(ReadOnlyTargetRules Target)
	{
		bool isLibararySupported = false;
		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			isLibararySupported = true;
			PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "ffmpeg-4.4.1-Win64", "include"));
            PrivateIncludePaths.Add(Path.Combine(ThirdPartyPath, "ffmpeg-4.4.1-Win64", "include"));
            
			string LibraryPath = Path.Combine(ThirdPartyPath, "ffmpeg-4.4.1-Win64", "lib");

			string[] libs =
			{
				"avcodec.lib", "avdevice.lib", "avfilter.lib", "avformat.lib", "avutil.lib", "postproc.lib",
				"swresample.lib", "swscale.lib"
			};

			foreach (string lib in libs)
			{
				PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, lib));
			}

			string[] dlls =
			{
				"avcodec-58.dll", "avdevice-58.dll", "avfilter-7.dll", "avformat-58.dll", "avutil-56.dll",
				"postproc-55.dll", "swresample-3.dll", "swscale-5.dll"
			};

			foreach (string dll in dlls)
			{
				PublicDelayLoadDLLs.Add(dll);
				RuntimeDependencies.Add(Path.Combine(LibraryPath, dll), StagedFileType.NonUFS);
			}
		}

		if (Target.Platform == UnrealTargetPlatform.Mac)
		{
			isLibararySupported = true;
			PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "ffmpeg-4.4.1-Mac", "include"));
			PrivateIncludePaths.Add(Path.Combine(ThirdPartyPath, "ffmpeg-4.4.1-Mac", "include"));
			
			string LibraryPath = Path.Combine(ThirdPartyPath, "ffmpeg-4.4.1-Mac", "lib");
			
			string[] dylibs =
			{
				"libavcodec.58.134.100.dylib", "libavdevice.58.13.100.dylib", "libavfilter.7.110.100.dylib","libavformat.58.76.100.dylib", "libavresample.4.0.0.dylib",
				"libavutil.56.70.100.dylib", "libpostproc.55.9.100.dylib", "libswresample.3.9.100.dylib", "libswscale.5.9.100.dylib"
			} ;

			foreach (string dylib in dylibs)
			{
				PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, dylib));
				RuntimeDependencies.Add(Path.Combine(LibraryPath, dylib), StagedFileType.NonUFS);
			}
		}
		return isLibararySupported;
	}
	
	public FFmpegWebcamUnreal(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
			
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);	
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		LoadffmpegLib(Target);
	}
}
