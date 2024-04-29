// 2024, Pseudo / Ageev Daniil. All rights reserved ©


#include "InsaneProjectileBase.h"

#include "InsanePartyCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AInsaneProjectileBase::AInsaneProjectileBase()
{

	this->bReplicates = true;
	this->ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	this->CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	this->ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	
	SetRootComponent(CapsuleComponent);
	this->ProjectileMesh->SetupAttachment(CapsuleComponent);
	UE_LOG(LogTemp, Warning, TEXT("%f"), this->ProjectileMovementComponent->InitialSpeed);
}



/*void AInsaneProjectileBase::BeginOverlap(UPrimitiveComponent* OverlappedComponent, 
								AActor* OtherActor, 
								UPrimitiveComponent* OtherComp, 
								int32 OtherBodyIndex, 
								bool bFromSweep, 
								const FHitResult &SweepResult )
{
	if(OtherActor != ProjectileOwner)
	{
		this->OverlapActor = OtherActor;
		if(this->HasAuthority())
		{
			AInsanePartyCharacter* OwnerPlayer = Cast<AInsanePartyCharacter>(this->ProjectileOwner);
			AInsanePartyCharacter* TargetPlayer = Cast<AInsanePartyCharacter>(this->OverlapActor);
			if(IsValid(OwnerPlayer) && IsValid(TargetPlayer))
			{
				UAbilitySystemComponent* OwnerASC = OwnerPlayer->GetAbilitySystemComponent();
				UAbilitySystemComponent* TargetASC = TargetPlayer->GetAbilitySystemComponent();
				FGameplayEffectContextHandle OwnerASCContextHandle = OwnerASC->MakeEffectContext();
				FGameplayEffectSpecHandle TargetASCOutgoingSpec = TargetASC->MakeOutgoingSpec(this->GE_Damaging, 0.f, OwnerASCContextHandle);
				if(IsValid(TargetASC) && IsValid(OwnerASC))
				{
					TArray<FHitResult> OutHit;
					TArray<AActor*> IgnoredActors;
					IgnoredActors.Add(this);
					TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
					ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
				
					FVector Start = this->GetActorLocation();
					FVector UpVector = this->GetActorForwardVector() * 150.f;
					FVector End = Start + UpVector;
				
					if(UKismetSystemLibrary::CapsuleTraceMultiForObjects(
						GetWorld(), Start, End,15.f, 5.f, ObjectTypes,
						true, IgnoredActors, EDrawDebugTrace::ForDuration,OutHit, true))
					{
						for(auto &HittedActorInfo : OutHit)
						{
							if(HittedActorInfo.GetActor() == this->OverlapActor)
							{
								this->HitResult = HittedActorInfo;
							
								OwnerASCContextHandle.AddHitResult(this->HitResult);
								TargetASCOutgoingSpec.Data.Get()->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("GameplayEffect.Damage")), this->Damage);
								TargetASC->ApplyGameplayEffectSpecToSelf(*TargetASCOutgoingSpec.Data.Get());
								this->Destroy();
								return;
							}
						}
					}
					this->Destroy();
				}
				this->Destroy();
			}
			this->Destroy();
		}
		this->Destroy();
	}
}*/


void AInsaneProjectileBase::BeginPlay()
{
	Super::BeginPlay();
}


