// 2024, Pseudo / Ageev Daniil. All rights reserved ©

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InsanePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class INSANEPARTY_API AInsanePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	
	UFUNCTION(Client, Reliable, WithValidation)
	void SetRespawnCountdown(float RespawnTimeRemaining);
	void SetRespawnCountdown_Implementation(float RespawnTimeRemaining);
	bool SetRespawnCountdown_Validate(float RespawnTimeRemaining);
	
protected:
	// Server only
	virtual void OnPossess(APawn* InPawn) override;

	virtual void OnRep_PlayerState() override;
};
