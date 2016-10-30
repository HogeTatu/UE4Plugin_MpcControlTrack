// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "IKeyframeSection.h"
#include "MovieSceneKeyStruct.h"
#include "MovieSceneSection.h"
#include "MovieSceneMpcColorSection.generated.h"


enum class EKeyColorChannel
{
	Red,
	Green,
	Blue,
	Alpha,
};


struct FColorKey
{
	FColorKey(EKeyColorChannel InChannel, float InChannelValue, bool InbIsSlateColor)
	{
		Channel = InChannel;
		ChannelValue = InChannelValue;
		bIsSlateColor = InbIsSlateColor;
	}

	EKeyColorChannel Channel;
	float ChannelValue;
	bool bIsSlateColor;
};


/**
 * Proxy structure for color section key data.
 */
USTRUCT()
struct FMovieSceneMpcColorKeyStruct
	: public FMovieSceneKeyStruct
{
	GENERATED_BODY()

	/** They key's color value. */
	UPROPERTY(EditAnywhere, Category=Key, meta=(InlineColorPicker))
	FLinearColor Color;

	FRichCurveKey* Keys[4];
	FRichCurve* Curves[4];

	virtual void PropagateChanges(const FPropertyChangedEvent& ChangeEvent) override;
};


/**
 * A single floating point section
 */
UCLASS(MinimalAPI)
class UMovieSceneMpcColorSection
	: public UMovieSceneSection
	, public IKeyframeSection<FColorKey>
{
	GENERATED_UCLASS_BODY()

public:

	/**
	 * Updates this section
	 *
	 * @param Position The position in time within the movie scene.
	 * @param DefaultColor The default value to return.
	 */
	virtual FLinearColor Eval(float Position, const FLinearColor& DefaultColor) const;

	/**
	 * Gets the red color curve
	 *
	 * @return The rich curve for this color channel
	 * @see GetAlphaCurve, GetBlueCurve, GetGreenCurve
	 */
	FRichCurve& GetRedCurve() { return RedCurve; }
	const FRichCurve& GetRedCurve() const { return RedCurve; }

	/**
	 * Gets the green color curve
	 *
	 * @return The rich curve for this color channel
	 * @see GetAlphaCurve, GetBlueCurve, GetRedCurve
	 */
	FRichCurve& GetGreenCurve() { return GreenCurve; }
	const FRichCurve& GetGreenCurve() const { return GreenCurve; }

	/**
	 * Gets the blue color curve
	 *
	 * @return The rich curve for this color channel
	 * @see GetAlphaCurve, GetGreenCurve, GetRedCurve
	 */
	FRichCurve& GetBlueCurve() { return BlueCurve; }
	const FRichCurve& GetBlueCurve() const { return BlueCurve; }

	/**
	 * Gets the alpha color curve
	 *
	 * @return The rich curve for this color channel
	 * @see GetBlueCurve, GetGreenCurve, GetRedCurve
	 */
	FRichCurve& GetAlphaCurve() { return AlphaCurve; }
	const FRichCurve& GetAlphaCurve() const { return AlphaCurve; }

public:

	//~ UMovieSceneSection interface

	virtual void MoveSection(float DeltaPosition, TSet<FKeyHandle>& KeyHandles) override;
	virtual void DilateSection(float DilationFactor, float Origin, TSet<FKeyHandle>& KeyHandles) override;
	virtual void GetKeyHandles(TSet<FKeyHandle>& OutKeyHandles, TRange<float> TimeRange) const override;
	virtual TSharedPtr<FStructOnScope> GetKeyStruct(const TArray<FKeyHandle>& KeyHandles) override;
	virtual TOptional<float> GetKeyTime(FKeyHandle KeyHandle) const override;
	virtual void SetKeyTime(FKeyHandle KeyHandle, float Time) override;

public:

	//~ IKeyframeSection interface

	virtual void AddKey(float Time, const FColorKey& Key, EMovieSceneKeyInterpolation KeyInterpolation) override;
	virtual bool NewKeyIsNewData(float Time, const FColorKey& Key) const override;
	virtual bool HasKeys(const FColorKey& Key) const override;
	virtual void SetDefault(const FColorKey& Key) override;

private:

	/** Red curve data */
	UPROPERTY()
	FRichCurve RedCurve;

	/** Green curve data */
	UPROPERTY()
	FRichCurve GreenCurve;

	/** Blue curve data */
	UPROPERTY()
	FRichCurve BlueCurve;

	/** Alpha curve data */
	UPROPERTY()
	FRichCurve AlphaCurve;
};
