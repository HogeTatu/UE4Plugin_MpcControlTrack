// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ModuleManager.h"

class FMpcControlTrackEditorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	FDelegateHandle ColorPropertyTrackCreateEditorHandle;
	FDelegateHandle FloatPropertyTrackCreateEditorHandle;
};