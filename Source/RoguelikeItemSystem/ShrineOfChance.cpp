// Fill out your copyright notice in the Description page of Project Settings.


#include "ShrineOfChance.h"
#include "InteractableBox.h"
#include "ItemDataManager.h"
#include "PlayerCharacter.h"
#include "ItemInventory.h"

// Sets default values
AShrineOfChance::AShrineOfChance()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_DropChances = 
	{  
		TPair<EItemRarity, int>(EItemRarity::White, 36),   
		TPair<EItemRarity, int>(EItemRarity::Green, 9),
		TPair<EItemRarity, int>(EItemRarity::Red, 1),
		TPair<EItemRarity, int>(EItemRarity::Orange, 9),
	};

	InteractableBox = CreateDefaultSubobject<UInteractableBox>(TEXT("InteractableBox"));
	RootComponent = InteractableBox;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(InteractableBox);
	StaticMeshComponent->SetCollisionProfileName(TEXT("BlockAllDynamic"));
}

// Called when the game starts or when spawned
void AShrineOfChance::BeginPlay()
{
	Super::BeginPlay();

	if (InteractableBox)
	{
		m_InteractDelegateHandle = InteractableBox->GetOnInteractEvent().AddLambda([this](APlayerCharacter* player)
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
	int randomNumber = FMath::RandRange(0, 100);
	if (randomNumber <= m_ChanceForNothing) return; // Add maybe a red VFX or something to indicate player didn't get anything
	UItemDataManager* manager = GetWorld()->GetGameInstance()->GetSubsystem<UItemDataManager>();
	UItemData* randomItem = manager->GetRandomItem(m_DropChances);
	player->GetItemInventory()->PickupItem(randomItem);
	++m_AmountDropped;
	if (m_AmountDropped >= m_MaxAmountOfDrops)
	{
		InteractableBox->GetOnInteractEvent().Remove(m_InteractDelegateHandle);
	}
}

// Called every frame
void AShrineOfChance::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

