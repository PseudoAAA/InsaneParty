// 2024, Pseudo / Ageev Daniil. All rights reserved ©

#include "InsaneAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "InsanePartyCharacter.h"
#include "InsanePlayerController.h"


UInsaneAttributeSet::UInsaneAttributeSet()
{}

void UInsaneAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UInsaneAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UInsaneAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UInsaneAttributeSet, Healing, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UInsaneAttributeSet, Damage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UInsaneAttributeSet, Damaging, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UInsaneAttributeSet, Medals, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UInsaneAttributeSet, MaxMedals, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UInsaneAttributeSet, Keys, COND_None, REPNOTIFY_Always);
}

void UInsaneAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetMaxHealthAttribute())
	{
		AdjustAttributeForMaxChange(Health, MaxHealth, NewValue, GetHealthAttribute());
	}
	/*else if (Attribute == GetMaxMedalsAttribute())
	{
		AdjustAttributeForMaxChange(Medals, MaxMedals, NewValue, GetMedalsAttribute());
	}*/
}

void UInsaneAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	FGameplayEffectContextHandle Context = Data.EffectSpec.GetContext();
	UAbilitySystemComponent* Source = Context.GetOriginalInstigatorAbilitySystemComponent();
	const FGameplayTagContainer& SourceTags = *Data.EffectSpec.CapturedSourceTags.GetAggregatedTags();
	FGameplayTagContainer SpecAssetTags;
	Data.EffectSpec.GetAllAssetTags(SpecAssetTags);

	//Get the Target actor, which should be our owner
	AActor* TargetActor = nullptr;
	AController* TargetController = nullptr;
	AInsanePartyCharacterBase* TargetCharacter = nullptr;
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		TargetCharacter = Cast<AInsanePartyCharacterBase>(TargetActor);
	}

	// Get the Source actor
	AActor* SourceActor = nullptr;
	AController* SourceController = nullptr;
	AInsanePartyCharacterBase* SourceCharacter = nullptr;
	if (Source && Source->AbilityActorInfo.IsValid() && Source->AbilityActorInfo->AvatarActor.IsValid())
	{
		SourceActor = Source->AbilityActorInfo->AvatarActor.Get();
		SourceController = Source->AbilityActorInfo->PlayerController.Get();
		if (SourceController == nullptr && SourceActor != nullptr)
		{
			if (APawn* Pawn = Cast<APawn>(SourceActor))
			{
				SourceController = Pawn->GetController();
			}
		}
		
		// Use the controller to find the source pawn
		if (SourceController)
		{
			SourceCharacter = Cast<AInsanePartyCharacterBase>(SourceController->GetPawn());
		}
		else
		{
			SourceCharacter = Cast<AInsanePartyCharacterBase>(SourceActor);
		}
		// Set the causer actor based on context if it's set
		if (Context.GetEffectCauser())
		{
			SourceActor = Context.GetEffectCauser();
		}
	}
	UE_LOG(LogTemp, Log, TEXT("Attribute is %s"), *Data.EvaluatedData.Attribute.GetName());
	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
		{
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
			// Try to extract a hit result
			FHitResult HitResult;
			if (Context.GetHitResult())
			{
				HitResult = *Context.GetHitResult();
			}
	
			// Store a local copy of the amount of damage done and clear the damage attribute
			const float LocalDamageDone = GetDamage();
			SetDamage(0.f);
		
			if (LocalDamageDone > 0.0f)
			{
				// If character was alive before damage is added, handle damage
				// This prevents damage being added to dead things and replaying death animations
				bool WasAlive = true;
	
				if (TargetCharacter)
				{
					WasAlive = TargetCharacter->IsAlive();
				}
	
				if (!TargetCharacter->IsAlive())
				{
					UE_LOG(LogTemp, Warning, TEXT("%s() %s is NOT alive when receiving damage"), TEXT(__FUNCTION__), *TargetCharacter->GetName());
				}
	
				// Apply the health change and then clamp it
				const float NewHealth = GetHealth() - LocalDamageDone;
				SetHealth(FMath::Clamp(NewHealth, 0.0f, GetMaxHealth()));
	
				if (TargetCharacter && WasAlive)
				{
					// This is the log statement for damage received. Turned off for live games.
					UE_LOG(LogTemp, Log, TEXT("%s() %s Damage Received: %f"), TEXT(__FUNCTION__), *GetOwningActor()->GetName(), LocalDamageDone);
					const FHitResult* Hit = Data.EffectSpec.GetContext().GetHitResult();
					
					// Show damage number for the Source player unless it was self damage
					if (SourceActor != TargetActor)
					{
						AInsanePlayerController* PC = Cast<AInsanePlayerController>(SourceController);
						if (PC)
						{
							
							UE_LOG(LogTemp, Log, TEXT("%s() %s Damage Received: %f"), TEXT(__FUNCTION__), *GetOwningActor()->GetName(), LocalDamageDone);
							//PC->ShowDamageNumber(LocalDamageDone, TargetCharacter);
						}
					}
				}	
			}
		}
		else if (Data.EvaluatedData.Attribute == GetHealingAttribute())
		{
			SetHealth(FMath::Clamp(GetHealth() + GetHealing(), 0.0f, GetMaxHealth()));
			SetHealing(0.0f);
		}
		else if (Data.EvaluatedData.Attribute == GetHealthAttribute())
		{
			SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
		}
		else if(Data.EvaluatedData.Attribute == GetMedalsAttribute())
		{
			SetMedals(FMath::Clamp(GetMedals(), 0.0f, GetMaxMedals()));
		}
		else if(Data.EvaluatedData.Attribute == GetKeysAttribute())
		{
			SetKeys(GetKeys());
		}
	
}

void UInsaneAttributeSet::AdjustAttributeForMaxChange(const FGameplayAttributeData& AffectedAttribute,
                                                      const FGameplayAttributeData& MaxAttribute, const float NewMaxValue,
                                                      const FGameplayAttribute& AffectedAttributeProperty) const
{
	UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
	const float CurrentMaxValue = MaxAttribute.GetCurrentValue();
	if (!FMath::IsNearlyEqual(CurrentMaxValue, NewMaxValue) && AbilityComp)
	{
		// Change current value to maintain the current Val / Max percent
		const float CurrentValue = AffectedAttribute.GetCurrentValue();
		float NewDelta = (CurrentMaxValue > 0.f) ? (CurrentValue * NewMaxValue / CurrentMaxValue) - CurrentValue : NewMaxValue;

		AbilityComp->ApplyModToAttributeUnsafe(AffectedAttributeProperty, EGameplayModOp::Additive, NewDelta);
	}
}

void UInsaneAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UInsaneAttributeSet, Health, OldValue);
}

void UInsaneAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UInsaneAttributeSet, MaxHealth, OldValue);
}

void UInsaneAttributeSet::OnRep_Healing(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UInsaneAttributeSet, Healing, OldValue);
}

void UInsaneAttributeSet::OnRep_Damage(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UInsaneAttributeSet, Damage, OldValue);
}

void UInsaneAttributeSet::OnRep_Damaging(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UInsaneAttributeSet, Damaging, OldValue);
}

void UInsaneAttributeSet::OnRep_Medals(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UInsaneAttributeSet, Medals, OldValue);
}

void UInsaneAttributeSet::OnRep_MaxMedals(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UInsaneAttributeSet, MaxMedals, OldValue);
}

void UInsaneAttributeSet::OnRep_Keys(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UInsaneAttributeSet, Keys, OldValue);
}




