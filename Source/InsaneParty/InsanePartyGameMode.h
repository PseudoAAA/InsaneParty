#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "InsanePartyGameMode.generated.h"

UCLASS(minimalapi)
class AInsanePartyGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AInsanePartyGameMode();
	
	void HeroDied(AController* Controller);

protected:
	float RespawnDelay;

	TSubclassOf<class AGDHeroCharacter> HeroClass;

	AActor* EnemySpawnPoint;

	virtual void BeginPlay() override;

	void RespawnHero(AController* Controller);
};



