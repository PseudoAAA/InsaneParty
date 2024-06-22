// 2024, Pseudo / Ageev Daniil. All rights reserved ©


#include "InsaneInventorySystemComponent.h"
#include "InsaneParty.h"

// Sets default values for this component's properties
UInsaneInventorySystemComponent::UInsaneInventorySystemComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	
	InventoryWeaponData.SetNum(InventorySize);
	InventoryWeapon.SetNum(InventorySize);
}

void UInsaneInventorySystemComponent::BeginPlay()
{
	Super::BeginPlay();
	
	InventoryWeaponData.SetNum(InventorySize);
	InventoryWeapon.SetNum(InventorySize);
	//UE_LOG(InsaneInventoryLog, Warning, TEXT("Inventory max size is %d"), InventoryWeaponData.Max());
	//UE_LOG(InsaneInventoryLog, Warning, TEXT("Inventory data empty? bool: %d"), InventoryWeaponData[0] == nullptr);
}

void UInsaneInventorySystemComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(UInsaneInventorySystemComponent, ActiveSlotIndex);
	DOREPLIFETIME(UInsaneInventorySystemComponent, InventoryWeaponData);
	DOREPLIFETIME(UInsaneInventorySystemComponent, InventoryWeapon);
}


void UInsaneInventorySystemComponent::SetActiveSlotIndex(const int SlotIndex)
{
	ActiveSlotIndex = SlotIndex;
	
}

void UInsaneInventorySystemComponent::AddWeaponToInventory(UInsaneWeaponPrimaryDataAsset* WeaponToAdd, FWeaponData WeaponMagazineInfo)
{
	int EmptySlot = GetFirstEmptySlot();
	UE_LOG(InsaneInventoryLog, Warning, TEXT("First empty slot %d"), EmptySlot);
	if(EmptySlot != IncorrectSlotIndex && IsUniqueWeapon(WeaponToAdd) && InventoryWeaponData[EmptySlot] == nullptr)
	{
		InventoryWeaponData[EmptySlot] = WeaponToAdd;
		InventoryWeapon[EmptySlot] = WeaponMagazineInfo;
		//UE_LOG(InsaneInventoryLog, Warning, TEXT("Weapon was added to inventory. Weapon name: %s"), *InventoryWeaponData[EmptySlot]->WeaponData.WeaponName.ToString());
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
	if(SlotIndex == IncorrectSlotIndex)
	{
		return false;
	}
	if(InventoryWeapon[SlotIndex].WeaponDataAsset == nullptr)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void UInsaneInventorySystemComponent::ClearInventory_Implementation(AActor* Actor)
{
	AInsaneWeaponBase* AttachedWeapon = GetAttachedWeapon(Actor, GetActiveSlotIndex());
	
	if(IsValid(AttachedWeapon))
	{
		AttachedWeapon->Destroy();
		//DespawnAttachedActor(AttachedWeapon, GetActiveSlotIndex());
		GEngine->AddOnScreenDebugMessage(0, 3, FColor::Black, TEXT("Destroyed"));
	}
	
	for (int i = 0; i < InventoryWeaponData.Num(); ++i)
	{
		InventoryWeaponData[i] = nullptr;
	}

	TArray<FWeaponData> NewWeaponData;
	NewWeaponData.SetNum(3);
	InventoryWeapon = NewWeaponData;
	SetActiveSlotIndex(-1);
}

bool UInsaneInventorySystemComponent::IsUniqueWeapon(UInsaneWeaponPrimaryDataAsset* WeaponToCheck)
{
	for(auto &Item : InventoryWeapon)
	{
		if (Item.WeaponDataAsset == WeaponToCheck)
		{
			return false;
		}
	}
	return true;
}


int UInsaneInventorySystemComponent::GetFirstEmptySlot()
{
	int SlotNum = 0;
	for(auto& Slot : InventoryWeapon)
	{
		if(Slot.WeaponDataAsset == nullptr)
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

AInsaneWeaponBase* UInsaneInventorySystemComponent::GetAttachedWeapon(AActor* Actor, int ActiveSlotIndexToCheckWeapon)
{
	
	TArray<AActor*> AttachedActors;
	Actor->GetAttachedActors(AttachedActors);
	TSubclassOf<AInsaneWeaponBase> Weapon = GetWeaponClass(ActiveSlotIndexToCheckWeapon);

	if(Weapon != nullptr)
	{
		for(auto ActorA : AttachedActors)
		{
			if (UKismetMathLibrary::ClassIsChildOf(Weapon,ActorA->GetClass()))
			{
				AInsaneWeaponBase* WeaponActor = Cast<AInsaneWeaponBase>(ActorA);
				//UE_LOG(LogTemp, Warning, TEXT("%s"), *WeaponActor->GetFName().ToString());
				return WeaponActor;
			}
		}
	}

	return nullptr;
}

void UInsaneInventorySystemComponent::DespawnAttachedActor(AActor* Actor, int ActiveSlotIndexToCheckWeapon)
{
	TArray<AActor*> AttachedActors;
	Actor->GetAttachedActors(AttachedActors);
	TSubclassOf<AInsaneWeaponBase> Weapon = GetWeaponClass(ActiveSlotIndexToCheckWeapon);

	if(Weapon != nullptr)
	{
		for(auto ActorA : AttachedActors)
		{
			if (UKismetMathLibrary::ClassIsChildOf(Weapon,ActorA->GetClass()) )
			{
				ActiveSlotIndex = IncorrectSlotIndex;
				ActorA->SetLifeSpan(0.01f);
				break;
			}
		}
	}
}

TSubclassOf<AInsaneWeaponBase> UInsaneInventorySystemComponent::GetWeaponClass(const int SlotIndex)
{ 
	//UE_LOG(InsaneInventoryLog, Warning, TEXT("Can't get weapon class in slot %d"), InventoryWeaponData[SlotIndex] == nullptr);
	if(SlotIndex == IncorrectSlotIndex ? true : InventoryWeapon[SlotIndex].WeaponDataAsset == nullptr)
	{
		if(!SlotIndex == IncorrectSlotIndex) UE_LOG(InsaneInventoryLog, Warning, TEXT("Can't get weapon class in slot %d"), SlotIndex);
		return nullptr;
	}
	return InventoryWeapon[SlotIndex].WeaponDataAsset->WeaponData.WeaponClass;
}

FWeaponData UInsaneInventorySystemComponent::GetWeaponDataFromInventory(const int SlotIndex)
{
	if(IsValidWeaponDataInSlot(SlotIndex))
	{
		return InventoryWeapon[SlotIndex];
	}
	return *new FWeaponData;
}

void UInsaneInventorySystemComponent::SetAttachedWeaponInfoInInventory(AInsaneWeaponBase* Weapon, const int SlotIndex)
{
	if(IsValid(Weapon) && SlotIndex != IncorrectSlotIndex)
	{
		InventoryWeapon[SlotIndex].CurrentMagazineInfo = Weapon->MagazineInfo;
	}
	else
	{
		if(IsValid(Weapon)) UE_LOG(InsaneInventoryLog, Warning, TEXT("Setting attached weapon info was failed"));
	}
}


bool UInsaneInventorySystemComponent::DecreaseAmmoInMagazine(AInsaneWeaponBase* Weapon)
{
	if(IsValid(Weapon) && Weapon->MagazineInfo.CurrentAmmoCount > 0)
	{
		Weapon->MagazineInfo.CurrentAmmoCount -= 1.f;
		return true;
	}
	return false;
}





