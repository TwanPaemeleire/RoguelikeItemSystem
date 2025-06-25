// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemData.h"
#include "ShrineOfChance.generated.h"

class UInteractableBox;
class UStaticMeshComponent;
class APlayerCharacter;

UCLASS()
class ROGUELIKEITEMSYSTEM_API AShrineOfChance : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShrineOfChance();

	UPROPERTY(EditAnywhere)
	UInteractableBox* InteractableBox;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMeshComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void OnInteract(APlayerCharacter* player);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private: 
	TArray<TPair<EItemRarity, int>> m_DropChances;
	int m_ChanceForNothing{ 45 };
	int m_MaxAmountOfDrops{ 2 };
	int m_AmountDropped{ 0 };
	FDelegateHandle m_InteractDelegateHandle;


};
