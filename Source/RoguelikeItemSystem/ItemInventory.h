// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemInventory.generated.h"

class UItemData;
class UBaseItemLogic;
class UItemInventoryWidget;

USTRUCT()
struct FInventorySlotData
{
	GENERATED_BODY();

	UPROPERTY()
	class UItemData* itemData;
	UPROPERTY()
	int amount;
	UPROPERTY()
	TArray<TObjectPtr<UBaseItemLogic>> itemLogicInstances;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROGUELIKEITEMSYSTEM_API UItemInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UItemInventory();

	void PickupItem(UItemData* data);
	void DropItem(UItemData* data, int amount);
	void DropItemAll(UItemData* data);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void RemoveLogicInstances(FInventorySlotData* slot, int amount);

	UPROPERTY()
	TArray<FInventorySlotData> m_Inventory{};

	UPROPERTY(EditAnywhere)
	TSubclassOf<UItemInventoryWidget> ItemInventoryWidgetClass;

	UPROPERTY()
	UItemInventoryWidget* ItemInventoryWidget;
		
};
