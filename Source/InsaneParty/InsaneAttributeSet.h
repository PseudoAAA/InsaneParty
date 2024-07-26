// 2024, Pseudo / Ageev Daniil. All rights reserved ©

#pragma once

#include "CoreMinimal.h"
#include "InsaneAbilitySystemComponent.h"
#include "AttributeSet.h"
#include "InsaneParty.h"
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

	
	UPROPERTY(BlueprintReadOnly, Category = "InsaneAttributes", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UInsaneAttributeSet, Health);
	
	UPROPERTY(BlueprintReadOnly, Category = "InsaneAttributes", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UInsaneAttributeSet, MaxHealth)
	
	UPROPERTY(BlueprintReadOnly, Category = "InsaneAttributes", ReplicatedUsing = OnRep_Healing)
	FGameplayAttributeData Healing;
	ATTRIBUTE_ACCESSORS(UInsaneAttributeSet, Healing)
	
	UPROPERTY(BlueprintReadOnly, Category = "InsaneAttributes", ReplicatedUsing = OnRep_Damage)
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UInsaneAttributeSet, Damage)
	
	UPROPERTY(BlueprintReadOnly, Category = "InsaneAttributes", ReplicatedUsing = OnRep_Damaging)
	FGameplayAttributeData Damaging;
	ATTRIBUTE_ACCESSORS(UInsaneAttributeSet, Damaging)
	
	UPROPERTY(BlueprintReadOnly, Category = "InsaneAttributes", ReplicatedUsing = OnRep_Medals)
	FGameplayAttributeData Medals;
	ATTRIBUTE_ACCESSORS(UInsaneAttributeSet, Medals);
	
	UPROPERTY(BlueprintReadOnly, Category = "InsaneAttributes", ReplicatedUsing = OnRep_MaxMedals)
	FGameplayAttributeData MaxMedals;
	ATTRIBUTE_ACCESSORS(UInsaneAttributeSet, MaxMedals);
	
	UPROPERTY(BlueprintReadOnly, Category = "InsaneAttributes", ReplicatedUsing = OnRep_Keys)
	FGameplayAttributeData Keys;
	ATTRIBUTE_ACCESSORS(UInsaneAttributeSet, Keys);
	
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
	virtual void OnRep_Damage(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_Damaging(const FGameplayAttributeData& OldValue);
	
	UFUNCTION()
	virtual void OnRep_Medals(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MaxMedals(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_Keys(const FGameplayAttributeData& OldValue);
	
};
