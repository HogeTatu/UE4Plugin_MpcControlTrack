#include "MpcControlTrackPrivatePCH.h"
#include "MpcOwnerActor.h"

AMpcOwnerActor::AMpcOwnerActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
}

void AMpcOwnerActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

#if WITH_EDITOR
	for (auto Property : TFieldRange<UProperty>(GetClass()))
	{
		if (Property->IsA(UFloatProperty::StaticClass()))
		{
			Property->SetMetaData(TEXT("SequencerTrackClass"), TEXT("MovieSceneMpcFloatTrack"));
			continue;
		}
		else if (Property->IsA(UStructProperty::StaticClass()))
		{
			auto PropertyFName = Cast<UStructProperty>(Property)->Struct->GetFName();
			if (PropertyFName == NAME_Color || PropertyFName == NAME_LinearColor)
			{
				Property->SetMetaData(TEXT("SequencerTrackClass"), TEXT("MovieSceneMpcColorTrack"));
			}
			continue;
		}
	}
#endif
}
