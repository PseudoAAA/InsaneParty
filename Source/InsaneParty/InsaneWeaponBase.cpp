// 2024, Pseudo / Ageev Daniil. All rights reserved ©


#include "InsaneWeaponBase.h"


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


// Called when the game starts or when spawned
void AInsaneWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	//UE_LOG(InsanePartyLog, Warning, TEXT("WeaponData->WeaponData.Weapon == this->StaticClass()? Bool: %d"), *WeaponData->WeaponData.Weapon == this->GetClass());
}