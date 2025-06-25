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

	if (InteractableBox)
	{
		UE_LOG(LogTemp, Warning, TEXT("InteractableBox is NOT null in AShrineOfChance::AShrineOfChance"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("InteractableBox is null in AShrineOfChance::AShrineOfChance"));
	}
}

// Called when the game starts or when spawned
void AShrineOfChance::BeginPlay()
{
	Super::BeginPlay();

	if (InteractableBox)
	{
		InteractableBox->GetOnInteractEvent().AddLambda([this](APlayerCharacter* player)
			{
				OnInteract(player);
			});
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("InteractableBox is null in AShrineOfChance::BeginPlay"));
	}
}

void AShrineOfChance::OnInteract(APlayerCharacter* player)
{
	UE_LOG(LogTemp, Warning, TEXT("INTERACTED WITH SHRINE"));
}

// Called every frame
void AShrineOfChance::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

