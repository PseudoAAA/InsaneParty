// 2024, Pseudo / Ageev Daniil. All rights reserved ©


#include "InsaneWeaponBase.h"


// Sets default values
AInsaneWeaponBase::AInsaneWeaponBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	this->bReplicates = true;
	this->SetReplicatingMovement(true);

	
    
	
	WeaponData = nullptr;

	//TODO WeaponData.WeaponClass = this
	//WeaponData->WeaponData.Weapon = this->StaticClass();
}

/*FWeapon* AInsaneWeaponBase::GetWeaponData() const
{
	if (WeaponData != nullptr)
	{
		return WeaponData;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("%s has bad WeaponData"), *GetDebugName(this));
	return nullptr;
}*/

// Called when the game starts or when spawned
void AInsaneWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	//UE_LOG(InsanePartyLog, Warning, TEXT("WeaponData->WeaponData.Weapon == this->StaticClass()? Bool: %d"), *WeaponData->WeaponData.Weapon == this->GetClass());
}