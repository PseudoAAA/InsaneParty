// 2024, Pseudo / Ageev Daniil. All rights reserved ©


#include "InsaneGA_Shoot.h"

#include "InsaneGameplayTags.h"
#include "InsanePartyCharacter.h"
#include "InsaneProjectileBase.h"
#include "NativeGameplayTags.h"
#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"


UInsaneGA_Shoot::UInsaneGA_Shoot()
{
	
	FGameplayTag AbilityShootTag = FGameplayTag::RequestGameplayTag(FName("PlayerActions.Shoot"));
	AbilityTags.AddTag(AbilityShootTag);
	ActivationOwnedTags.AddTag(AbilityShootTag);
	this->ReplicationPolicy = EGameplayAbilityReplicationPolicy::ReplicateYes;
	
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("GameplayStatus.IsDead")));
}

void UInsaneGA_Shoot::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                      const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                      const FGameplayEventData* TriggerEventData)
{
	AInsanePartyCharacter* PartyCharacter = CastChecked<AInsanePartyCharacter>(GetAvatarActorFromActorInfo());
	UInsaneInventorySystemComponent* PartyCharacterInventory = CastChecked<AInsanePlayerState>(PartyCharacter->GetPlayerState())->GetInventorySystemComponent();
	AInsaneWeaponBase* AttachedWeapon = PartyCharacterInventory->GetAttachedWeapon(PartyCharacter, PartyCharacterInventory->GetActiveSlotIndex());
	
	if(AttachedWeapon && AttachedWeapon->MagazineInfo.CurrentAmmoCount > 0 && AttachedWeapon->WeaponData->WeaponData.WeaponType == EWeaponType::Gun)
	{
		PartyCharacterInventory->DecreaseAmmoInMagazine(AttachedWeapon);
		K2_ActivateAbility();
		
		if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
		{
			EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
		}
		else
		{
			FGameplayTagContainer Tags;
			GetAbilitySystemComponentFromActorInfo()->GetOwnedGameplayTags(Tags);
			if(Tags.HasTag(InsaneGameplayTags::GameplayStatus_Aiming))
			{
				UE_LOG(LogTemp, Warning, TEXT("Active Slot: %d"), PartyCharacterInventory->GetActiveSlotIndex());
				UE_LOG(LogTemp, Warning, TEXT("Weapon name: %s"), *AttachedWeapon->GetName());
				
				GetWorld()->GetTimerManager().SetTimer(ShootDelay, this, &UInsaneGA_Shoot::OnDelayEnd, AttachedWeapon->WeaponData->WeaponData.Properties.ShootDelay, false);
				PartyCharacter->IMP_Recoil(0.3f * 0.7f, 1.2f * 0.5f, 0.5f, 0.8f);
			}
			else
			{
				GetWorld()->GetTimerManager().SetTimer(ShootDelay, this, &UInsaneGA_Shoot::OnDelayEnd, AttachedWeapon->WeaponData->WeaponData.Properties.ShootDelay, false);
				PartyCharacter->IMP_Recoil(0.3f, 1.2f, 0.5f, 0.8f);
			}
		}
	}
	else
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
	}
}

void UInsaneGA_Shoot::SingleFireRelease(float TimeHeld)	
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UInsaneGA_Shoot::OnDelayEnd()
{
	UAbilityTask_WaitInputRelease* Task = UAbilityTask_WaitInputRelease::WaitInputRelease(this, true);
	AInsanePartyCharacter* PartyCharacter = CastChecked<AInsanePartyCharacter>(GetAvatarActorFromActorInfo());
	UInsaneInventorySystemComponent* PartyCharacterInventory = CastChecked<AInsanePlayerState>(PartyCharacter->GetPlayerState())->GetInventorySystemComponent();
	AInsaneWeaponBase* AttachedWeapon = PartyCharacterInventory->GetAttachedWeapon(PartyCharacter, PartyCharacterInventory->GetActiveSlotIndex());
	if(AttachedWeapon && AttachedWeapon->MagazineInfo.CurrentFireMode == AttachedWeapon->WeaponData->WeaponData.SingleFireModeEffect)
	{
		Task->OnRelease.AddDynamic(this, &UInsaneGA_Shoot::SingleFireRelease);
		Task->ReadyForActivation();
	}
	else
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
	}
}


void UInsaneGA_Shoot::OnCancelled(FGameplayTag EventTag, FGameplayEventData EventData)
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}

void UInsaneGA_Shoot::OnCompleted(FGameplayTag EventTag, FGameplayEventData EventData)
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

