// 2024, Pseudo / Ageev Daniil. All rights reserved ©

#pragma once

#include "CoreMinimal.h"
#include "InsaneParty.h"
#include "GameFramework/Actor.h"
#include "InsaneWeaponBase.generated.h"


class UInsaneThrowablePrimaryDataAsset;

UCLASS()
class INSANEPARTY_API AInsaneWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInsaneWeaponBase();
	

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	//FWeapon GetWeaponData() const;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InsaneParty|Weapon Data")
	UInsaneWeaponPrimaryDataAsset* WeaponData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "InsaneParty|Weapon Data", meta=(ExposeOnSpawn=true))
	FWeaponCurrentMagazineInfo MagazineInfo;
	
	UFUNCTION(BlueprintCallable, Category = "InsaneParty|Weapon")
	void ReloadWeapon();

	UFUNCTION(BlueprintCallable, Category = "InsaneParty|Weapon")
	bool SwitchFireMode();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "InsaneParty|Weapon")
	bool bCanPickup;
	
	UFUNCTION(BlueprintCallable, Category = "InsaneParty|Weapon")
	TSubclassOf<UGameplayEffect> GetCurrentFireMode();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
