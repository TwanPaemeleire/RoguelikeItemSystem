// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "InteractableBox.generated.h"

class APlayerCharacter;

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE_OneParam(FOnInteractableOverlap, AActor*);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnInteract, APlayerCharacter*);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ROGUELIKEITEMSYSTEM_API UInteractableBox : public UBoxComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	void Interact(APlayerCharacter* character);

	FOnInteractableOverlap& GetOnBeginOverlapEvent() { return OnBeginOverlap; }
	FOnInteractableOverlap& GetOnEndOverlapEvent() { return OnEndOverlap; }
	FOnInteract& GetOnInteractEvent() { return OnInteract; }

private:
	FOnInteractableOverlap OnBeginOverlap;
	FOnInteractableOverlap OnEndOverlap;
	FOnInteract OnInteract;
};
