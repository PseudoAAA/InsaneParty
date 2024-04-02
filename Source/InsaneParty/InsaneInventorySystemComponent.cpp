// 2024, Pseudo / Ageev Daniil. All rights reserved ©


#include "InsaneInventorySystemComponent.h"
#include "InsaneParty.h"

// Sets default values for this component's properties
UInsaneInventorySystemComponent::UInsaneInventorySystemComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	
	InventoryWeaponData.SetNum(InventorySize);
}

void UInsaneInventorySystemComponent::BeginPlay()
{
	Super::BeginPlay();
	
	InventoryWeaponData.SetNum(InventorySize);
	//UE_LOG(InsaneInventoryLog, Warning, TEXT("Inventory max size is %d"), InventoryWeaponData.Max());
	//UE_LOG(InsaneInventoryLog, Warning, TEXT("Inventory data empty? bool: %d"), InventoryWeaponData[0] == nullptr);
}

void UInsaneInventorySystemComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
}


void UInsaneInventorySystemComponent::SetActiveSlotIndex(const int SlotIndex)
{
	ActiveSlotIndex = SlotIndex;
	OnActiveSlotIndexChanged.Broadcast(ActiveSlotIndex);
}

void UInsaneInventorySystemComponent::AddWeaponToInventory(UInsaneWeaponPrimaryDataAsset* WeaponToAdd)
{
	int EmptySlot = GetFirstEmptySlot();
	if(EmptySlot != IncorrectSlotIndex && IsUniqueWeapon(WeaponToAdd) && InventoryWeaponData[EmptySlot] == nullptr)
	{
		InventoryWeaponData[EmptySlot] = WeaponToAdd;
		UE_LOG(InsaneInventoryLog, Warning, TEXT("Weapon was added to inventory. Weapon name: %s"), *InventoryWeaponData[EmptySlot]->WeaponData.WeaponName.ToString());
	}
	else
	{
		UE_LOG(InsaneInventoryLog, Warning, TEXT("Can't add weapon to inventory. Incorrect slot index or not unique weapon"));
	}
}

void UInsaneInventorySystemComponent::ActivateWeaponInSlot()
{
	
}

bool UInsaneInventorySystemComponent::IsValidWeaponDataInSlot(const int SlotIndex)
{
	return SlotIndex != IncorrectSlotIndex; 
}

bool UInsaneInventorySystemComponent::IsUniqueWeapon(UInsaneWeaponPrimaryDataAsset* WeaponToCheck)
{
	UE_LOG(InsaneInventoryLog, Warning, TEXT("Is unique weapon in inventory? bool: %d"), !InventoryWeaponData.Contains(WeaponToCheck));
	return WeaponToCheck == nullptr ? false : !InventoryWeaponData.Contains(WeaponToCheck);
}


int UInsaneInventorySystemComponent::GetFirstEmptySlot()
{
	int SlotNum = 0;
	for(auto& Slot : InventoryWeaponData)
	{
		if(Slot == nullptr)
		{
			//UE_LOG(InsaneInventoryLog, Warning, TEXT("Slot is empty. SlotIndex: %d"), SlotNum);
			return SlotNum;
		}
		SlotNum++;
		//UE_LOG(InsaneInventoryLog, Warning, TEXT("Slot is not empty. SlotIndex: %d"), SlotNum);
	}
	return this->IncorrectSlotIndex;
}

int UInsaneInventorySystemComponent::GetActiveSlotIndex()
{
	return ActiveSlotIndex;
}

int UInsaneInventorySystemComponent::GetInventorySize() const	
{
	return InventoryWeaponData.Max();
}

TSubclassOf<AInsaneWeaponBase> UInsaneInventorySystemComponent::GetWeaponClass(const int SlotIndex)
{ 
	//UE_LOG(InsaneInventoryLog, Warning, TEXT("Can't get weapon class in slot %d"), InventoryWeaponData[SlotIndex] == nullptr);
	if(SlotIndex == IncorrectSlotIndex ? true : InventoryWeaponData[SlotIndex] == nullptr)
	{
		UE_LOG(InsaneInventoryLog, Warning, TEXT("Can't get weapon class in slot %d"), SlotIndex);
		return nullptr;
	}
	return InventoryWeaponData[SlotIndex]->WeaponData.Weapon;
}

UInsaneWeaponPrimaryDataAsset* UInsaneInventorySystemComponent::GetWeaponDataFromInventory(const int SlotIndex)
{
	if(IsValidWeaponDataInSlot(SlotIndex))
	{
		return InventoryWeaponData[SlotIndex];
	}
	else
	{
		return nullptr;
	}
}


