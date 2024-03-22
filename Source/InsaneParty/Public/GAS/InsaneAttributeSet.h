// 2024, Pseudo / Ageev Daniil. All rights reserved ©

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "InsaneResourcesAttributeSet.h"
#include "InsaneParty/InsaneParty.h"
#include "InsaneAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


UCLASS()
class INSANEPARTY_API UInsaneAttributeSet : public UInsaneResourcesAttributeSet
{
	GENERATED_BODY()


public:
	UInsaneAttributeSet();
	
	ATTRIBUTE_ACCESSORS(UInsaneAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(UInsaneAttributeSet, MaxHealth)
	ATTRIBUTE_ACCESSORS(UInsaneAttributeSet, Healing)
	ATTRIBUTE_ACCESSORS(UInsaneAttributeSet, Damage)
	ATTRIBUTE_ACCESSORS(UInsaneAttributeSet, Damaging)
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	
	UPROPERTY(BlueprintReadOnly, Category = "InsaneAttributes", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	
	UPROPERTY(BlueprintReadOnly, Category = "InsaneAttributes", ReplicatedUsing=OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;

	UPROPERTY(BlueprintReadOnly, Category = "InsaneAttributes")
	FGameplayAttributeData Healing;

	UPROPERTY(BlueprintReadOnly, Category = "InsaneAttributes")
	FGameplayAttributeData Damage;
	
	UPROPERTY(BlueprintReadOnly, Category = "InsaneAttributes")
	FGameplayAttributeData Damaging;
	
	void AdjustAttributeForMaxChange(const FGameplayAttributeData& AffectedAttribute,
		const FGameplayAttributeData& MaxAttribute, float NewMaxValue,
		const FGameplayAttribute& AffectedAttributeProperty) const;
	
	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);
	
};
