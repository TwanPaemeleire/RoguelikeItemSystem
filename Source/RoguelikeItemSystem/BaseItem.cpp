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

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComponent;
	BoxComponent->SetBoxExtent(FVector(50.f));
	BoxComponent->SetGenerateOverlapEvents(true);
	BoxComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	//BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ABaseItem::OnOverlapBegin);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(BoxComponent);
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
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

void ABaseItem::OnPickUp()
{
	// Play VFX or anything else
}

// Called when the game starts or when spawned
void ABaseItem::BeginPlay()
{
	Super::BeginPlay();
	StaticMeshComponent->SetStaticMesh(ItemData->Mesh);
	StaticMeshComponent->SetMaterial(0, ItemData->Material);
	DrawDebugBox(GetWorld(), BoxComponent->GetComponentLocation(), BoxComponent->GetScaledBoxExtent(), FColor::Red, true, 10.0f);
}

void ABaseItem::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
	if (Player)
	{
		UE_LOG(LogTemp, Warning, TEXT("Collision with player detected in item"));
		if (ItemData)
		{
			Player->GetItemInventory()->PickupItem(ItemData);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("ItemData is null in the ActorBeginOverlap function of ABaseItem"));
		}
		Destroy();
	}
}

// Called every frame
void ABaseItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

