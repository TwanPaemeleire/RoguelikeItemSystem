// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseChest.h"
#include "InteractableBox.h"
#include "ChestData.h"

// Sets default values
ABaseChest::ABaseChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	InteractableBox = CreateDefaultSubobject<UInteractableBox>(TEXT("InteractableBox"));
	RootComponent = InteractableBox;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(InteractableBox);
	StaticMeshComponent->SetGenerateOverlapEvents(false);
	StaticMeshComponent->SetCollisionProfileName(TEXT("NoCollision"));
}

// Called when the game starts or when spawned
void ABaseChest::BeginPlay()
{
	Super::BeginPlay();
	StaticMeshComponent->SetStaticMesh(ChestData->Mesh);
	StaticMeshComponent->SetMaterial(0, ChestData->Material);
	StaticMeshComponent->SetGenerateOverlapEvents(false);
	StaticMeshComponent->SetCollisionProfileName(TEXT("NoCollision"));
}

// Called every frame
void ABaseChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

