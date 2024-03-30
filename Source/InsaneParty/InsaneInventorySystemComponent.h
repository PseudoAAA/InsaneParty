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

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	const uint8 InventorySize = 3;
	const int32 IncorrectSlotIndex = -1;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "InsaneParty|InsanePartyCharacter|Inventory")
	TArray<UInsaneWeaponPrimaryDataAsset*> InventoryWeaponData;
	
	UFUNCTION(BlueprintCallable, Category = "InsaneParty|InsanePartyCharacter|Inventory")
	TSubclassOf<AInsaneWeaponBase> GetWeaponClass(const int32 SlotIndex);
	
	UFUNCTION(BlueprintCallable, Category = "InsaneParty|InsanePartyCharacter|Inventory")
	UInsaneWeaponPrimaryDataAsset* GetWeaponDataFromInventory(const int32 SlotIndex);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "InsaneParty|InsanePartyCharacter|Inventory")
	int32 GetFirstEmptySlot();

	UFUNCTION(BlueprintCallable, Category = "InsaneParty|InsanePartyCharacter|Inventory")
	bool IsValidWeaponDataInSlot(const int32 SlotIndex);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "InsaneParty|InsanePartyCharacter|Inventory")
	int32 GetInventorySize() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "InsaneParty|InsanePartyCharacter|Inventory")
	bool IsUniqueWeapon(UInsaneWeaponPrimaryDataAsset* WeaponToCheck);
	
	UFUNCTION(NetMulticast, Reliable, BlueprintCallable, Category = "InsaneParty|InsanePartyCharacter|Inventory")
	void AddWeaponToInventory(UInsaneWeaponPrimaryDataAsset* WeaponToAdd);
	

	UFUNCTION(BlueprintCallable, Category = "InsaneParty|InsanePartyCharacter|Inventory")
	void ActivateWeaponInSlot();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

};
