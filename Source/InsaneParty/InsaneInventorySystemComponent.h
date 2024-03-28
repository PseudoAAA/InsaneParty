// 2024, Pseudo / Ageev Daniil. All rights reserved ©

#pragma once

#include "CoreMinimal.h"
#include "InsaneParty.h"
#include "InsaneWeaponPrimaryDataAsset.h"
#include "Components/ActorComponent.h"
#include "InsaneInventorySystemComponent.generated.h"

UCLASS()
class INSANEPARTY_API UInsaneInventorySystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInsaneInventorySystemComponent();
	

	const uint8 InventorySize = 3;
	const int32 IncorrectSlotIndex = -1;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "InsaneParty|InsanePartyCharacter|Inventory")
	TArray<UInsaneWeaponPrimaryDataAsset*> InventoryWeaponData;

	UFUNCTION(BlueprintCallable, Category = "InsaneParty|InsanePartyCharacter|Inventory")
	TSubclassOf<AInsaneWeaponBase> GetWeaponClass(const int32 SlotIndex); 
	
	UFUNCTION(BlueprintCallable, Category = "InsaneParty|InsanePartyCharacter|Inventory")
	int32 GetFirstEmptySlot();
	
	UFUNCTION(BlueprintCallable, Category = "InsaneParty|InsanePartyCharacter|Inventory")
	int32 GetInventorySize() const;

	UFUNCTION(BlueprintCallable, Category = "InsaneParty|InsanePartyCharacter|Inventory")
	bool IsUniqueWeapon(UInsaneWeaponPrimaryDataAsset* WeaponToCheck);
	
	UFUNCTION(BlueprintCallable, Category = "InsaneParty|InsanePartyCharacter|Inventory")
	bool AddWeaponToInventory(UInsaneWeaponPrimaryDataAsset* WeaponToAdd);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

};
