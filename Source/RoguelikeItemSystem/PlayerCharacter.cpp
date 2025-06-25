// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "ItemData.h"
#include "ItemInventory.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h" 
#include "ItemInventoryWidget.h"
#include "InteractableBox.h"

#include "Camera/CameraComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	m_Camera->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	m_ItemInventory = GetComponentByClass<UItemInventory>();

	if (APlayerController* playerController = Cast<APlayerController>(GetController()))
	{
		if (ULocalPlayer* localPlayer = playerController->GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* subsystem = localPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				if (InputContext)
				{
					subsystem->AddMappingContext(InputContext, 0);
				}
			}
		}
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		EnhancedInput->BindAction(InteractAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Interact);
	}
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	FVector2D input = Value.Get<FVector2D>();
	if (input.IsNearlyZero()) return;
	input.Normalize();

	AddMovementInput(GetActorForwardVector(), input.Y);
	AddMovementInput(GetActorRightVector(), input.X);
}

void APlayerCharacter::Interact(const FInputActionValue& Value)
{
	if (m_InteractableInRange != nullptr)
	{
		m_InteractableInRange->Interact(this);
	}
}

