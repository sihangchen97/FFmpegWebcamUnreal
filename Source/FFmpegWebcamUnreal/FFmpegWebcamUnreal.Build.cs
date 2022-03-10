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
			string LibraryPath = Path.Combine(ThirdPartyPath, "ffmpeg-4.4.1", "lib","Win64");

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
			string LibraryPath = Path.Combine(ThirdPartyPath, "ffmpeg-4.4.1", "lib","Mac");
			
			string[] dylibs =
			{
				"libavcodec.dylib", "libavdevice.dylib", "libavfilter.dylib","libavformat.dylib", "libavresample.dylib",
				"libavutil.dylib", "libpostproc.dylib", "libswresample.dylib", "libswscale.dylib"
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
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
				Path.Combine(ThirdPartyPath, "ffmpeg-4.4.1", "include"),
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
				Path.Combine(ThirdPartyPath, "ffmpeg-4.4.1", "include"),
			}
			);
			
		
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
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
		
		LoadffmpegLib(Target);
	}
}
