// 2024, Pseudo / Ageev Daniil. All rights reserved ©

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InsaneInventorySystemComponent.h"
#include "InsanePartyCharacterBase.h"
#include "InsanePartyCharacter.generated.h"


UCLASS()
class INSANEPARTY_API AInsanePartyCharacter : public AInsanePartyCharacterBase
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** Interact Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

public:
	AInsanePartyCharacter();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;
	
	/** Called for movement input */
	void Move(const FInputActionValue& Value);
	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerInteract(AActor* AnActor);

	void Interact();
	
	/** Returns CameraBoom subobject **/
	class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void PostInitializeComponents() override;

	// Client only
	virtual void OnRep_PlayerState() override;
};
