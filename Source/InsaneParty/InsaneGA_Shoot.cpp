// 2024, Pseudo / Ageev Daniil. All rights reserved ©


#include "InsaneGA_Shoot.h"

#include "InsaneGameplayTags.h"
#include "InsanePartyCharacter.h"
#include "InsaneProjectileBase.h"
#include "NativeGameplayTags.h"
#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"




UInsaneGA_Shoot::UInsaneGA_Shoot()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	
	FGameplayTag AbilityShootTag = FGameplayTag::RequestGameplayTag(FName("PlayerActions.Shoot"));
	AbilityTags.AddTag(AbilityShootTag);
	ActivationOwnedTags.AddTag(AbilityShootTag);
	
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("GameplayStatus.IsDead")));
}


void UInsaneGA_Shoot::Features(AActor* Target)
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
			if(AttachedWeapon->MagazineInfo.CurrentAmmoCount > 0)
			{
				if(Tags.HasTag(InsaneGameplayTags::GameplayStatus_Aiming))
				{
					UE_LOG(LogTemp, Warning, TEXT("1"));
					GetWorld()->GetTimerManager().SetTimer(ShootDelay, this, &UInsaneGA_Shoot::OnDelayEnd, AttachedWeapon->WeaponData->WeaponData.ShootDelay, false);
					//add recoil in weapon data
					Player->IMP_Recoil(0.5f * 0.7f, 1.5f * 0.5f, 0.5f, 0.8f);
					UGameplayStatics::PlaySoundAtLocation(GetWorld(), WeaponFireSound, Player->GetActorLocation());
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("0"));
					GetWorld()->GetTimerManager().SetTimer(ShootDelay, this, &UInsaneGA_Shoot::OnDelayEnd, AttachedWeapon->WeaponData->WeaponData.ShootDelay, false);
					//add recoil in weapon data
					Player->IMP_Recoil(0.5f, 1.5f, 0.5f, 0.8f);
					UGameplayStatics::PlaySoundAtLocation(GetWorld(), WeaponFireSound, Player->GetActorLocation());
				}
			}
			else
			{
				EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
			}
		}
		else
		{
			EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
		}
	}
	else
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
	}
}

void UInsaneGA_Shoot::SR_Features_Implementation(AInsanePartyCharacter* PartyCharacter)
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

	Features(GetAvatarActorFromActorInfo());
	
	AInsanePartyCharacter* PartyCharacter = CastChecked<AInsanePartyCharacter>(GetAvatarActorFromActorInfo());
	if(!PartyCharacter)
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
	}

	UInsaneInventorySystemComponent* PartyCharacterInventory = CastChecked<AInsanePlayerState>(PartyCharacter->GetPlayerState())->GetInventorySystemComponent();
	AInsaneWeaponBase* AttachedWeapon = PartyCharacterInventory->GetAttachedWeapon(PartyCharacter, PartyCharacterInventory->GetActiveSlotIndex());
	PartyCharacterInventory->DecreaseAmmoInMagazine(AttachedWeapon);
	
	if(IsValid(AttachedWeapon) && IsValid(AttachedWeapon->WeaponData))
	{
		if(AttachedWeapon->MagazineInfo.CurrentAmmoCount > 0)
		{
			GetWorld()->GetTimerManager().SetTimer(ShootDelay, this, &UInsaneGA_Shoot::OnDelayEnd, AttachedWeapon->WeaponData->WeaponData.ShootDelay, false);
			SR_Features(PartyCharacter);
		}
		else
		{
			EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
		}
	}
	else
	{
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

	if(AttachedWeapon->MagazineInfo.CurrentFireMode == AttachedWeapon->WeaponData->WeaponData.SingleFireModeEffect)
	{
		Task->OnRelease.AddDynamic(this, &UInsaneGA_Shoot::SingleFireRelease);
		Task->ReadyForActivation();
	}
	else
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
	}
}


