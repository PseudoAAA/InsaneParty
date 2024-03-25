// 2024, Pseudo / Ageev Daniil. All rights reserved ©


#include "InsaneParty/Public/Player/InsanePlayerState.h"

#include "GAS/InsaneAbilitySystemComponent.h"
#include "GAS/InsaneAttributeSet.h"
#include "Player/InsanePartyCharacter.h"


AInsanePlayerState::AInsanePlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UInsaneAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	InsaneAttributeSet = CreateDefaultSubobject<UInsaneAttributeSet>(TEXT("InsaneAttributeSet"));
	
	NetUpdateFrequency = 100.0f;

	DeadTag = FGameplayTag::RequestGameplayTag("Gameplay.Status.IsDead");
}

UAbilitySystemComponent* AInsanePlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UInsaneAttributeSet* AInsanePlayerState::GetInsaneAttributeSet() const
{
	return InsaneAttributeSet;
}

bool AInsanePlayerState::IsAlive() const
{
	return GetHealth() > 0.0f;
}

float AInsanePlayerState::GetHealth() const
{
	return InsaneAttributeSet->GetHealth();
}

float AInsanePlayerState::GetMaxHealth() const
{
	return InsaneAttributeSet->GetMaxHealth();
}

float AInsanePlayerState::GetMedals() const
{
	return InsaneAttributeSet->GetMedals();
}

float AInsanePlayerState::GetMaxMedals() const
{
	return InsaneAttributeSet->GetMaxMedals();
}

float AInsanePlayerState::GetKeys() const
{
	return InsaneAttributeSet->GetKeys();
}

void AInsanePlayerState::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComponent)
	{
		// Attribute change callbacks
		HealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(InsaneAttributeSet->GetHealthAttribute()).AddUObject(this, &AInsanePlayerState::HealthChanged);
		MaxHealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(InsaneAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &AInsanePlayerState::MaxHealthChanged);
		MedalsChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(InsaneAttributeSet->GetMedalsAttribute()).AddUObject(this, &AInsanePlayerState::MedalsChanged);
		MaxMedalsChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(InsaneAttributeSet->GetMaxMedalsAttribute()).AddUObject(this, &AInsanePlayerState::MaxMedalsChanged);
		KeysChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(InsaneAttributeSet->GetKeysAttribute()).AddUObject(this, &AInsanePlayerState::KeysChanged);

		// Tag change callbacks
		//AbilitySystemComponent->RegisterGameplayTagEvent(FGameplayTag::RequestGameplayTag(FName("State.Debuff.Stun")), EGameplayTagEventType::NewOrRemoved).AddUObject(this, &AInsanePlayerState::StunTagChanged);
	}
}

void AInsanePlayerState::HealthChanged(const FOnAttributeChangeData& Data)
{
	float Health = Data.NewValue;

	// Update floating status bar
	AInsanePartyCharacter* Hero = Cast<AInsanePartyCharacter>(GetPawn());
	if (Hero)
	{
		/*UGDFloatingStatusBarWidget* HeroFloatingStatusBar = Hero->GetFloatingStatusBar();
		if (HeroFloatingStatusBar)
		{
			HeroFloatingStatusBar->SetHealthPercentage(Health / GetMaxHealth());
		}*/
	}

	// Update the HUD
	// Handled in the UI itself using the AsyncTaskAttributeChanged node as an example how to do it in Blueprint

	// If the player died, handle death
	if (!IsAlive() && !AbilitySystemComponent->HasMatchingGameplayTag(DeadTag))
	{
		/*if (Hero)
		{
			Hero->Die();
		}*/
	}
}

void AInsanePlayerState::MaxHealthChanged(const FOnAttributeChangeData& Data)
{
}

void AInsanePlayerState::MedalsChanged(const FOnAttributeChangeData& Data)
{
}

void AInsanePlayerState::MaxMedalsChanged(const FOnAttributeChangeData& Data)
{
}

void AInsanePlayerState::KeysChanged(const FOnAttributeChangeData& Data)
{
}

