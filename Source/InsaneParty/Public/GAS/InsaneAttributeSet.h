// 2024, Pseudo / Ageev Daniil. All rights reserved ©

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "InsaneParty/InsaneParty.h"
#include "InsaneAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


UCLASS()
class INSANEPARTY_API UInsaneAttributeSet : public UAttributeSet
{
	GENERATED_BODY()


public:
	UInsaneAttributeSet();
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	
	UPROPERTY(BlueprintReadOnly, Category = "Health" ,ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UInsaneAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing=OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UInsaneAttributeSet, MaxHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Healing", ReplicatedUsing=OnRep_Healing)
	FGameplayAttributeData Healing;
	ATTRIBUTE_ACCESSORS(UInsaneAttributeSet, Healing)
	
	UPROPERTY(BlueprintReadOnly, Category = "Medals", ReplicatedUsing=OnRep_Medals)
	FGameplayAttributeData Medals;
	ATTRIBUTE_ACCESSORS(UInsaneAttributeSet, Medals)



	void AdjustAttributeForMaxChange(const FGameplayAttributeData& AffectedAttribute,
		const FGameplayAttributeData& MaxAttribute, float NewMaxValue,
		const FGameplayAttribute& AffectedAttributeProperty) const;
	
	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);
	
	UFUNCTION()
	virtual void OnRep_Healing(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_Medals(const FGameplayAttributeData& OldValue);
};
