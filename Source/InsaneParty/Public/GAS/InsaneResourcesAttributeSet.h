// 2024, Pseudo / Ageev Daniil. All rights reserved ©

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "InsaneResourcesAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class INSANEPARTY_API UInsaneResourcesAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UInsaneResourcesAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(BlueprintReadOnly, Category = "InsaneAttributes", ReplicatedUsing = OnRep_Medals)
	FGameplayAttributeData Medals;
	ATTRIBUTE_ACCESSORS(UInsaneResourcesAttributeSet, Medals);
	
	UPROPERTY(BlueprintReadOnly, Category = "InsaneAttributes", ReplicatedUsing = OnRep_Medals)
	FGameplayAttributeData MaxMedals;
	ATTRIBUTE_ACCESSORS(UInsaneResourcesAttributeSet, MaxMedals);

	UPROPERTY(BlueprintReadOnly, Category = "InsaneAttributes", ReplicatedUsing = OnRep_Medals)
	FGameplayAttributeData Keys;
	ATTRIBUTE_ACCESSORS(UInsaneResourcesAttributeSet, Keys);

	
	UFUNCTION()
	virtual void OnRep_Medals(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_MaxMedals(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_Keys(const FGameplayAttributeData& OldValue);
};
