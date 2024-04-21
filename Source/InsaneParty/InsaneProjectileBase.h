// 2024, Pseudo / Ageev Daniil. All rights reserved ©

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InsaneProjectileBase.generated.h"

class UGameplayEffect;
class UProjectileMovementComponent;
class UCapsuleComponent;

UCLASS()
class INSANEPARTY_API AInsaneProjectileBase : public AActor
{
	GENERATED_BODY()

public:
	AInsaneProjectileBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UProjectileMovementComponent* ProjectileMovementComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	float Damage = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	float Range = 0.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	float InitialSpeed = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	float ProjectileGravityScale = 0.f;

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
