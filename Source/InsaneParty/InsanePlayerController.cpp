// 2024, Pseudo / Ageev Daniil. All rights reserved ©


#include "InsanePlayerController.h"
#include "AbilitySystemComponent.h"
#include "InsanePlayerState.h"

void AInsanePlayerController::SetRespawnCountdown_Implementation(float RespawnTimeRemaining)
{
}

bool AInsanePlayerController::SetRespawnCountdown_Validate(float RespawnTimeRemaining)
{
	return true;
}

// Server only
void AInsanePlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AInsanePlayerState* PS = GetPlayerState<AInsanePlayerState>();
	if (PS)
	{
		// Init ASC with PS (Owner) and our new Pawn (AvatarActor)
		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, InPawn);
	}
	
}

void AInsanePlayerController::OnRep_PlayerState()
{
	
	Super::OnRep_PlayerState();
}