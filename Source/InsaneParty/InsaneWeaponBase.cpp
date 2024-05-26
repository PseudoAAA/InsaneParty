// 2024, Pseudo / Ageev Daniil. All rights reserved ©

#include "InsaneWeaponBase.h"

#include "InsaneGameplayTags.h"
#include "InsanePartyCharacter.h"
#include "InsaneProjectileBase.h"

// Sets default values
AInsaneWeaponBase::AInsaneWeaponBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	bReplicates = true;
	SetReplicatingMovement(true);
	WeaponData = nullptr;

	SkeletalMeshWeapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh")); 
}



void AInsaneWeaponBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(AInsaneWeaponBase, MagazineInfo, COND_InitialOrOwner);
}


void AInsaneWeaponBase::ReloadWeapon()
{
	int CurrentAmmoCount = this->MagazineInfo.CurrentAmmoCount;
	int MagazineAmmoCount = this->WeaponData->WeaponMagazineData.MagazineAmmoCount;
	int AmmoToAdd = MagazineAmmoCount - CurrentAmmoCount;
	if(this->MagazineInfo.CurrentAllAmmoCount >= AmmoToAdd && CurrentAmmoCount < MagazineAmmoCount)
	{
		this->MagazineInfo.CurrentAmmoCount += AmmoToAdd;
		this->MagazineInfo.CurrentAllAmmoCount -= AmmoToAdd;
	}
	else if(CurrentAmmoCount < MagazineAmmoCount)
	{
		this->MagazineInfo.CurrentAmmoCount += this->MagazineInfo.CurrentAllAmmoCount;
		this->MagazineInfo.CurrentAllAmmoCount -= this->MagazineInfo.CurrentAllAmmoCount;
	}
	else
	{
		UE_LOG(InsaneInventoryLog, Warning, TEXT("Weapon magazine is full"));
	}
}

bool AInsaneWeaponBase::SwitchFireMode()
{
	if(IsValid(this->WeaponData))
	{
		if(this->WeaponData->WeaponData.Properties .bCanAutoFire)
		{
			this->MagazineInfo.CurrentFireMode = this->MagazineInfo.CurrentFireMode == this->WeaponData->WeaponData.SingleFireModeEffect
			? this->WeaponData->WeaponData.FullAutoFireModeEffect
			: this->WeaponData->WeaponData.SingleFireModeEffect;
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}

}

TSubclassOf<UGameplayEffect> AInsaneWeaponBase::GetCurrentFireMode()
{
	if(IsValid(this->MagazineInfo.CurrentFireMode))
	{
		return this->MagazineInfo.CurrentFireMode;
	}
	else
	{
		return nullptr;
	}
}


// Called when the game starts or when spawned
void AInsaneWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(InsanePartyLog, Warning, TEXT("WeaponData->WeaponData.Weapon == this->StaticClass()? Bool: %d"), *WeaponData->WeaponData.Weapon == this->GetClass());
}