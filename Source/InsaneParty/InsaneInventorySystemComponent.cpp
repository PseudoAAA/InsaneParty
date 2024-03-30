// 2024, Pseudo / Ageev Daniil. All rights reserved ©


#include "InsaneInventorySystemComponent.h"

// Sets default values for this component's properties
UInsaneInventorySystemComponent::UInsaneInventorySystemComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	
	InventoryWeaponData.SetNum(InventorySize);
}

void UInsaneInventorySystemComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

TSubclassOf<AInsaneWeaponBase> UInsaneInventorySystemComponent::GetWeaponClass(const int32 SlotIndex)
{ 
	//UE_LOG(LogInsaneInventory, Warning, TEXT("Can't get weapon class in slot %d"), InventoryWeaponData[SlotIndex] == nullptr);
	if(SlotIndex != IncorrectSlotIndex && InventoryWeaponData[SlotIndex] == nullptr )
	{
		UE_LOG(LogInsaneInventory, Warning, TEXT("Can't get weapon class in slot %d"), SlotIndex);
		return nullptr;
	}
	return InventoryWeaponData[SlotIndex]->WeaponData.Weapon;
}

UInsaneWeaponPrimaryDataAsset* UInsaneInventorySystemComponent::GetWeaponDataFromInventory(const int32 SlotIndex)
{
	if(IsValidWeaponDataInSlot(SlotIndex))
	{
		return InventoryWeaponData[SlotIndex];
	}
	return nullptr;
}

int32 UInsaneInventorySystemComponent::GetFirstEmptySlot()
{
	int SlotNum = 0;
	for(auto& Slot : InventoryWeaponData)
	{
		if(Slot == nullptr)
		{
			//UE_LOG(LogInsaneInventory, Warning, TEXT("Slot is empty. SlotIndex: %d"), SlotNum);
			return SlotNum;
		}
		SlotNum++;
		//UE_LOG(LogInsaneInventory, Warning, TEXT("Slot is not empty. SlotIndex: %d"), SlotNum);
	}
	return IncorrectSlotIndex;
}

bool UInsaneInventorySystemComponent::IsValidWeaponDataInSlot(const int32 SlotIndex)
{
	return InventoryWeaponData[SlotIndex] != nullptr;
}

int32 UInsaneInventorySystemComponent::GetInventorySize() const	
{
	return this->InventoryWeaponData.Max();
}

bool UInsaneInventorySystemComponent::IsUniqueWeapon(UInsaneWeaponPrimaryDataAsset* WeaponToCheck)
{
	UE_LOG(LogInsaneInventory, Warning, TEXT("Is unique weapon in inventory? bool: %d"), !InventoryWeaponData.Contains(WeaponToCheck));
	return WeaponToCheck == nullptr ? false : !InventoryWeaponData.Contains(WeaponToCheck);
}

void UInsaneInventorySystemComponent::AddWeaponToInventory_Implementation(UInsaneWeaponPrimaryDataAsset* WeaponToAdd)
{
	int32 EmptySlot = GetFirstEmptySlot();
	if(EmptySlot != IncorrectSlotIndex && IsUniqueWeapon(WeaponToAdd) && InventoryWeaponData[EmptySlot] == nullptr)
	{
		InventoryWeaponData[EmptySlot] = WeaponToAdd;
		UE_LOG(LogInsaneInventory, Warning, TEXT("Weapon was added to inventory. Weapon name: %s"), *InventoryWeaponData[EmptySlot]->WeaponData.WeaponName.ToString());
	}
	UE_LOG(LogInsaneInventory, Warning, TEXT("Can't add weapon to inventory. Incorrect slot index"));
}

void UInsaneInventorySystemComponent::ActivateWeaponInSlot()
{
	
}

// Called when the game starts
void UInsaneInventorySystemComponent::BeginPlay()
{
	Super::BeginPlay();
	
	InventoryWeaponData.SetNum(InventorySize);
	//UE_LOG(LogInsaneInventory, Warning, TEXT("Inventory max size is %d"), InventoryWeaponData.Max());
	//UE_LOG(LogInsaneInventory, Warning, TEXT("Inventory data empty? bool: %d"), InventoryWeaponData[0] == nullptr);
}


