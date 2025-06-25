// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class UItemInventory;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;
class UInputMappingContext;
class UInteractableBox;


UCLASS()
class ROGUELIKEITEMSYSTEM_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& Value);
	void Interact(const FInputActionValue& Value);

	UItemInventory* GetItemInventory() const { return m_ItemInventory; }
	void SetInteractableInRange(UInteractableBox* interactable) { m_InteractableInRange = interactable; }

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* InputContext;

private:
	UItemInventory* m_ItemInventory{};

	UInteractableBox* m_InteractableInRange{nullptr};

	UPROPERTY(EditAnywhere)
	UCameraComponent* m_Camera;
};
