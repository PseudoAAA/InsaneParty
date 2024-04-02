// 2024, Pseudo / Ageev Daniil. All rights reserved ©

#pragma once

#include "CoreMinimal.h"
#include "InsaneWeaponPrimaryDataAsset.h"
#include "Components/ActorComponent.h"
#include "InsaneInventorySystemComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FActiveSlotIndexChanged, int, ActiveSlotIndex);

UCLASS()
class INSANEPARTY_API UInsaneInventorySystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInsaneInventorySystemComponent();
	
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	const uint8 InventorySize = 3;
	const int IncorrectSlotIndex = -1;
	int ActiveSlotIndex = -1;

	UPROPERTY(BlueprintAssignable, Category = "GASDocumentation|GDCharacter")
	FActiveSlotIndexChanged OnActiveSlotIndexChanged;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "InsaneParty|InsanePartyCharacter|Inventory")
	TArray<UInsaneWeaponPrimaryDataAsset*> InventoryWeaponData;
	
	UFUNCTION(BlueprintCallable, Category = "InsaneParty|InsanePartyCharacter|Inventory")
	void SetActiveSlotIndex(int SlotIndex);

	UFUNCTION(BlueprintCallable, BlueprintCallable, Category = "InsaneParty|InsanePartyCharacter|Inventory")
	void AddWeaponToInventory(UInsaneWeaponPrimaryDataAsset* WeaponToAdd);

	UFUNCTION(BlueprintCallable, Category = "InsaneParty|InsanePartyCharacter|Inventory")
	void ActivateWeaponInSlot();
	
	UFUNCTION(BlueprintCallable, Category = "InsaneParty|InsanePartyCharacter|Inventory")
	bool IsValidWeaponDataInSlot(const int SlotIndex);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "InsaneParty|InsanePartyCharacter|Inventory")
	bool IsUniqueWeapon(UInsaneWeaponPrimaryDataAsset* WeaponToCheck);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "InsaneParty|InsanePartyCharacter|Inventory")
	int GetFirstEmptySlot();
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "InsaneParty|InsanePartyCharacter|Inventory")
	int GetActiveSlotIndex();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "InsaneParty|InsanePartyCharacter|Inventory")
	int GetInventorySize() const;
	
	UFUNCTION(BlueprintCallable, Category = "InsaneParty|InsanePartyCharacter|Inventory")
	TSubclassOf<AInsaneWeaponBase> GetWeaponClass(const int SlotIndex);
	
	UFUNCTION(BlueprintCallable, Category = "InsaneParty|InsanePartyCharacter|Inventory")
	UInsaneWeaponPrimaryDataAsset* GetWeaponDataFromInventory(const int SlotIndex);

	
};
