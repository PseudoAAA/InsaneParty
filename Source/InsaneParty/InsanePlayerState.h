// 2024, Pseudo / Ageev Daniil. All rights reserved ©

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "GameplayTagContainer.h"
#include "InsaneInventorySystemComponent.h"
#include "GameFramework/PlayerState.h"
#include "InsanePlayerState.generated.h"

class UInsaneAbilitySystemComponent;
class UInsaneAttributeSet;
class UInsaneInventorySystemComponent;
/**
 * 
 */

UCLASS()
class INSANEPARTY_API AInsanePlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AInsanePlayerState();
	
	UFUNCTION(BlueprintCallable)
	UInsaneInventorySystemComponent* GetInventorySystemComponent() const;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UInsaneAttributeSet* GetInsaneAttributeSet() const;

	UFUNCTION(BlueprintCallable, Category = "InsanePlayerState")
	bool IsAlive() const;
	

	/** Getters for attributes from GDAttributeSetBase. Returns Current Value unless otherwise specified.*/
	UFUNCTION(BlueprintCallable, Category = "InsanePlayerState|Attributes")
	float GetHealth() const;
	UFUNCTION(BlueprintCallable, Category = "InsanePlayerState|Attributes")
	float GetMaxHealth() const;
	UFUNCTION(BlueprintCallable, Category = "InsanePlayerState|Attributes")
	float GetMedals() const;
	UFUNCTION(BlueprintCallable, Category = "InsanePlayerState|Attributes")
	float GetMaxMedals() const;
	UFUNCTION(BlueprintCallable, Category = "InsanePlayerState|Attributes")
	float GetKeys() const;

protected:
	UPROPERTY()
	UInsaneInventorySystemComponent* InventorySystemComponent;
	
	UPROPERTY()
	UInsaneAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY()
	UInsaneAttributeSet* InsaneAttributeSet;

	FGameplayTag DeadTag;

	FDelegateHandle HealthChangedDelegateHandle;
	FDelegateHandle MaxHealthChangedDelegateHandle;
	FDelegateHandle MedalsChangedDelegateHandle;
	FDelegateHandle MaxMedalsChangedDelegateHandle;
	FDelegateHandle KeysChangedDelegateHandle;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Attribute changed callbacks
	virtual void HealthChanged(const FOnAttributeChangeData& Data);
	virtual void MaxHealthChanged(const FOnAttributeChangeData& Data);
	virtual void MedalsChanged(const FOnAttributeChangeData& Data);
	virtual void MaxMedalsChanged(const FOnAttributeChangeData& Data);
	virtual void KeysChanged(const FOnAttributeChangeData& Data);
};
