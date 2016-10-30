// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "MpcControlTrackEditor.h"

// You should place include statements to your module's private header files here.  You only need to
// add includes for headers that are used in most of your module's source files though.

#include "Runtime/Core/Public/Core.h"
#include "Runtime/CoreUObject/Public/CoreUObject.h"
#include "Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "Runtime/Engine/Classes/Curves/IntegralCurve.h"
#include "Runtime/Engine/Classes/Curves/NameCurve.h"
#include "Runtime/Engine/Classes/Curves/RichCurve.h"
#include "Runtime/MovieScene/Public/MovieScene.h"
#include "Runtime/MovieScene/Public/MovieSceneSequenceInstance.h"
#include "Runtime/MovieScene/Public/KeyParams.h"
#include "Runtime/Slate/Public/SlateBasics.h"

#include "Editor/Sequencer/Public/ISectionLayoutBuilder.h"
#include "Editor/Sequencer/Public/ISequencerSection.h"
#include "Editor/Sequencer/Public/MovieSceneTrackEditor.h"
#include "Runtime/MovieScene/Public/MovieSceneCommonHelpers.h"
#include "Runtime/MovieScene/Public/MovieSceneSection.h"
#include "Editor/UnrealEd/Public/ScopedTransaction.h"
#include "Editor/UnrealEd/Public/UnrealEd.h"
