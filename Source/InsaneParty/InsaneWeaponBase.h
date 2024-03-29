// 2024, Pseudo / Ageev Daniil. All rights reserved ©

#pragma once

#include "CoreMinimal.h"
#include "InsaneWeaponPrimaryDataAsset.h"
#include "InsaneParty.h"
#include "GameFramework/Actor.h"
#include "InsaneWeaponBase.generated.h"

UCLASS()
class INSANEPARTY_API AInsaneWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInsaneWeaponBase();

	
	//FWeapon GetWeaponData() const;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InsaneParty|WeaponData")
	UInsaneWeaponPrimaryDataAsset* WeaponData;
	
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InsaneParty|WeaponData")
	FWeapon WeaponData;
	*/

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



};
