// 2024, Pseudo / Ageev Daniil. All rights reserved ©


#include "InsanePlayerState.h"

#include "InsaneAbilitySystemComponent.h"
#include "InsaneAttributeSet.h"
#include "InsanePartyCharacter.h"


AInsanePlayerState::AInsanePlayerState()
{
	InventorySystemComponent = CreateDefaultSubobject<UInsaneInventorySystemComponent>(TEXT("InventorySystemComponent"));
	InventorySystemComponent->SetIsReplicated(true);
	
	AbilitySystemComponent = CreateDefaultSubobject<UInsaneAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	InsaneAttributeSet = CreateDefaultSubobject<UInsaneAttributeSet>(TEXT("InsaneAttributeSet"));
	
	NetUpdateFrequency = 100.0f;

	DeadTag = FGameplayTag::RequestGameplayTag("GameplayStatus.IsDead");
}

UInsaneInventorySystemComponent* AInsanePlayerState::GetInventorySystemComponent() const 
{
	return InventorySystemComponent;
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

	}
}

void AInsanePlayerState::HealthChanged(const FOnAttributeChangeData& Data)
{
	float Health = Data.NewValue;

	// Update floating status bar
	AInsanePartyCharacter* Hero = Cast<AInsanePartyCharacter>(GetPawn());
	
	if (!IsAlive() && !AbilitySystemComponent->HasMatchingGameplayTag(DeadTag))
	{
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

