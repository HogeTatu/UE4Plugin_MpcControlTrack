// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MpcControlTrack : ModuleRules
{
	public MpcControlTrack(TargetInfo Target)
	{
		PublicIncludePaths.AddRange(
			new string[] {
				"MpcControlTrack/Public",
				"MpcControlTrack/Public/MovieScene",
				"MpcControlTrack/Public/Actor",
			}
		);

		PrivateIncludePaths.AddRange(
			new string[] {
				"MpcControlTrack/Private",
				"MpcControlTrack/Private/MovieScene",
				"MpcControlTrack/Private/Actor",
			}
		);

		PublicDependencyModuleNames.AddRange(
			new string[] {
				"Core",
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[] {
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"MovieScene",
				"MovieSceneTracks",
			}
		);
	}
}
