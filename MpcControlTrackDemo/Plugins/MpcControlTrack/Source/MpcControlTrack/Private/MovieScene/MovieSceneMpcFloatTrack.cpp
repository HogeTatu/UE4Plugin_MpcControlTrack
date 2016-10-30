// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "MpcControlTrackPrivatePCH.h"
#include "MovieSceneMpcFloatSection.h"
#include "MovieSceneMpcFloatTrack.h"
#include "IMovieScenePlayer.h"
#include "MovieSceneMpcFloatTrackInstance.h"


UMovieSceneMpcFloatTrack::UMovieSceneMpcFloatTrack( const FObjectInitializer& ObjectInitializer )
	: Super( ObjectInitializer )
{ }


UMovieSceneSection* UMovieSceneMpcFloatTrack::CreateNewSection()
{
	return NewObject<UMovieSceneSection>(this, UMovieSceneMpcFloatSection::StaticClass(), NAME_None, RF_Transactional);
}


TSharedPtr<IMovieSceneTrackInstance> UMovieSceneMpcFloatTrack::CreateInstance()
{
	return MakeShareable( new FMovieSceneMpcFloatTrackInstance( *this ) );
}


bool UMovieSceneMpcFloatTrack::Eval( float Position, float LastPosition, float& OutFloat ) const
{
	const UMovieSceneSection* Section = MovieSceneHelpers::FindNearestSectionAtTime( Sections, Position );

	if( Section )
	{
		if (!Section->IsInfinite())
		{
			Position = FMath::Clamp(Position, Section->GetStartTime(), Section->GetEndTime());
		}

		OutFloat = CastChecked<UMovieSceneMpcFloatSection>( Section )->Eval( Position );
	}

	return Section != nullptr;
}

