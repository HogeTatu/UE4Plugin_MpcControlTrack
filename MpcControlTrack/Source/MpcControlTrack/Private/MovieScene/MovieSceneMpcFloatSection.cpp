// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "MpcControlTrackPrivatePCH.h"
#include "MovieSceneMpcFloatSection.h"


UMovieSceneMpcFloatSection::UMovieSceneMpcFloatSection( const FObjectInitializer& ObjectInitializer )
	: Super( ObjectInitializer )
{ }


float UMovieSceneMpcFloatSection::Eval( float Position ) const
{
	return FloatCurve.Eval( Position );
}


void UMovieSceneMpcFloatSection::MoveSection( float DeltaPosition, TSet<FKeyHandle>& KeyHandles )
{
	Super::MoveSection( DeltaPosition, KeyHandles );

	// Move the curve
	FloatCurve.ShiftCurve(DeltaPosition, KeyHandles);
}


void UMovieSceneMpcFloatSection::DilateSection( float DilationFactor, float Origin, TSet<FKeyHandle>& KeyHandles )
{
	Super::DilateSection(DilationFactor, Origin, KeyHandles);

	FloatCurve.ScaleCurve(Origin, DilationFactor, KeyHandles);
}


void UMovieSceneMpcFloatSection::GetKeyHandles(TSet<FKeyHandle>& OutKeyHandles, TRange<float> TimeRange) const
{
	if (!TimeRange.Overlaps(GetRange()))
	{
		return;
	}

	for (auto It(FloatCurve.GetKeyHandleIterator()); It; ++It)
	{
		float Time = FloatCurve.GetKeyTime(It.Key());
		if (TimeRange.Contains(Time))
		{
			OutKeyHandles.Add(It.Key());
		}
	}
}


TOptional<float> UMovieSceneMpcFloatSection::GetKeyTime( FKeyHandle KeyHandle ) const
{
	if ( FloatCurve.IsKeyHandleValid( KeyHandle ) )
	{
		return TOptional<float>( FloatCurve.GetKeyTime( KeyHandle ) );
	}
	return TOptional<float>();
}


void UMovieSceneMpcFloatSection::SetKeyTime( FKeyHandle KeyHandle, float Time )
{
	if ( FloatCurve.IsKeyHandleValid( KeyHandle ) )
	{
		FloatCurve.SetKeyTime( KeyHandle, Time );
	}
}


void UMovieSceneMpcFloatSection::AddKey( float Time, const float& Value, EMovieSceneKeyInterpolation KeyInterpolation )
{
	AddKeyToCurve( FloatCurve, Time, Value, KeyInterpolation );
}


bool UMovieSceneMpcFloatSection::NewKeyIsNewData(float Time, const float& Value) const
{
	return FMath::IsNearlyEqual( FloatCurve.Eval( Time ), Value ) == false;
}

bool UMovieSceneMpcFloatSection::HasKeys( const float& Value ) const
{
	return FloatCurve.GetNumKeys() > 0;
}

void UMovieSceneMpcFloatSection::SetDefault( const float& Value )
{
	SetCurveDefault( FloatCurve, Value );
}
