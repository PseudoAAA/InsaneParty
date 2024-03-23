// 2024, Pseudo / Ageev Daniil. All rights reserved ©

#pragma once

#include "AbilitySystemInterface.h"
#include "InsaneParty.h"
#include "GameFramework/Character.h"
#include "InsanePartyCharacterBase.generated.h"

class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS()
class AInsanePartyCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AInsanePartyCharacterBase();

	// To add mapping context
	virtual void BeginPlay() override;
	
	// Implement IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	
	UFUNCTION(BlueprintCallable, Category = "InsanePartyCharacter|Attributes")
	float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "InsanePartyCharacter|Attributes")
	float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable, Category = "InsanePartyCharacter|Attributes")
	float GetMedals() const;

	UFUNCTION(BlueprintCallable, Category = "InsanePartyCharacter|Attributes")
	float GetMaxMedals() const;
	
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	
	UFUNCTION(BlueprintCallable, Category = "GASDocumentation|GDCharacter")
	virtual int32 GetAbilityLevel(EInsaneAbilityInputID AbilityID) const;
	
	// Removes all CharacterAbilities. Can only be called by the Server. Removing on the Server will remove from Client too.
	virtual void RemoveCharacterAbilities();

	UFUNCTION(BlueprintCallable, Category = "InsanePartyCharacter")
	virtual void IsAlive();
	virtual void Die();
	
	/*UFUNCTION(BlueprintCallable, Category = "InsanePartyCharacter")
	virtual void FinishDying();*/
	
protected:
	
	TWeakObjectPtr<UInsaneAbilitySystemComponent> AbilitySystemComponent;
	TWeakObjectPtr<UInsaneAttributeSet> AttributeSetBase;



	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "InsanePartyCharacter")
	FText CharacterName;

	
	// Default abilities for this Character. These will be removed on Character death and regiven if Character respawns.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "InsanePartyCharacter|Abilities")
	TArray<TSubclassOf<UInsaneGameplayAbility>> CharacterAbilities;

	// Default attributes for a character for initializing on spawn/respawn.
	// This is an instant GE that overrides the values for attributes that get reset on spawn/respawn.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "InsanePartyCharacter|Abilities")
	TSubclassOf<UGameplayEffect> DefaultAttributes;

	// These effects are only applied one time on startup
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "InsanePartyCharacter|Abilities")
	TArray<TSubclassOf<UGameplayEffect>> StartupEffects;

	// Grant abilities on the Server. The Ability Specs will be replicated to the owning client.
	virtual void AddCharacterAbilities();

	// Initialize the Character's attributes. Must run on Server but we run it on Client too
	// so that we don't have to wait. The Server's replication to the Client won't matter since
	// the values should be the same.
	virtual void InitializeAttributes();

	virtual void AddStartupEffects();
	
	/**
	* Setters for Attributes. Only use these in special cases like Respawning, otherwise use a GE to change Attributes.
	* These change the Attribute's Base Value.
	*/
	
	virtual void SetHealth(float Health);
	//virtual void SetMana(float Mana);
	//virtual void SetStamina(float Stamina);
};

