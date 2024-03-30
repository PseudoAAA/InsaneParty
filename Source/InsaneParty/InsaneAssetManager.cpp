// 2024, Pseudo / Ageev Daniil. All rights reserved ©


#include "InsaneAssetManager.h"
#include "AbilitySystemGlobals.h"

UInsaneAssetManager& UInsaneAssetManager::Get()
{
	UInsaneAssetManager* Singleton = Cast<UInsaneAssetManager>(GEngine->AssetManager);

	if (Singleton)
	{
		return *Singleton;
	}
	else
	{
		UE_LOG(LogTemp, Fatal, TEXT("Invalid AssetManager in DefaultEngine.ini, must be GDAssetManager!"));
		return *NewObject<UInsaneAssetManager>();	 // never calls this
	}
}

void UInsaneAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	UAbilitySystemGlobals::Get().InitGlobalData();
}
