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



protected:
	// Server only
	virtual void OnPossess(APawn* InPawn) override;

	virtual void OnRep_PlayerState() override;
};
