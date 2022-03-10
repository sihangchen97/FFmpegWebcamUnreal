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
		if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
		{
			isLibararySupported = true;
			string LibraryPath = Path.Combine(ThirdPartyPath, "ffmpeg-4.4.1", "lib","Win64");
			PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, "avcodec.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, "avdevice.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, "avfilter.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, "avformat.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, "avutil.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, "postproc.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, "swresample.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, "swscale.lib"));
			
			PublicDelayLoadDLLs.Add( "avcodec-58.dll");
			PublicDelayLoadDLLs.Add( "avdevice-58.dll");
			PublicDelayLoadDLLs.Add( "avfilter-7.dll");
			PublicDelayLoadDLLs.Add( "avformat-58.dll");
			PublicDelayLoadDLLs.Add( "avutil-56.dll");
			PublicDelayLoadDLLs.Add( "postproc-55.dll");
			PublicDelayLoadDLLs.Add( "swresample-3.dll");
			PublicDelayLoadDLLs.Add( "swscale-5.dll");
			
			RuntimeDependencies.Add(new RuntimeDependency(LibraryPath + "avcodec-58.dll"));
			RuntimeDependencies.Add(new RuntimeDependency(LibraryPath + "avdevice-58.dll"));
			RuntimeDependencies.Add(new RuntimeDependency(LibraryPath + "avfilter-7.dll"));
			RuntimeDependencies.Add(new RuntimeDependency(LibraryPath + "avformat-58.dll"));
			RuntimeDependencies.Add(new RuntimeDependency(LibraryPath + "avutil-56.dll"));
			RuntimeDependencies.Add(new RuntimeDependency(LibraryPath + "postproc-55.dll"));
			RuntimeDependencies.Add(new RuntimeDependency(LibraryPath + "swresample-3.dll"));
			RuntimeDependencies.Add(new RuntimeDependency(LibraryPath + "swscale-5.dll"));
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
