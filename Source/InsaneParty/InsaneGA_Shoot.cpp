// 2024, Pseudo / Ageev Daniil. All rights reserved ©


#include "InsaneGA_Shoot.h"

#include "InsaneGameplayTags.h"
#include "InsanePartyCharacter.h"
#include "InsaneProjectileBase.h"
#include "NativeGameplayTags.h"
#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"
#include "Interfaces/NetworkPredictionInterface.h"

UInsaneGA_Shoot::UInsaneGA_Shoot()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	
	FGameplayTag AbilityShootTag = FGameplayTag::RequestGameplayTag(FName("PlayerActions.Shoot"));
	AbilityTags.AddTag(AbilityShootTag);
	ActivationOwnedTags.AddTag(AbilityShootTag);
	
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("GameplayStatus.IsDead")));
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("GameplayEffect.ShootDelay")));
}

void UInsaneGA_Shoot::SingleFireRelease(float TimeHeld)
{
	UE_LOG(LogTemp, Warning, TEXT("Release"));
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UInsaneGA_Shoot::SR_SpawnSound_Implementation()
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), WeaponFireSound, GetAvatarActorFromActorInfo()->GetActorLocation());
}

void UInsaneGA_Shoot::Client_Features_Implementation(AActor* Target)
{
	AInsanePartyCharacter* Player = Cast<AInsanePartyCharacter>(GetAvatarActorFromActorInfo());
	if(IsValid(Player))
	{
		UInsaneInventorySystemComponent* PartyCharacterInventory = Cast<AInsanePlayerState>(Player->GetPlayerState())->GetInventorySystemComponent();
		AInsaneWeaponBase* AttachedWeapon = PartyCharacterInventory->GetAttachedWeapon(Player, PartyCharacterInventory->GetActiveSlotIndex());
		FGameplayTagContainer Tags;
		GetAbilitySystemComponentFromActorInfo()->GetOwnedGameplayTags(Tags);

		if(IsValid(PartyCharacterInventory), IsValid(AttachedWeapon))
		{
			if(Tags.HasTag(InsaneGameplayTags::GameplayStatus_Aiming))
			{
				UE_LOG(LogTemp, Warning, TEXT("1"));
				//add recoil in weapon data
				Player->IMP_Recoil(0.5f * 0.7f, 1.5f * 0.5f, 0.5f, 0.8f);
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), WeaponFireSound, Player->GetActorLocation());
				SR_SpawnSound();
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("0"));
				//add recoil in weapon data
				Player->IMP_Recoil(0.5f, 1.5f, 0.5f, 0.8f);
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), WeaponFireSound, Player->GetActorLocation());
				SR_SpawnSound();
			}
		}
	}
}

void UInsaneGA_Shoot::SR_SpawnProjectile_Implementation(AInsanePartyCharacter* PartyCharacter)
{
	FVector Location = PartyCharacter->GetFollowCamera()->GetForwardVector() * 500.f + PartyCharacter->GetFollowCamera()->GetComponentLocation();
	FRotator Rotation = PartyCharacter->GetFollowCamera()->GetComponentRotation();
	FTransform Transform;
	Transform.SetLocation(Location);
	Transform.SetRotation(Rotation.Quaternion());
	Transform.SetScale3D(FVector(1.f));
		
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		
	AInsaneProjectileBase* Projectile = GetWorld()->SpawnActorDeferred<AInsaneProjectileBase>(ProjectileClass, Transform, PartyCharacter,
		GetAvatarActorFromActorInfo()->GetInstigator(), ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	Projectile->FinishSpawning(Transform);
}

void UInsaneGA_Shoot::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                      const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                      const FGameplayEventData* TriggerEventData)
{

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
	}
	else
	{
		if (GetOwningActorFromActorInfo()->GetLocalRole() == ROLE_Authority && ProjectileClass != nullptr)
		{
			AInsanePartyCharacter* PartyCharacter = Cast<AInsanePartyCharacter>(GetAvatarActorFromActorInfo());
			if(!PartyCharacter)
			{
				EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
			}

			UInsaneInventorySystemComponent* PartyCharacterInventory = Cast<AInsanePlayerState>(PartyCharacter->GetPlayerState())->GetInventorySystemComponent();
			AInsaneWeaponBase* AttachedWeapon = PartyCharacterInventory->GetAttachedWeapon(PartyCharacter, PartyCharacterInventory->GetActiveSlotIndex());

			if(IsValid(AttachedWeapon) && IsValid(AttachedWeapon->WeaponData))
			{
				if(AttachedWeapon->MagazineInfo.CurrentFireMode == AttachedWeapon->WeaponData->WeaponData.SingleFireModeEffect
					&& PartyCharacterInventory->DecreaseAmmoInMagazine(AttachedWeapon))
				{
					Client_Features(GetAvatarActorFromActorInfo());
					Shoot(AttachedWeapon, GetAbilitySystemComponentFromActorInfo()->MakeEffectContext());
					UAbilityTask_WaitInputRelease* Task = UAbilityTask_WaitInputRelease::WaitInputRelease(this, true);
					Task->OnRelease.AddDynamic(this, &UInsaneGA_Shoot::SingleFireRelease);
					Task->ReadyForActivation();
				}
				else if(AttachedWeapon->MagazineInfo.CurrentFireMode == AttachedWeapon->WeaponData->WeaponData.FullAutoFireModeEffect
					&& PartyCharacterInventory->DecreaseAmmoInMagazine(AttachedWeapon))
				{
					Client_Features(GetAvatarActorFromActorInfo());
					Shoot(AttachedWeapon, GetAbilitySystemComponentFromActorInfo()->MakeEffectContext());
					EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
				}
				else
				{
					EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
				}
			}
		}

		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
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



void UInsaneGA_Shoot::Shoot(AInsaneWeaponBase* WeaponData, FGameplayEffectContextHandle Context)
{
	AInsanePartyCharacter* PartyCharacter = Cast<AInsanePartyCharacter>(GetAvatarActorFromActorInfo());
	if (!PartyCharacter)
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
	}

	TSubclassOf<UGameplayEffect> ShootDelayEffect = WeaponData->WeaponData->WeaponData.ShootDelayEffect;
	FGameplayEffectSpecHandle EffectSpec = MakeOutgoingGameplayEffectSpec(ShootDelayEffect, GetAbilityLevel());
	EffectSpec.Data.Get()->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("GameplayEffect.ShootDelay")), WeaponData->WeaponData->WeaponData.ShootDelay);
	//UE_LOG(LogTemp, Warning, TEXT("%f"), EffectSpec.Data.Get()->GetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("GameplayEffect.ShootDelay")), false, 0.f));
	GetAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToSelf(*EffectSpec.Data.Get());
	
	SR_SpawnProjectile(PartyCharacter);
}

