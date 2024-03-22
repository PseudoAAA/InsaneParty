// 2024, Pseudo / Ageev Daniil. All rights reserved ©

#include "InsaneParty/Public/GAS/InsaneAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "InsaneParty/InsanePartyCharacter.h"


UInsaneAttributeSet::UInsaneAttributeSet()
	:Health(100.f)
	,MaxHealth(100.f)
{}

void UInsaneAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UInsaneAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UInsaneAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
}

void UInsaneAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetMaxHealthAttribute())
	{
		AdjustAttributeForMaxChange(Health, MaxHealth, NewValue, GetHealthAttribute());
	}
}

void UInsaneAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	float MinimumValue = 0.0f;
	
	FGameplayEffectContextHandle Context = Data.EffectSpec.GetContext();
	UAbilitySystemComponent* Source = Context.GetOriginalInstigatorAbilitySystemComponent();
	const FGameplayTagContainer& SourceTags = *Data.EffectSpec.CapturedSourceTags.GetAggregatedTags();

	float DeltaValue = 0;
	if (Data.EvaluatedData.ModifierOp == EGameplayModOp::Type::Additive)
	{
		// If this was additive, store the raw delta value to be passed along later
		DeltaValue = Data.EvaluatedData.Magnitude;
	}
	
	AInsanePartyCharacter* TargetCharacter = nullptr;
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		// AController* TargetController = nullptr;
		AActor* TargetActor = nullptr;
		TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		// TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		TargetCharacter = Cast<AInsanePartyCharacter>(TargetActor);
	}
	
	if (Data.EvaluatedData.Attribute == GetHealingAttribute())
	{
		// Convert into +Health and then clamp
		SetHealth(FMath::Clamp(GetHealth() + GetHealing(), MinimumValue, GetMaxHealth()));
		SetHealing(0.0f);
	}
	else if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		// Clamp and fall into out of health handling below
		SetHealth(FMath::Clamp(GetHealth(), MinimumValue, GetMaxHealth()));
	}

	if (Data.EvaluatedData.Attribute == GetMedalsAttribute())
	{
		SetMedals(FMath::Clamp(GetMedals(), MinimumValue, GetMaxMedals()));
	}
	
	if (Data.EvaluatedData.Attribute == GetDamagingAttribute())
	{
		// Convert into Damage and then clamp
		SetHealth(FMath::Clamp(GetHealth() + (GetDamaging() > 0 ? GetDamaging() * -1 : GetDamaging()), MinimumValue, GetMaxHealth()));
		if (GetHealth() <= 0)
		{
			FGameplayTag DeadTag = FGameplayTag::RequestGameplayTag("Gameplay.Status.IsDead");
			GetOwningAbilitySystemComponent()->AddLooseGameplayTags(DeadTag.GetSingleTagContainer(), 1);
		}
		//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("%f"), GetHealth() + (GetDamaging()*-1)));
		SetDamaging(0.0f);
	}
	else if(Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth() + (GetDamage() > 0 ? GetDamage() * -1 : GetDamage()), MinimumValue, GetMaxHealth()));
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
		const float NewDelta = (CurrentMaxValue > 0.f)
								   ? (CurrentValue * NewMaxValue / CurrentMaxValue) - CurrentValue
								   : NewMaxValue;

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




