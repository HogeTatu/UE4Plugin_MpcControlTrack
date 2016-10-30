// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "MpcControlTrackEditorPrivatePCH.h"
#include "FloatCurveKeyArea.h"
#include "MpcFloatPropertySection.h"
#include "MovieSceneMpcFloatSection.h"


void FMpcFloatPropertySection::GenerateSectionLayout(class ISectionLayoutBuilder& LayoutBuilder) const
{
	UMovieSceneMpcFloatSection* FloatSection = Cast<UMovieSceneMpcFloatSection>(&SectionObject);
	KeyArea = MakeShareable(new FFloatCurveKeyArea(&FloatSection->GetFloatCurve(), FloatSection));
	LayoutBuilder.SetSectionAsKeyArea(KeyArea.ToSharedRef());
}


void FMpcFloatPropertySection::SetIntermediateValue(FPropertyChangedParams PropertyChangedParams)
{
	KeyArea->SetIntermediateValue(PropertyChangedParams.GetPropertyValue<float>());
}


void FMpcFloatPropertySection::ClearIntermediateValue()
{
	KeyArea->ClearIntermediateValue();
}
