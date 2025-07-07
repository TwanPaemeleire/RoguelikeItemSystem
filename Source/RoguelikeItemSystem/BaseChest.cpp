// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseChest.h"
#include "InteractableBox.h"
#include "ChestData.h"
#include "ItemDataManager.h"
#include "PlayerCharacter.h"
#include "ItemInventory.h"

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

	if (InteractableBox)
	{
		m_InteractDelegateHandle = InteractableBox->GetOnInteractEvent().AddLambda([this](APlayerCharacter* player)
			{
				OnInteract(player);
			});
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("InteractableBox is null in ABaseChest::BeginPlay"));
	}
}

// Called every frame
void ABaseChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseChest::OnInteract(APlayerCharacter* player)
{
	UItemDataManager* manager = GetWorld()->GetGameInstance()->GetSubsystem<UItemDataManager>();
	UItemData* randomItem = nullptr;
	if (ChestData->IsNonDefaultChest)
	{
		randomItem = manager->GetRandomItem(ChestData->DropTable, ChestData->ChestCategory);
	}
	else
	{
		randomItem = manager->GetRandomItem(ChestData->DropTable);
	}
	if(!randomItem)
	{
		UE_LOG(LogTemp, Warning, TEXT("No item found in the drop table for chest: %s"), *GetName());
		return;
	}
	
	player->GetItemInventory()->PickupItem(randomItem);
	InteractableBox->GetOnInteractEvent().Remove(m_InteractDelegateHandle);
}