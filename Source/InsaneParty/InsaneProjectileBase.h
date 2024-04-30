// 2024, Pseudo / Ageev Daniil. All rights reserved ©

#pragma once

#include "CoreMinimal.h"
#include "InsaneData.h"
#include "GameFramework/Actor.h"
#include "InsaneProjectileBase.generated.h"

struct FWeaponSoundData;
class UInsaneWeaponPrimaryDataAsset;
class UGameplayEffect;
class UProjectileMovementComponent;
class UCapsuleComponent;

UCLASS()
class INSANEPARTY_API AInsaneProjectileBase : public AActor
{
	GENERATED_BODY()

public:
	AInsaneProjectileBase();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCapsuleComponent* ProjectileCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UProjectileMovementComponent* ProjectileMovementComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated,  meta = (ExposeOnSpawn = true))
	UInsaneWeaponPrimaryDataAsset* ProjectileData;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, meta = (ExposeOnSpawn = true))
	FWeaponSoundData ProjectileSoundData;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FHitResult HitResult;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* ProjectileOwner;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* OverlapActor;

	//TEMP GE
	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayEffect> GE_Damaging;
	
	/*UFUNCTION( )
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, 
								AActor* OtherActor, 
								UPrimitiveComponent* OtherComp, 
								int32 OtherBodyIndex, 
								bool bFromSweep, 
								const FHitResult &SweepResult );
	//Add hit result message*/

protected:
	virtual void BeginPlay() override;

	
};
