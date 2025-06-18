// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseItem.h"
#include "ItemData.h"
#include "PlayerCharacter.h"
#include "ItemInventory.h"
#include "Components/BoxComponent.h"

// Sets default values
ABaseItem::ABaseItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ABaseItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Collision in item detected"));
	APlayerCharacter* player = Cast<APlayerCharacter>(OtherActor);
	if (player)
	{
		UE_LOG(LogTemp, Warning, TEXT("Collision with player detected in item"));
		player->GetItemInventory()->PickupItem(ItemData);
		Destroy();
	}
}

// Called when the game starts or when spawned
void ABaseItem::BeginPlay()
{
	Super::BeginPlay();
	UStaticMeshComponent* meshComponent = GetComponentByClass<UStaticMeshComponent>();
	if (meshComponent)
	{
		meshComponent->SetStaticMesh(ItemData->Mesh);
		meshComponent->SetMaterial(0, ItemData->Material);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No StaticMeshComponent found in ABaseItem!"));
	}

	UBoxComponent* boxComponent = GetComponentByClass<UBoxComponent>();
	if (boxComponent)
	{
		boxComponent->OnComponentBeginOverlap.AddDynamic(this, &ABaseItem::OnOverlapBegin);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No BoxComponent found in ABaseItem!"));
	}

}

// Called every frame
void ABaseItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

