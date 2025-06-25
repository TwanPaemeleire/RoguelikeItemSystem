// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShrineOfChance.generated.h"

class UInteractableBox;
class UStaticMeshComponent;

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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
