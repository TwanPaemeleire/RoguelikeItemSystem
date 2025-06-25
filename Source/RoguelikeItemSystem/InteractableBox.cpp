// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableBox.h"
#include "PlayerCharacter.h"

void UInteractableBox::BeginPlay()
{
    Super::BeginPlay();

    OnComponentBeginOverlap.AddDynamic(this, &UInteractableBox::OnOverlapBegin);
    OnComponentEndOverlap.AddDynamic(this, &UInteractableBox::OnOverlapEnd);
}

void UInteractableBox::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor != GetOwner())
    {
        APlayerCharacter* player = Cast<APlayerCharacter>(OtherActor);
        if (player)
        {
            UE_LOG(LogTemp, Warning, TEXT("OVERLAP BEGIN WITH PLAYER CHAR"));
            player->SetInteractableInRange(this);
            OnBeginOverlap.Broadcast(OtherActor);
        }
    }
}

void UInteractableBox::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor && OtherActor != GetOwner())
    {
        APlayerCharacter* player = Cast<APlayerCharacter>(OtherActor);
        if (player)
        {
            UE_LOG(LogTemp, Warning, TEXT("OVERLAP END WITH PLAYER CHAR"));
            player->SetInteractableInRange(nullptr);
            OnEndOverlap.Broadcast(OtherActor);
        }
    }
}

void UInteractableBox::Interact(APlayerCharacter* character)
{
    OnInteract.Broadcast(character);
}
