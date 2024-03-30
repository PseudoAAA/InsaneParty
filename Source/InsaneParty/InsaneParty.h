// 2024, Pseudo / Ageev Daniil. All rights reserved ©

#pragma once

#include "CoreMinimal.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


#include "InsaneParty/InsaneData.h"
#include "InsaneAbilitySystemComponent.h"
#include "InsaneGameplayAbility.h"
#include "InsaneAttributeSet.h"

#define ACTOR_ROLE_FSTRING *(FindObject<UEnum>(nullptr, TEXT("/Script/Engine.ENetRole"), true)->GetNameStringByValue(GetLocalRole()))
#define GET_ACTOR_ROLE_FSTRING(Actor) *(FindObject<UEnum>(nullptr, TEXT("/Script/Engine.ENetRole"), true)->GetNameStringByValue(Actor->GetLocalRole()))


INSANEPARTY_API DECLARE_LOG_CATEGORY_EXTERN(InsanePartyLog, Log, All);
INSANEPARTY_API DECLARE_LOG_CATEGORY_EXTERN(LogInsaneCharacter, Log, All);
INSANEPARTY_API DECLARE_LOG_CATEGORY_EXTERN(LogInsaneInventory, Log, All);