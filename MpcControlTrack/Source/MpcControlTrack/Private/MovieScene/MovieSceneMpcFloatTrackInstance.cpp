// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "MpcControlTrackPrivatePCH.h"
#include "MovieSceneMpcFloatTrack.h"
#include "MpcOwnerActor.h"
#include "MovieSceneMpcFloatTrackInstance.h"


FMovieSceneMpcFloatTrackInstance::FMovieSceneMpcFloatTrackInstance( UMovieSceneMpcFloatTrack& InFloatTrack )
{
	FloatTrack = &InFloatTrack;

	PropertyBindings = MakeShareable( new FTrackInstancePropertyBindings( FloatTrack->GetPropertyName(), FloatTrack->GetPropertyPath(), TEXT("SetFloatValue") ) );
}


void FMovieSceneMpcFloatTrackInstance::SaveState(const TArray<TWeakObjectPtr<UObject>>& RuntimeObjects, IMovieScenePlayer& Player, FMovieSceneSequenceInstance& SequenceInstance)
{
	for (auto ObjectPtr : RuntimeObjects)
	{
		UObject* Object = ObjectPtr.Get();

		if (InitFloatMap.Find(Object) == nullptr)
		{
			float FloatValue = PropertyBindings->GetCurrentValue<float>(Object);
			InitFloatMap.Add(Object, FloatValue);
		}
	}
}


void FMovieSceneMpcFloatTrackInstance::RestoreState(const TArray<TWeakObjectPtr<UObject>>& RuntimeObjects, IMovieScenePlayer& Player, FMovieSceneSequenceInstance& SequenceInstance)
{
	for (auto ObjectPtr : RuntimeObjects)
	{
		UObject* Object = ObjectPtr.Get();

		if (!IsValid(Object))
		{
			continue;
		}

		float *FloatValue = InitFloatMap.Find(Object);
		if (FloatValue != nullptr)
		{
			PropertyBindings->CallFunction<float>( Object, &FloatValue );
			TrySetMpcScalarValue(Object, *FloatValue);
		}
	}

	PropertyBindings->UpdateBindings( RuntimeObjects );
}


void FMovieSceneMpcFloatTrackInstance::Update(EMovieSceneUpdateData& UpdateData, const TArray<TWeakObjectPtr<UObject>>& RuntimeObjects, class IMovieScenePlayer& Player, FMovieSceneSequenceInstance& SequenceInstance )
{
	float FloatValue = 0.0f;
	if( FloatTrack->Eval( UpdateData.Position, UpdateData.LastPosition, FloatValue ) )
	{
		for(auto ObjectPtr : RuntimeObjects)
		{
			UObject* Object = ObjectPtr.Get();
			PropertyBindings->CallFunction<float>( Object, &FloatValue );
			TrySetMpcScalarValue(Object, FloatValue);
		}
	}
}


void FMovieSceneMpcFloatTrackInstance::TrySetMpcScalarValue(UObject* Object, float FloatValue)
{
	auto MpcOwner = Cast<AMpcOwnerActor>(Object);
	if (MpcOwner)
	{
		auto Collection = MpcOwner->GetMaterialParameterCollection();
		if (Collection)
		{
			auto World = MpcOwner->GetWorld();
			auto Instance = World->GetParameterCollectionInstance(Collection);
			Instance->SetScalarParameterValue(FloatTrack->GetPropertyName(), FloatValue);
		}
	}
}


void FMovieSceneMpcFloatTrackInstance::RefreshInstance( const TArray<TWeakObjectPtr<UObject>>& RuntimeObjects, class IMovieScenePlayer& Player, FMovieSceneSequenceInstance& SequenceInstance )
{
	PropertyBindings->UpdateBindings( RuntimeObjects );
}
