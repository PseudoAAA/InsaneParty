// 2024, Pseudo / Ageev Daniil. All rights reserved ©

#pragma once

#include "CoreMinimal.h" 
#include "InsaneParty/InsaneParty.h"
#include "Abilities/GameplayAbility.h"
#include "InsaneGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class INSANEPARTY_API UInsaneGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UInsaneGameplayAbility();
	
	// Abilities will activate when input is pressed
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	EInsaneAbilityInputID AbilityInputID {EInsaneAbilityInputID::None};
};
