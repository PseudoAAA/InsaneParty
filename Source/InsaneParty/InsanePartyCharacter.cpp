// 2024, Pseudo / Ageev Daniil. All rights reserved ©


#include "InsanePartyCharacter.h"
#include "EnhancedInputComponent.h"
#include "InteractInterface.h"


// Sets default values
AInsanePartyCharacter::AInsanePartyCharacter(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

}

void AInsanePartyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AInsanePartyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AInsanePartyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AInsanePartyCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AInsanePartyCharacter::Look);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AInsanePartyCharacter::Interact);
	}
	else
	{
		UE_LOG(LogInsaneCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AInsanePartyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	
	AInsanePlayerState* PS = GetPlayerState<AInsanePlayerState>();
	if (PS)
	{
		// Set the ASC on the Server. Clients do this in OnRep_PlayerState()
		AbilitySystemComponent = Cast<UInsaneAbilitySystemComponent>(PS->GetAbilitySystemComponent());

		// AI won't have PlayerControllers so we can init again here just to be sure. No harm in initing twice for heroes that have PlayerControllers.
		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, this);

		// Set the AttributeSetBase for convenience attribute functions
		AttributeSetBase = PS->GetInsaneAttributeSet();

		// If we handle players disconnecting and rejoining in the future, we'll have to change this so that possession from rejoining doesn't reset attributes.
		// For now assume possession = spawn/respawn.
		InitializeAttributes();

		// Forcibly set the DeadTag count to 0
		AbilitySystemComponent->SetTagMapCount(DeadTag, 0);

		// Set Health to max. This is only necessary for *Respawn*.
		SetHealth(GetMaxHealth());

		AddStartupEffects();

		AddCharacterAbilities();
	}
}

void AInsanePartyCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AInsanePartyCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AInsanePartyCharacter::Interact()
{
	if (Controller != nullptr)
	{
		FHitResult OutHit;
		FVector Start = GetFollowCamera()->GetComponentLocation();
		FVector ForwardVector = FollowCamera->GetForwardVector();
		FVector End = ((ForwardVector * 700.f) + Start);

		TArray<AActor*> IgnoredActors;
		IgnoredActors.Add(this);
		
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldDynamic));
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));


#if UE_BUILD_DEBUG
		EDrawDebugTrace::Type TraceVisibility = EDrawDebugTrace::ForDuration;
#else
		EDrawDebugTrace::Type TraceVisibility = EDrawDebugTrace::None;
#endif
		
		if(UKismetSystemLibrary::SphereTraceSingleForObjects(
			GetWorld(), Start, End, 5.0f,
			ObjectTypes, false, IgnoredActors,
			TraceVisibility,
			OutHit,true,
			FColor::FromHex("D49AFFFF"), FColor::FromHex("FFFFFFFF"))
			){
			if(OutHit.bBlockingHit)
			{
				if (GEngine) {
					if (OutHit.GetActor()->Implements<UInteractInterface>())
					{
						ServerInteract(OutHit.GetActor());
						//IInteractInterface::Execute_Interact(OutHit.GetActor(), this);
					}
				}
			}
		}
	}
}

void AInsanePartyCharacter::ServerInteract_Implementation(AActor* AnActor)
{
	IInteractInterface::Execute_Interact(AnActor, this);
}

bool AInsanePartyCharacter::ServerInteract_Validate(AActor* AnActor)
{
	return true;
}

void AInsanePartyCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	
	AInsanePlayerState* PS = GetPlayerState<AInsanePlayerState>();
	if (PS)
	{
		// Set the ASC for clients. Server does this in PossessedBy.
		AbilitySystemComponent = Cast<UInsaneAbilitySystemComponent>(PS->GetAbilitySystemComponent());

		// Init ASC Actor Info for clients. Server will init its ASC when it possesses a new Actor.
		AbilitySystemComponent->InitAbilityActorInfo(PS, this);

		// Set the AttributeSetBase for convenience attribute functions
		AttributeSetBase = PS->GetInsaneAttributeSet();

		// If we handle players disconnecting and rejoining in the future, we'll have to change this so that posession from rejoining doesn't reset attributes.
		// For now assume possession = spawn/respawn.
		InitializeAttributes();
		
		// Forcibly set the DeadTag count to 0
		AbilitySystemComponent->SetTagMapCount(DeadTag, 0);

		// Set Health to max. This is only necessary for *Respawn*.
		SetHealth(GetMaxHealth());
	}
}
