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
	EInsaneAbilityInputID AbilityInputID = EInsaneAbilityInputID::None;

	// Value to associate an ability with an slot without tying it to an automatically activated input.
	// Passive abilities won't be tied to an input so we need a way to generically associate abilities with slots.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	EInsaneAbilityInputID AbilityID = EInsaneAbilityInputID::None;

	// Tells an ability to activate immediately when its granted. Used for passive abilities and abilities forced on others.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ability")
	bool ActivateAbilityOnGranted = false;

	// If an ability is marked as 'ActivateAbilityOnGranted', activate them immediately when given here
	// Epic's comment: Projects may want to initiate passives or do other "BeginPlay" type of logic here.
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
};
