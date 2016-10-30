// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MpcControlTrackEditor : ModuleRules
{
	public MpcControlTrackEditor(TargetInfo Target)
	{
		PublicIncludePaths.AddRange(
			new string[] {
				"MpcControlTrack/Public",
				"MpcControlTrack/Public/MovieScene",
			}
		);

		PrivateIncludePaths.AddRange(
			new string[] {
				"MpcControlTrackEditor/Private",
				"MpcControlTrackEditor/Private/TrackEditors",
				"MpcControlTrackEditor/Private/Sections",
				"MpcControlTrack/Private",
				"MpcControlTrack/Private/MovieScene",
				"Editor/MovieSceneTools/Private/TrackEditors",
				"Editor/MovieSceneTools/Private/TrackEditors/PropertyTrackEditors",
				"Editor/MovieSceneTools/Private/Sections",
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
                "EditorStyle",
				"MovieScene",
				"MovieSceneTracks",
				"MovieSceneTools",
				"MpcControlTrack",
				"Sequencer",
				"UnrealEd",
			}
		);
	}
}
