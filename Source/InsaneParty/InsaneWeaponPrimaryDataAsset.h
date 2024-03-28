// 2024, Pseudo / Ageev Daniil. All rights reserved ©

#pragma once

#include "CoreMinimal.h"
#include "InsaneData.h"
#include "Engine/DataAsset.h"
#include "InsaneWeaponPrimaryDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class INSANEPARTY_API UInsaneWeaponPrimaryDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InsaneParty|InventoryWeaponData")
	FWeapon WeaponData;

	UFUNCTION()
	bool WeaponDataIsEmpty() const;
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InsaneParty|InventoryWeaponData")
	FGameplayTag WeaponTag;*/
};
