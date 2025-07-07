// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseChest.generated.h"

class UChestData;
class UStaticMeshComponent;
class UInteractableBox;
class APlayerCharacter;

UCLASS()
class ROGUELIKEITEMSYSTEM_API ABaseChest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseChest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void OnInteract(APlayerCharacter* player);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
	UChestData* ChestData;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere)
	UInteractableBox* InteractableBox;

	FDelegateHandle m_InteractDelegateHandle;
};
