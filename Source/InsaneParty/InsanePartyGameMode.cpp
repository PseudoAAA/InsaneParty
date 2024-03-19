#include "InsanePartyGameMode.h"
#include "InsanePartyCharacter.h"
#include "UObject/ConstructorHelpers.h"

AInsanePartyGameMode::AInsanePartyGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Characters/DefaultCharacter/BP_ThirdPersonCharacter"));
	
	
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
