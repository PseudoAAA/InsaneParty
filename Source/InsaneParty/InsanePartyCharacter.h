// 2024, Pseudo / Ageev Daniil. All rights reserved ©

#pragma once

#include "InsaneParty.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "InsanePartyCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UInsaneGameplayAbility;
class UInsaneAbilitySystemComponent;
class UInsaneAttributeSet;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AInsanePartyCharacter : public ACharacter, public IAbilitySystemInterface
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

	/*Returns attribute variables*/
	UFUNCTION(BlueprintCallable, Category = "InsaneAttributes")
	virtual float GetHealth() const;
	UFUNCTION(BlueprintCallable, Category = "InsaneAttributes")
	virtual float GetMaxHealth() const;
	UFUNCTION(BlueprintCallable, Category = "InsaneAttributes")
	virtual float GetMedals() const;
	UFUNCTION(BlueprintCallable, Category = "InsaneAttributes")
	virtual float GetMaxMedals() const;
	UFUNCTION(BlueprintCallable, Category = "InsaneAttributes")
	virtual float GetKeys() const;

	/** Returns CameraBoom subobject **/
	class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	// To add mapping context
	virtual void BeginPlay() override;
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void AddStartupGameplayAbilities();
	
	/** Called for movement input */
	void Move(const FInputActionValue& Value);
	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	void Interact(const FInputActionValue& Value);

	
	//Health
	UFUNCTION(BlueprintImplementableEvent)
	void OnHealthChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);

	virtual void HandleHealthChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UInsaneAbilitySystemComponent> AbilitySystemComponent;
	
	/** Passive gameplay effects applied on creation */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	TArray<TSubclassOf<UGameplayEffect>> PassiveGameplayEffects;

	/** Abilities to grant to this character on creation. These will be activated
	 * by tag or event and are not bound to specific inputs */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	TArray<TSubclassOf<UInsaneGameplayAbility>> GameplayAbilities;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	TObjectPtr<UInsaneAttributeSet> Attributes;

	UPROPERTY()
	bool bAbilitiesInitialized;
	
	FGameplayTag DeadTag;
};

