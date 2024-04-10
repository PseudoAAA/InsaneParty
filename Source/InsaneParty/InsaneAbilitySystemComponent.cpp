// 2024, Pseudo / Ageev Daniil. All rights reserved ©


#include "InsaneAbilitySystemComponent.h"

#include "InsaneGameplayAbility.h"


void UInsaneAbilitySystemComponent::ReceiveDamage(UInsaneAbilitySystemComponent* SourceASC, float Damage)
{
	ReceivedDamage.Broadcast(SourceASC, Damage);
	
}
