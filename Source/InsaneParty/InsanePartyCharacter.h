// 2024, Pseudo / Ageev Daniil. All rights reserved ©

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InsanePartyCharacterBase.h"
#include "InsanePartyCharacter.generated.h"


UCLASS()
class INSANEPARTY_API AInsanePartyCharacter : public AInsanePartyCharacterBase
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;


	
	

public:
	AInsanePartyCharacter(const class FObjectInitializer& ObjectInitializer);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual void PossessedBy(AController* NewController) override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
	UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
	UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
	UInputAction* JumpAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
	UInputAction* ShootAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
	UInputAction* AimingAction;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
	UInputAction* InteractAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
	UInputAction* SwitchFireModeAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
	UInputAction* SelectFirstSlotAction;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
	UInputAction* SelectSecondSlotAction;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
	UInputAction* SelectThirdSlotAction;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
	UInputAction* ReloadAction;

	
	
	void Move(const FInputActionValue& Value);
	
	void Look(const FInputActionValue& Value);

	void HandleShootActionPressed();
	void HandleShootActionReleased();
	
	void HandleAimingActionPressed();
	void HandleAimingActionReleased();
	
	void HandleInteractActionPressed();
	
	void HandleInteractActionReleased();
	
	void HandleSwitchFireModeActionPressed();
	void HandleSwitchFireModeActionReleased();

	void HandleSelectFirstSlotActionPressed();
	void HandleSelectFirstSlotActionReleased();
	
	void HandleSelectSecondSlotActionPressed();
	void HandleSelectSecondSlotActionReleased();
	
	void HandleSelectThirdSlotActionPressed();
	void HandleSelectThirdSlotActionReleased();
	
	void HandleReloadActionPressed();
	void HandleReloadActionReleased();
	
	UFUNCTION(BlueprintCallable)
	void Interact();

	//Used for wait input release abilities, cuz idk how work prediction on server
	UFUNCTION(Server, Reliable)
	void SendServerInputToASC(bool bIsPressed, const EInsaneAbilityInputID AbilityInputID);
	void SendInputToASC(bool bIsPressed, const EInsaneAbilityInputID AbilityInputID);

	UFUNCTION(BlueprintImplementableEvent)
	void IMP_Recoil(float RecoilAmplitude, float SidewaysRecoilAmplitude, float Min, float Max);
	
	
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
