// Fill out your copyright notice in the Description page of Project Settings.


#include "ShrineOfChance.h"
#include "InteractableBox.h"

// Sets default values
AShrineOfChance::AShrineOfChance()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InteractableBox = CreateDefaultSubobject<UInteractableBox>(TEXT("CustomInteractableBox"));
	RootComponent = InteractableBox;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(InteractableBox);
	StaticMeshComponent->SetCollisionProfileName(TEXT("BlockAllDynamic"));
}

// Called when the game starts or when spawned
void AShrineOfChance::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShrineOfChance::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

