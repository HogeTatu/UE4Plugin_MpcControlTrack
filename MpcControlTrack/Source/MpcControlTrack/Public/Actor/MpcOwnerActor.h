#pragma once

#include "Materials/MaterialParameterCollection.h"
#include "MpcOwnerActor.generated.h"

/**
 * The owner actor of the material parameter collection.
 */
UCLASS( MinimalAPI )
class AMpcOwnerActor : public AActor
{
	GENERATED_BODY()

public:
	AMpcOwnerActor(const FObjectInitializer& ObjectInitializer);

	virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION(BlueprintPure, Category="Material")
	UMaterialParameterCollection* GetMaterialParameterCollection() const
	{
		return MaterialParameterCollection;
	}

private_subobject:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Material")
	UMaterialParameterCollection* MaterialParameterCollection;
};
