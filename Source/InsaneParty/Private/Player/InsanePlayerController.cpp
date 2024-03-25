// 2024, Pseudo / Ageev Daniil. All rights reserved ©


#include "Player/InsanePlayerController.h"

#include "AbilitySystemComponent.h"
#include "Player/InsanePlayerState.h"

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