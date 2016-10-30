// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "MpcControlTrackEditorPrivatePCH.h"
#include "MpcFloatPropertyTrackEditor.h"
#include "MpcFloatPropertySection.h"
#include "MatineeImportTools.h"
#include "Matinee/InterpTrackFloatBase.h"


TSharedRef<ISequencerTrackEditor> FMpcFloatPropertyTrackEditor::CreateTrackEditor( TSharedRef<ISequencer> OwningSequencer )
{
	return MakeShareable(new FMpcFloatPropertyTrackEditor(OwningSequencer));
}


TSharedRef<FPropertySection> FMpcFloatPropertyTrackEditor::MakePropertySectionInterface( UMovieSceneSection& SectionObject, UMovieSceneTrack& Track )
{
	return MakeShareable(new FMpcFloatPropertySection(SectionObject, Track.GetDisplayName()));
}


void FMpcFloatPropertyTrackEditor::GenerateKeysFromPropertyChanged( const FPropertyChangedParams& PropertyChangedParams, TArray<float>& NewGeneratedKeys, TArray<float>& DefaultGeneratedKeys )
{
	NewGeneratedKeys.Add( PropertyChangedParams.GetPropertyValue<float>() );
}

void FMpcFloatPropertyTrackEditor::BuildTrackContextMenu( FMenuBuilder& MenuBuilder, UMovieSceneTrack* Track )
{
	UInterpTrackFloatBase* MatineeFloatTrack = nullptr;
	for ( UObject* CopyPasteObject : GUnrealEd->MatineeCopyPasteBuffer )
	{
		MatineeFloatTrack = Cast<UInterpTrackFloatBase>( CopyPasteObject );
		if ( MatineeFloatTrack != nullptr )
		{
			break;
		}
	}
}

void FMpcFloatPropertyTrackEditor::InitializeNewTrack( UMovieSceneMpcFloatTrack* NewTrack, FPropertyChangedParams PropertyChangedParams )
{
	NewTrack->SetPropertyNameAndPath( PropertyChangedParams.PropertyPath.Last()->GetFName(), PropertyChangedParams.GetPropertyPathString() );
#if WITH_EDITORONLY_DATA
	NewTrack->SetDisplayName(FText::FromString(PropertyChangedParams.PropertyPath.Last()->GetDisplayNameText().ToString() + FString(" (MPC)")));
#endif
}
