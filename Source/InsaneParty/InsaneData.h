// 2024, Pseudo / Ageev Daniil. All rights reserved ©

#pragma once

#include "Engine/StaticMesh.h"
#include "InsaneData.generated.h"

class UGameplayEffect;
class UGameplayAbility;
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
	// 3 LMB
	Shoot 			UMETA(DisplayName = "Shoot"),
	// 4 RMB
	Aiming			UMETA(DisplayName = "Aiming"),
	// 5 E
	Interact		UMETA(DisplayName = "Interact"),
	// 6 B
	SwitchFireMode	UMETA(DisplayName = "SwitchFireMode"),
	// 7 1
	SelectFirstSlot	UMETA(DisplayName = "SelectFirstSlot"),
	// 8 2
	SelectSecondSlot UMETA(DisplayName = "SelectSecondSlot"),
	// 9 3
	SelectThirdSlot	UMETA(DisplayName = "SelectThirdSlot"),
	//10 R
	Reload			UMETA(Displayname = "Reload")
};




USTRUCT(BlueprintType)
struct FWeaponProperties 
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage = 0.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Range = 15000.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BulletSpeed = 5000.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BulletGravityScale = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ShootDelay = 0.2f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanAutoFire = false;
};

USTRUCT(BlueprintType)
struct FWeapon
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName WeaponName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UGameplayAbility> Ability;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<UGameplayEffect> AbilityEffect;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AInsaneWeaponBase> WeaponClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> Projectile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UGameplayEffect> SingleFireModeEffect;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UGameplayEffect> FullAutoFireModeEffect;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FWeaponProperties Properties;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Thumbnail;
};

USTRUCT(BlueprintType)
struct FWeaponDefaultMagazine
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MagazineAmmoCount = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxAmmoCount = 0;
	
};

USTRUCT(BlueprintType)
struct FWeaponMagazineInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CurrentAmmoCount = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int AllAmmoCount = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UGameplayEffect> CurrentFireMode = nullptr;
	
};

USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UInsaneWeaponPrimaryDataAsset* WeaponDataAsset = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FWeaponMagazineInfo WeaponMagazineInfo;
};

USTRUCT(BlueprintType)
struct FWeaponSoundData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* ShootSound;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* ReloadingSound;

};

USTRUCT(BlueprintType)
struct FThrowable
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ThrowableName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UGameplayAbility> Ability;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UGameplayEffect> AbilityEffect;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AInsaneWeaponBase> ThrowableClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> Projectile;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Thumbnail;
};