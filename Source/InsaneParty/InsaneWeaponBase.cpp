// 2024, Pseudo / Ageev Daniil. All rights reserved ©


#include "InsaneWeaponBase.h"

#include "InterchangeResult.h"


// Sets default values
AInsaneWeaponBase::AInsaneWeaponBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	bReplicates = true;
	SetReplicatingMovement(true);
	
	WeaponData = nullptr;
}

void AInsaneWeaponBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AInsaneWeaponBase, MagazineInfo);
}


void AInsaneWeaponBase::ReloadWeapon()
{
	int CurrentAmmoCount = this->MagazineInfo.CurrentAmmoCount;
	int MagazineAmmoCount = this->WeaponData->WeaponMagazineData.MagazineAmmoCount;
	int AmmoToAdd = MagazineAmmoCount - CurrentAmmoCount;
	if(this->MagazineInfo.AllAmmoCount >= AmmoToAdd && CurrentAmmoCount < MagazineAmmoCount)
	{
		this->MagazineInfo.CurrentAmmoCount += AmmoToAdd;
		this->MagazineInfo.AllAmmoCount -= AmmoToAdd;
	}
	else if(CurrentAmmoCount < MagazineAmmoCount)
	{
		this->MagazineInfo.CurrentAmmoCount += this->MagazineInfo.AllAmmoCount;
		this->MagazineInfo.AllAmmoCount -= this->MagazineInfo.AllAmmoCount;
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