// 2024, Pseudo / Ageev Daniil. All rights reserved ©


#include "InsaneGA_Shoot.h"

#include "InsaneGameplayTags.h"
#include "InsanePartyCharacter.h"
#include "InsaneProjectileBase.h"
#include "NativeGameplayTags.h"
#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"
#include "GameFramework/ProjectileMovementComponent.h"


UInsaneGA_Shoot::UInsaneGA_Shoot()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	
	FGameplayTag AbilityShootTag = FGameplayTag::RequestGameplayTag(FName("PlayerActions.Shoot"));
	AbilityTags.AddTag(AbilityShootTag);
	ActivationOwnedTags.AddTag(AbilityShootTag);
	
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
		if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
		{
			EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
		}
		else
		{
			K2_ActivateAbility();
			ProjectileSpawn(PartyCharacter, AttachedWeapon->WeaponData->WeaponData.Projectile, AttachedWeapon->WeaponData, GetAvatarActorFromActorInfo()->GetInstigator());
			FGameplayTagContainer Tags;
			GetAbilitySystemComponentFromActorInfo()->GetOwnedGameplayTags(Tags);
			if(Tags.HasTag(InsaneGameplayTags::GameplayStatus_Aiming))
			{
				UE_LOG(LogTemp, Warning, TEXT("1"));
				GetWorld()->GetTimerManager().SetTimer(ShootDelay, this, &UInsaneGA_Shoot::OnDelayEnd, AttachedWeapon->WeaponData->WeaponData.Properties.ShootDelay, false);
				//add recoil in weapon data
				PartyCharacter->IMP_Recoil(0.5f * 0.7f, 1.5f * 0.5f, 0.5f, 0.8f);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("0"));
				GetWorld()->GetTimerManager().SetTimer(ShootDelay, this, &UInsaneGA_Shoot::OnDelayEnd, AttachedWeapon->WeaponData->WeaponData.Properties.ShootDelay, false);
				//add recoil in weapon data
				PartyCharacter->IMP_Recoil(0.5f, 1.5f, 0.5f, 0.8f);
			}
		}
	}
	else
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
	}
}

void UInsaneGA_Shoot::ProjectileSpawn_Implementation(AInsanePartyCharacter* PartyCharacter, TSubclassOf<AInsaneProjectileBase> Projectile, UInsaneWeaponPrimaryDataAsset* WeaponData, APawn* PartyInstigator)
{
	FVector Location = PartyCharacter->GetFollowCamera()->GetForwardVector() * 200.f + PartyCharacter->GetFollowCamera()->GetComponentLocation();
	FRotator Rotation = PartyCharacter->GetFollowCamera()->GetComponentRotation();
	FTransform Transform;
	Transform.SetLocation(Location);
	Transform.SetRotation(Rotation.Quaternion());
	Transform.SetScale3D(FVector(1.f));

	
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		
	AInsaneProjectileBase* ProjectileToSpawn = GetWorld()->SpawnActorDeferred<AInsaneProjectileBase>(Projectile, Transform, PartyCharacter,
		PartyInstigator, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	ProjectileToSpawn->ProjectileMovementComponent->InitialSpeed = WeaponData->WeaponData.Properties.ProjectileSpeed;
	ProjectileToSpawn->ProjectileMovementComponent->ProjectileGravityScale = WeaponData->WeaponData.Properties.ProjectileGravityScale;
	ProjectileToSpawn->ProjectileData = WeaponData;
	ProjectileToSpawn->FinishSpawning(Transform);
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

