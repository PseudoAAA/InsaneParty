#include "InsanePartyGameMode.h"
#include "UObject/ConstructorHelpers.h"

AInsanePartyGameMode::AInsanePartyGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/BP_InsanePartyCharacter"));
	
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
