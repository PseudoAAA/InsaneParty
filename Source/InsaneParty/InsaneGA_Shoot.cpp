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
		if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
		{
			EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
		}
		else
		{
			//ProjectileSpawn(PartyCharacter, AttachedWeapon->WeaponData->WeaponData.Projectile, AttachedWeapon->WeaponData, GetAvatarActorFromActorInfo()->GetInstigator());
			FGameplayTagContainer Tags;
			GetAbilitySystemComponentFromActorInfo()->GetOwnedGameplayTags(Tags);
			if(Tags.HasTag(InsaneGameplayTags::GameplayStatus_Aiming))
			{
				UE_LOG(LogTemp, Warning, TEXT("Active Slot: %d"), PartyCharacterInventory->GetActiveSlotIndex());
				UE_LOG(LogTemp, Warning, TEXT("Weapon name: %s"), *AttachedWeapon->GetName());
				
				GetWorld()->GetTimerManager().SetTimer(ShootDelay, this, &UInsaneGA_Shoot::OnDelayEnd, AttachedWeapon->WeaponData->WeaponData.Properties.ShootDelay, false);
				//add recoil in weapon data
				PartyCharacter->IMP_Recoil(0.5f * 0.7f, 1.5f * 0.5f, 0.5f, 0.8f);
				//NO RECOIL   PartyCharacter->IMP_Recoil(0.0f, 0.f, 0.0f, 0.0f);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("0"));
				GetWorld()->GetTimerManager().SetTimer(ShootDelay, this, &UInsaneGA_Shoot::OnDelayEnd, AttachedWeapon->WeaponData->WeaponData.Properties.ShootDelay, false);
				//add recoil in weapon data
				PartyCharacter->IMP_Recoil(0.5f, 1.5f, 0.5f, 0.8f);
				//NO RECOIL    PartyCharacter->IMP_Recoil(0.0f, 0.f, 0.0f, 0.0f);
			}
		}
	}
	else
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
	}
}
//_Implementation
/*void UInsaneGA_Shoot::ProjectileSpawn(AInsanePartyCharacter* PartyCharacter, TSubclassOf<AInsaneProjectileBase> Projectile, UInsaneWeaponPrimaryDataAsset* WeaponData, APawn* PartyInstigator)
{
	UInsaneInventorySystemComponent* PartyCharacterInventory = CastChecked<AInsanePlayerState>(PartyCharacter->GetPlayerState())->GetInventorySystemComponent();
	AInsaneWeaponBase* AttachedWeapon = PartyCharacterInventory->GetAttachedWeapon(PartyCharacter, PartyCharacterInventory->GetActiveSlotIndex());
	FVector MuzzleLocation = Cast<AInsaneWeaponBase>(AttachedWeapon)->SkeletalMeshWeapon->GetBoneLocation("muzzle_end", EBoneSpaces::WorldSpace);
	FTransform Transform;
	if(AttachedWeapon)
	{
		//FVector MuzzleLocation = Cast<AInsaneWeaponBase>(AttachedWeapon)->SkeletalMeshWeapon->GetSocketLocation("muzzle_end");
		FVector Start = PartyCharacter->GetFollowCamera()->GetComponentLocation();
		FVector End = Start + PartyCharacter->GetFollowCamera()->GetForwardVector() * 99999.f;
		TArray<AActor*> ActorsToIgnore;
		ActorsToIgnore.Add(PartyCharacter);
		FHitResult HitResult;
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldDynamic));
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_PhysicsBody));
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));
		
		UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), Start, End, ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResult, true);
		//DrawDebugLine(GetWorld(), PartyCharacter->GetFollowCamera()->GetComponentLocation(), PartyCharacter->GetFollowCamera()->GetForwardVector()* 1500.f, FColor::Red, false, 5.f, 0.f, 1.f);
		FRotator MuzzleRotationToViewPoint = UKismetMathLibrary::FindLookAtRotation(MuzzleLocation, HitResult.Location);
		FVector TransformVector = Cast<AInsaneWeaponBase>(AttachedWeapon)->SkeletalMeshWeapon->GetBoneLocation("muzzle_end", EBoneSpaces::WorldSpace);
		TransformVector.Z = Cast<AInsaneWeaponBase>(AttachedWeapon)->SkeletalMeshWeapon->GetBoneLocation("muzzle_end", EBoneSpaces::WorldSpace).Z + Cast<APawn>(GetAvatarActorFromActorInfo())->GetBaseAimRotation().Pitch;
		Transform.SetLocation(TransformVector + Cast<APawn>(GetAvatarActorFromActorInfo())->GetBaseAimRotation().Vector());
		
		UE_LOG(LogTemp, Warning, TEXT("%s"), *MuzzleLocation.ToString());
		Transform.SetRotation(MuzzleRotationToViewPoint.Quaternion());
		Transform.SetScale3D(FVector(1.f));
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		if(K2_HasAuthority())
		{
			UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), Cast<AInsaneWeaponBase>(AttachedWeapon)->SkeletalMeshWeapon->GetBoneLocation("muzzle_end", EBoneSpaces::WorldSpace) + Cast<APawn>(GetAvatarActorFromActorInfo())->GetBaseAimRotation().Vector(), End, ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResult, true, FLinearColor::Black);
			
			AInsaneProjectileBase* ProjectileToSpawn = GetWorld()->SpawnActorDeferred<AInsaneProjectileBase>(Projectile, Transform, PartyCharacter,
				PartyInstigator, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
			ProjectileToSpawn->ProjectileMovementComponent->InitialSpeed = WeaponData->WeaponData.Properties.ProjectileSpeed;
			ProjectileToSpawn->ProjectileMovementComponent->ProjectileGravityScale = WeaponData->WeaponData.Properties.ProjectileGravityScale;
			ProjectileToSpawn->ProjectileData = WeaponData;
			ProjectileToSpawn->FinishSpawning(Transform);
		}
	}	
}*/

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

