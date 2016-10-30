// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "MovieSceneMpcFloatTrack.h"
#include "MovieSceneMpcFloatSection.h"
#include "PropertyTrackEditor.h"


class ISequencer;


/**
 * A property track editor for floats.
 */
class FMpcFloatPropertyTrackEditor
	: public FPropertyTrackEditor<UMovieSceneMpcFloatTrack, UMovieSceneMpcFloatSection, float>
{
public:

	/**
	 * Constructor.
	 *
	 * @param InSequencer The sequencer instance to be used by this tool.
	 */
	FMpcFloatPropertyTrackEditor(TSharedRef<ISequencer> InSequencer)
		: FPropertyTrackEditor(InSequencer, NAME_FloatProperty)
	{ }

	/**
	 * Creates an instance of this class (called by a sequencer).
	 *
	 * @param OwningSequencer The sequencer instance to be used by this tool
	 * @return The new instance of this class
	 */
	static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> OwningSequencer);

public:

	//~ FMovieSceneTrackEditor interface

	virtual void BuildTrackContextMenu(FMenuBuilder& MenuBuilder, UMovieSceneTrack* Track) override;

protected:

	//~ FPropertyTrackEditor interface

	virtual TSharedRef<FPropertySection> MakePropertySectionInterface(UMovieSceneSection& SectionObject, UMovieSceneTrack& Track) override;
	virtual void GenerateKeysFromPropertyChanged(const FPropertyChangedParams& PropertyChangedParams, TArray<float>& NewGeneratedKeys, TArray<float>& DefaultGeneratedKeys) override;
	virtual bool ForCustomizedUseOnly() { return true; }
	virtual void InitializeNewTrack( UMovieSceneMpcFloatTrack* NewTrack, FPropertyChangedParams PropertyChangedParams ) override;
};
