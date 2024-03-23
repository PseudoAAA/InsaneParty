// 2024, Pseudo / Ageev Daniil. All rights reserved ©

#include "InsanePartyCharacterBase.h"
#include "Engine/LocalPlayer.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Player/InsanePlayerState.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

/**
 * The base class of character.
 * Everything with an AbilitySystemComponent in this game will inherit from this class.
*/
AInsanePartyCharacterBase::AInsanePartyCharacterBase()
{
	bReplicates = true;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
}

void AInsanePartyCharacterBase::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

}


void AInsanePartyCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	AInsanePlayerState* PS = GetPlayerState<AInsanePlayerState>();
	if (PS)
	{
		// Set the ASC on the Server. Clients do this in OnRep_PlayerState()
		AbilitySystemComponent = Cast<UInsaneAbilitySystemComponent>(PS->GetAbilitySystemComponent());

		// AI won't have PlayerControllers so we can init again here just to be sure. No harm in initing twice for heroes that have PlayerControllers.
		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, this);
	}
}

void AInsanePartyCharacterBase::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

}

void AInsanePartyCharacterBase::IsAlive()
{
	
}


