// 2024, Pseudo / Ageev Daniil. All rights reserved ©

#pragma once

#include "CoreMinimal.h"
#include "InsaneGameplayAbility.h"
#include "InsaneGA_Shoot.generated.h"


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
	TSubclassOf<AInsaneProjectileBase> ProjectileClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<UGameplayEffect> DamageGameplayEffect;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	USoundWave* WeaponFireSound;


	UFUNCTION()
	void SingleFireRelease(float TimeHeld);

	UFUNCTION(Client, Unreliable)
	void Client_Features(AActor* Target);
	
	UFUNCTION(Server, Reliable)
	void SR_SpawnSound();
	
	UFUNCTION(Server, Reliable)
	void SR_SpawnProjectile(AInsanePartyCharacter* PartyCharacter);
	
	/** Actually activate ability, do not call this directly. We'll call it from APAHeroCharacter::ActivateAbilitiesWithTags(). */
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:
	
	UFUNCTION()
	void OnCancelled(FGameplayTag EventTag, FGameplayEventData EventData);

	UFUNCTION()
	void OnCompleted(FGameplayTag EventTag, FGameplayEventData EventData);
	
	UFUNCTION()
	void Shoot(AInsaneWeaponBase* WeaponData, FGameplayEffectContextHandle Context);
};
