// 2024, Pseudo / Ageev Daniil. All rights reserved ©

#pragma once

#include "Abilities/GameplayAbility.h"
#include "Engine/StaticMesh.h"
#include "InsaneData.generated.h"

class AInsaneWeaponBase;

UENUM(BlueprintType)
enum class EInsaneAbilityInputID : uint8
{
	// 0 None
	None			UMETA(DisplayName = "None"),
	// 1 Confirm
	Confirm			UMETA(DisplayName = "Confirm"),
	// 2 Cancel
	Cancel			UMETA(DisplayName = "Cancel"),
};


USTRUCT(BlueprintType)
struct FWeapon
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName WeaponName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UGameplayAbility> Ability;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AInsaneWeaponBase> Weapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage = 0.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Range = 15000.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BulletSpeed = 5000.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BulletGravityScale = 1.f;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanAutoFire = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UGameplayEffect> SingleFireModeEffect;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UGameplayEffect> FullAutoFireModeEffect;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Thumbnail;
};

USTRUCT(BlueprintType)
struct FWeaponDefaultMagazine
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MagazineAmmoCount = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxAmmoCount = 0;
	
};

USTRUCT(BlueprintType)
struct FWeaponMagazineInfo
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CurrentAmmoCount = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int AllAmmoCount = 0;
	
};

USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UInsaneWeaponPrimaryDataAsset* WeaponDataAsset = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FWeaponMagazineInfo WeaponMagazineInfo;
};

