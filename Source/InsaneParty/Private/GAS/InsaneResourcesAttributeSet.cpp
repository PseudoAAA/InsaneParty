// 2024, Pseudo / Ageev Daniil. All rights reserved ©


#include "GAS/InsaneResourcesAttributeSet.h"
#include "Net/UnrealNetwork.h"

UInsaneResourcesAttributeSet::UInsaneResourcesAttributeSet()
	:Medals(0)
	,MaxMedals(4)
	,Keys(0)
{}

void UInsaneResourcesAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UInsaneResourcesAttributeSet, Medals, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UInsaneResourcesAttributeSet, MaxMedals, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UInsaneResourcesAttributeSet, Keys, COND_None, REPNOTIFY_Always);
}

void UInsaneResourcesAttributeSet::OnRep_Medals(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UInsaneResourcesAttributeSet, Medals, OldValue);
}

void UInsaneResourcesAttributeSet::OnRep_MaxMedals(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UInsaneResourcesAttributeSet, MaxMedals, OldValue);
}

void UInsaneResourcesAttributeSet::OnRep_Keys(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UInsaneResourcesAttributeSet, Keys, OldValue);
}
