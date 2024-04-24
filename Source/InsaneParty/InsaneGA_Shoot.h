// 2024, Pseudo / Ageev Daniil. All rights reserved ©

#pragma once

#include "CoreMinimal.h"
#include "InsaneGameplayAbility.h"
#include "InsaneProjectileBase.h"
#include "InsaneGA_Shoot.generated.h"


class AInsanePartyCharacter;
class AInsaneProjectileBase;
/**
 * 
 */
UCLASS()
class INSANEPARTY_API UInsaneGA_Shoot : public UInsaneGameplayAbility
{
	GENERATED_BODY()

public:
	UInsaneGA_Shoot();

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<UGameplayEffect> DamageGameplayEffect;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	USoundWave* WeaponFireSound;
	
	UFUNCTION(Server, Reliable)
	void ProjectileSpawn(AInsanePartyCharacter* PartyCharacter, TSubclassOf<AInsaneProjectileBase> Projectile, APawn* PartyInstigator);
	
	UFUNCTION()
	void SingleFireRelease(float TimeHeld);
	
	UFUNCTION()
	void OnDelayEnd();
	FTimerHandle ShootDelay;
	
	/** Actually activate ability, do not call this directly. We'll call it from APAHeroCharacter::ActivateAbilitiesWithTags(). */
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	
protected:
	
	UFUNCTION()
	void OnCancelled(FGameplayTag EventTag, FGameplayEventData EventData);

	UFUNCTION()
	void OnCompleted(FGameplayTag EventTag, FGameplayEventData EventData);
};
