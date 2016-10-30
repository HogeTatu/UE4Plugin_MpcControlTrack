// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "IMovieSceneTrackInstance.h"


class FTrackInstancePropertyBindings;
class UMovieSceneMpcColorTrack;


/**
 * Instance of a UMovieSceneMpcColorTrack
 */
class FMovieSceneMpcColorTrackInstance
	: public IMovieSceneTrackInstance
{
public:
	FMovieSceneMpcColorTrackInstance( UMovieSceneMpcColorTrack& InColorTrack );

	/** IMovieSceneTrackInstance interface */
	virtual void SaveState (const TArray<TWeakObjectPtr<UObject>>& RuntimeObjects, IMovieScenePlayer& Player, FMovieSceneSequenceInstance& SequenceInstance) override;
	virtual void RestoreState (const TArray<TWeakObjectPtr<UObject>>& RuntimeObjects, IMovieScenePlayer& Player, FMovieSceneSequenceInstance& SequenceInstance) override;
	virtual void Update(EMovieSceneUpdateData& UpdateData, const TArray<TWeakObjectPtr<UObject>>& RuntimeObjects, IMovieScenePlayer& Player, FMovieSceneSequenceInstance& SequenceInstance) override;
	virtual void RefreshInstance( const TArray<TWeakObjectPtr<UObject>>& RuntimeObjects, IMovieScenePlayer& Player, FMovieSceneSequenceInstance& SequenceInstance ) override;
	virtual void ClearInstance( IMovieScenePlayer& Player, FMovieSceneSequenceInstance& SequenceInstance ) override {}

private:
	void TrySetMpcVectorValue(UObject* Object, const FLinearColor& ColorValue);

private:
	enum class EColorType : uint8
	{
		/** FSlateColor */
		Slate,
		/** FLinearColor */
		Linear,
		/** FColor */
		Color,
	};

	/** The track being instanced */
	UMovieSceneMpcColorTrack* ColorTrack;

	/** Runtime property bindings */
	TSharedPtr<FTrackInstancePropertyBindings> PropertyBindings;

	/** Map from object to initial state */
	/** @todo Sequencer: This may be editor only data */
	TMap< TWeakObjectPtr<UObject>, FSlateColor > InitSlateColorMap;
	TMap< TWeakObjectPtr<UObject>, FLinearColor > InitLinearColorMap;

	/** The type of color primitive being animated */
	EColorType ColorType;
};
