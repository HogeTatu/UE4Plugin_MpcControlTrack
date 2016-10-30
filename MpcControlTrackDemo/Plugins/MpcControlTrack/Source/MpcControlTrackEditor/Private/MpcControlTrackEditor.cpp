// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "MpcControlTrackEditorPrivatePCH.h"
#include "ModuleManager.h"
#include "ISequencerModule.h"
#include "MpcColorPropertyTrackEditor.h"
#include "MpcFloatPropertyTrackEditor.h"

#define LOCTEXT_NAMESPACE "FMpcControlTrackEditorModule"

void FMpcControlTrackEditorModule::StartupModule()
{
	ISequencerModule& SequencerModule = FModuleManager::Get().LoadModuleChecked<ISequencerModule>( "Sequencer" );
	ColorPropertyTrackCreateEditorHandle = SequencerModule.RegisterTrackEditor_Handle( FOnCreateTrackEditor::CreateStatic( &FMpcColorPropertyTrackEditor::CreateTrackEditor ) );
	FloatPropertyTrackCreateEditorHandle = SequencerModule.RegisterTrackEditor_Handle( FOnCreateTrackEditor::CreateStatic( &FMpcFloatPropertyTrackEditor::CreateTrackEditor ) );
}

void FMpcControlTrackEditorModule::ShutdownModule()
{
	ISequencerModule& SequencerModule = FModuleManager::Get().LoadModuleChecked<ISequencerModule>( "Sequencer" );
	SequencerModule.UnRegisterTrackEditor_Handle( ColorPropertyTrackCreateEditorHandle );
	SequencerModule.UnRegisterTrackEditor_Handle( FloatPropertyTrackCreateEditorHandle );
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FMpcControlTrackEditorModule, MpcControlTrackEditor)