// 2024, Pseudo / Ageev Daniil. All rights reserved ©

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "InsaneAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class INSANEPARTY_API UInsaneAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	bool bCharacterAbilitiesGiven = false;
	bool bStartupEffectsApplied = false;
	
};
