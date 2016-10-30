// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "MpcControlTrackPrivatePCH.h"
#include "MovieSceneMpcColorSection.h"
#include "MovieSceneMpcColorTrack.h"
#include "IMovieScenePlayer.h"
#include "MovieSceneMpcColorTrackInstance.h"


UMovieSceneMpcColorTrack::UMovieSceneMpcColorTrack( const FObjectInitializer& ObjectInitializer )
	: Super( ObjectInitializer )
{ }


UMovieSceneSection* UMovieSceneMpcColorTrack::CreateNewSection()
{
	return NewObject<UMovieSceneSection>(this, UMovieSceneMpcColorSection::StaticClass(), NAME_None, RF_Transactional);
}


TSharedPtr<IMovieSceneTrackInstance> UMovieSceneMpcColorTrack::CreateInstance()
{
	return MakeShareable( new FMovieSceneMpcColorTrackInstance( *this ) );
}


bool UMovieSceneMpcColorTrack::Eval( float Position, float LastPosition, FLinearColor& OutColor ) const
{
	const UMovieSceneSection* Section = MovieSceneHelpers::FindNearestSectionAtTime( Sections, Position );

	if( Section )
	{
		if (!Section->IsInfinite())
		{
			Position = FMath::Clamp(Position, Section->GetStartTime(), Section->GetEndTime());
		}

		OutColor = CastChecked<UMovieSceneMpcColorSection>( Section )->Eval( Position, OutColor );
	}

	return Section != nullptr;
}

