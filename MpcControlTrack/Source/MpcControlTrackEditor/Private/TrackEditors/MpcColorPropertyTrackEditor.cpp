// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "MpcControlTrackEditorPrivatePCH.h"
#include "MovieSceneMpcColorTrack.h"
#include "MpcColorPropertyTrackEditor.h"
#include "MpcColorPropertySection.h"
#include "MatineeImportTools.h"
#include "Matinee/InterpTrackLinearColorProp.h"
#include "Matinee/InterpTrackColorProp.h"


FName FMpcColorPropertyTrackEditor::RedName( "R" );
FName FMpcColorPropertyTrackEditor::GreenName( "G" );
FName FMpcColorPropertyTrackEditor::BlueName( "B" );
FName FMpcColorPropertyTrackEditor::AlphaName( "A" );


TSharedRef<ISequencerTrackEditor> FMpcColorPropertyTrackEditor::CreateTrackEditor(TSharedRef<ISequencer> InSequencer)
{
	return MakeShareable(new FMpcColorPropertyTrackEditor(InSequencer));
}


TSharedRef<FPropertySection> FMpcColorPropertyTrackEditor::MakePropertySectionInterface( UMovieSceneSection& SectionObject, UMovieSceneTrack& Track )
{
	return MakeShareable(new FMpcColorPropertySection(SectionObject, GetSequencer().Get(), Track));
}


void FMpcColorPropertyTrackEditor::GenerateKeysFromPropertyChanged( const FPropertyChangedParams& PropertyChangedParams, TArray<FColorKey>& NewGeneratedKeys, TArray<FColorKey>& DefaultGeneratedKeys )
{
	const UStructProperty* StructProp = Cast<const UStructProperty>( PropertyChangedParams.PropertyPath.Last() );
	FName StructName = StructProp->Struct->GetFName();
	FName PropertyName = PropertyChangedParams.PropertyPath.Last()->GetFName();

	bool bIsFColor = StructName == NAME_Color;
	bool bIsFLinearColor = StructName == NAME_LinearColor;
	bool bIsSlateColor = StructName == FName( "SlateColor" );

	FLinearColor ColorValue;

	if (bIsFColor)
	{
		ColorValue = FLinearColor( PropertyChangedParams.GetPropertyValue<FColor>() );
	}
	else
	{
		ColorValue = PropertyChangedParams.GetPropertyValue<FLinearColor>();
	}

	if( StructProp->HasMetaData("HideAlphaChannel") )
	{
		ColorValue.A = 1;
	}

	FName ChannelName = PropertyChangedParams.StructPropertyNameToKey;

	TArray<FColorKey>& RedKeys = ChannelName == NAME_None || ChannelName == RedName ? NewGeneratedKeys : DefaultGeneratedKeys;
	RedKeys.Add( FColorKey( EKeyColorChannel::Red, ColorValue.R, bIsSlateColor ) );

	TArray<FColorKey>& GreenKeys = ChannelName == NAME_None || ChannelName == GreenName ? NewGeneratedKeys : DefaultGeneratedKeys;
	GreenKeys.Add( FColorKey( EKeyColorChannel::Green, ColorValue.G, bIsSlateColor ) );

	TArray<FColorKey>& BlueKeys =  ChannelName == NAME_None || ChannelName == BlueName ? NewGeneratedKeys : DefaultGeneratedKeys;
	BlueKeys.Add( FColorKey( EKeyColorChannel::Blue, ColorValue.B, bIsSlateColor ) );

	TArray<FColorKey>& AlphaKeys = ChannelName == NAME_None || ChannelName == AlphaName ? NewGeneratedKeys : DefaultGeneratedKeys;
	AlphaKeys.Add( FColorKey( EKeyColorChannel::Alpha, ColorValue.A, bIsSlateColor ) );
}

void FMpcColorPropertyTrackEditor::BuildTrackContextMenu( FMenuBuilder& MenuBuilder, UMovieSceneTrack* Track )
{
	UInterpTrackColorProp* ColorPropTrack = nullptr;
	UInterpTrackLinearColorProp* LinearColorPropTrack = nullptr;
	for ( UObject* CopyPasteObject : GUnrealEd->MatineeCopyPasteBuffer )
	{
		ColorPropTrack = Cast<UInterpTrackColorProp>( CopyPasteObject );
		LinearColorPropTrack = Cast<UInterpTrackLinearColorProp>( CopyPasteObject );
		if ( ColorPropTrack != nullptr || LinearColorPropTrack != nullptr )
		{
			break;
		}
	}
}

void FMpcColorPropertyTrackEditor::InitializeNewTrack( UMovieSceneMpcColorTrack* NewTrack, FPropertyChangedParams PropertyChangedParams )
{
	NewTrack->SetPropertyNameAndPath( PropertyChangedParams.PropertyPath.Last()->GetFName(), PropertyChangedParams.GetPropertyPathString() );
#if WITH_EDITORONLY_DATA
	NewTrack->SetDisplayName(FText::FromString(PropertyChangedParams.PropertyPath.Last()->GetDisplayNameText().ToString() + FString(" (MPC)")));
#endif
}

