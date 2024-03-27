// 2024, Pseudo / Ageev Daniil. All rights reserved ©

#pragma once

#include "Abilities/GameplayAbility.h"
#include "InsaneData.generated.h"

UENUM(BlueprintType)
enum class EInsaneAbilityInputID : uint8
{
	// 0 None
	None			UMETA(DisplayName = "None"),
	// 1 Confirm
	Confirm			UMETA(DisplayName = "Confirm"),
	// 2 Cancel
	Cancel			UMETA(DisplayName = "Cancel"),
};

USTRUCT(BlueprintType)
struct FWeapon
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InsaneParty|WeaponStruct")
	FName WeaponName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InsaneParty|WeaponStruct")
	TSubclassOf<UGameplayAbility> Ability;
	
};
