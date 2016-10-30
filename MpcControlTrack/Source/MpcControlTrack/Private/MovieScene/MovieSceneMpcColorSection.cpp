// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "MpcControlTrackPrivatePCH.h"
#include "MovieSceneMpcColorSection.h"
#include "MovieSceneMpcColorTrack.h"


/* FMovieSceneMpcColorKeyStruct interface
 *****************************************************************************/

void FMovieSceneMpcColorKeyStruct::PropagateChanges(const FPropertyChangedEvent& ChangeEvent)
{
	for (int32 Index = 0; Index <= 3; ++Index)
	{
		if (Keys[Index] == nullptr)
		{
			if (Curves[Index] != nullptr)
			{
				Curves[Index]->SetDefaultValue(Color.Component(Index));
			}
		}
		else
		{
			Keys[Index]->Value = Color.Component(Index);
		}
	}
}


/* UMovieSceneMpcColorSection structors
 *****************************************************************************/

UMovieSceneMpcColorSection::UMovieSceneMpcColorSection(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{ }


/* UMovieSceneMpcColorSection interface
 *****************************************************************************/

FLinearColor UMovieSceneMpcColorSection::Eval(float Position, const FLinearColor& DefaultColor) const
{
	return FLinearColor(
		RedCurve.Eval(Position, DefaultColor.R),
		GreenCurve.Eval(Position, DefaultColor.G),
		BlueCurve.Eval(Position, DefaultColor.B),
		AlphaCurve.Eval(Position, DefaultColor.A));
}


/* UMovieSceneSection interface
 *****************************************************************************/

void UMovieSceneMpcColorSection::MoveSection(float DeltaTime, TSet<FKeyHandle>& KeyHandles)
{
	Super::MoveSection(DeltaTime, KeyHandles);

	// Move all the curves in this section
	RedCurve.ShiftCurve(DeltaTime, KeyHandles);
	GreenCurve.ShiftCurve(DeltaTime, KeyHandles);
	BlueCurve.ShiftCurve(DeltaTime, KeyHandles);
	AlphaCurve.ShiftCurve(DeltaTime, KeyHandles);
}


void UMovieSceneMpcColorSection::DilateSection(float DilationFactor, float Origin, TSet<FKeyHandle>& KeyHandles)
{
	Super::DilateSection(DilationFactor, Origin, KeyHandles);

	RedCurve.ScaleCurve(Origin, DilationFactor, KeyHandles);
	GreenCurve.ScaleCurve(Origin, DilationFactor, KeyHandles);
	BlueCurve.ScaleCurve(Origin, DilationFactor, KeyHandles);
	AlphaCurve.ScaleCurve(Origin, DilationFactor, KeyHandles);
}


void UMovieSceneMpcColorSection::GetKeyHandles(TSet<FKeyHandle>& OutKeyHandles, TRange<float> TimeRange) const
{
	if (!TimeRange.Overlaps(GetRange()))
	{
		return;
	}

	for (auto It(RedCurve.GetKeyHandleIterator()); It; ++It)
	{
		float Time = RedCurve.GetKeyTime(It.Key());
		if (TimeRange.Contains(Time))
		{
			OutKeyHandles.Add(It.Key());
		}
	}

	for (auto It(GreenCurve.GetKeyHandleIterator()); It; ++It)
	{
		float Time = GreenCurve.GetKeyTime(It.Key());
		if (TimeRange.Contains(Time))
		{
			OutKeyHandles.Add(It.Key());
		}
	}

	for (auto It(BlueCurve.GetKeyHandleIterator()); It; ++It)
	{
		float Time = BlueCurve.GetKeyTime(It.Key());
		if (TimeRange.Contains(Time))
		{
			OutKeyHandles.Add(It.Key());
		}
	}

	for (auto It(AlphaCurve.GetKeyHandleIterator()); It; ++It)
	{
		float Time = AlphaCurve.GetKeyTime(It.Key());
		if (TimeRange.Contains(Time))
		{
			OutKeyHandles.Add(It.Key());
		}
	}
}


TSharedPtr<FStructOnScope> UMovieSceneMpcColorSection::GetKeyStruct(const TArray<FKeyHandle>& KeyHandles)
{
	TSharedRef<FStructOnScope> KeyStruct = MakeShareable(new FStructOnScope(FMovieSceneMpcColorKeyStruct::StaticStruct()));
	auto Struct = (FMovieSceneMpcColorKeyStruct*)KeyStruct->GetStructMemory();
	{
		Struct->Curves[0] = &RedCurve;
		Struct->Curves[1] = &GreenCurve;
		Struct->Curves[2] = &BlueCurve;
		Struct->Curves[3] = &AlphaCurve;

		Struct->Keys[0] = RedCurve.GetFirstMatchingKey(KeyHandles);
		Struct->Keys[1] = GreenCurve.GetFirstMatchingKey(KeyHandles);
		Struct->Keys[2] = BlueCurve.GetFirstMatchingKey(KeyHandles);
		Struct->Keys[3] = AlphaCurve.GetFirstMatchingKey(KeyHandles);

		float FirstValidKeyTime = 0.f;
		for (int32 Index = 0; Index <= 3; ++Index)
		{
			if (Struct->Keys[Index] != nullptr)
			{
				FirstValidKeyTime = Struct->Keys[Index]->Time;
			}
		}

		for (int32 Index = 0; Index <= 3; ++Index)
		{
			if (Struct->Keys[Index] == nullptr && Struct->Curves[Index] != nullptr)
			{
				Struct->Color.Component(Index) = Struct->Curves[Index]->Eval(FirstValidKeyTime);
			}
			else
			{
				Struct->Color.Component(Index) = Struct->Keys[Index]->Value;
			}
		}
	}

	return KeyStruct;
}


TOptional<float> UMovieSceneMpcColorSection::GetKeyTime( FKeyHandle KeyHandle ) const
{
	if ( RedCurve.IsKeyHandleValid( KeyHandle ) )
	{
		return TOptional<float>( RedCurve.GetKeyTime( KeyHandle ) );
	}
	if ( GreenCurve.IsKeyHandleValid( KeyHandle ) )
	{
		return TOptional<float>( GreenCurve.GetKeyTime( KeyHandle ) );
	}
	if ( BlueCurve.IsKeyHandleValid( KeyHandle ) )
	{
		return TOptional<float>( BlueCurve.GetKeyTime( KeyHandle ) );
	}
	if ( AlphaCurve.IsKeyHandleValid( KeyHandle ) )
	{
		return TOptional<float>( AlphaCurve.GetKeyTime( KeyHandle ) );
	}
	return TOptional<float>();
}


void UMovieSceneMpcColorSection::SetKeyTime( FKeyHandle KeyHandle, float Time )
{
	if ( RedCurve.IsKeyHandleValid( KeyHandle ) )
	{
		RedCurve.SetKeyTime( KeyHandle, Time );
	}
	else if ( GreenCurve.IsKeyHandleValid( KeyHandle ) )
	{
		GreenCurve.SetKeyTime( KeyHandle, Time );
	}
	else if ( BlueCurve.IsKeyHandleValid( KeyHandle ) )
	{
		BlueCurve.SetKeyTime( KeyHandle, Time );
	}
	else if ( AlphaCurve.IsKeyHandleValid( KeyHandle ) )
	{
		AlphaCurve.SetKeyTime( KeyHandle, Time );
	}
}


/* IKeyframeSection interface
 *****************************************************************************/

template<typename CurveType>
CurveType* GetCurveForChannel(EKeyColorChannel Channel, CurveType* RedCurve, CurveType* GreenCurve, CurveType* BlueCurve, CurveType* AlphaCurve)
{
	switch (Channel)
	{
	case EKeyColorChannel::Red:
		return RedCurve;
	case EKeyColorChannel::Green:
		return GreenCurve;
	case EKeyColorChannel::Blue:
		return BlueCurve;
	case EKeyColorChannel::Alpha:
		return AlphaCurve;
	default:
		checkf(false, TEXT("Invalid key color channel"));
		return nullptr;
	}
}


void UMovieSceneMpcColorSection::AddKey(float Time, const FColorKey& Key, EMovieSceneKeyInterpolation KeyInterpolation)
{
	FRichCurve* ChannelCurve = GetCurveForChannel(Key.Channel, &RedCurve, &GreenCurve, &BlueCurve, &AlphaCurve);
	AddKeyToCurve(*ChannelCurve, Time, Key.ChannelValue, KeyInterpolation);
}


bool UMovieSceneMpcColorSection::NewKeyIsNewData(float Time, const FColorKey& Key) const
{
	const FRichCurve* ChannelCurve = GetCurveForChannel(Key.Channel, &RedCurve, &GreenCurve, &BlueCurve, &AlphaCurve);
	return FMath::IsNearlyEqual(ChannelCurve->Eval(Time), Key.ChannelValue) == false;
}


bool UMovieSceneMpcColorSection::HasKeys(const FColorKey& Key) const
{
	const FRichCurve* ChannelCurve = GetCurveForChannel(Key.Channel, &RedCurve, &GreenCurve, &BlueCurve, &AlphaCurve);
	return ChannelCurve->GetNumKeys() != 0;
}


void UMovieSceneMpcColorSection::SetDefault(const FColorKey& Key)
{
	FRichCurve* ChannelCurve = GetCurveForChannel(Key.Channel, &RedCurve, &GreenCurve, &BlueCurve, &AlphaCurve);
	SetCurveDefault(*ChannelCurve, Key.ChannelValue);
}
