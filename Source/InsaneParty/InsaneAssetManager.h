// 2024, Pseudo / Ageev Daniil. All rights reserved ©

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "InsaneAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class INSANEPARTY_API UInsaneAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	static UInsaneAssetManager& Get();

	/** Starts initial load, gets called from InitializeObjectReferences */
	virtual void StartInitialLoading() override;
};
