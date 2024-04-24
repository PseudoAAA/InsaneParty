// 2024, Pseudo / Ageev Daniil. All rights reserved ©

#pragma once

#include "InsaneData.generated.h"

class UGameplayEffect;
class UGameplayAbility;
class AInsaneWeaponBase;
class AInsaneProjectileBase;

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
	float ProjectileSpeed = 5000.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ProjectileGravityScale = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ShootDelay = 0.2f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanAutoFire = false;
};

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	//0
	None,
	//1
	Gun,
	//2
	Throwable
};

//TODO ENUM OF FIRE MODE TYPE
UENUM(BlueprintType)
enum class EFireMode : uint8
{
	//0
	None,
	//1
	Single,
	//2
	FullAuto
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
	EWeaponType WeaponType = EWeaponType::None;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AInsaneProjectileBase> Projectile;

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
struct FWeaponMagazineData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MagazineAmmoCount = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MagazineMaxAmmoCount = 0;
	
};

USTRUCT(BlueprintType)
struct FWeaponCurrentMagazineInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CurrentAmmoCount = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CurrentAllAmmoCount = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UGameplayEffect> CurrentFireMode = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EFireMode FireMode = EFireMode::None;
	
};

USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UInsaneWeaponPrimaryDataAsset* WeaponDataAsset = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FWeaponCurrentMagazineInfo CurrentMagazineInfo;

};

USTRUCT(BlueprintType)
struct FWeaponSoundData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* FireSound;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* ReloadingSound;

};


