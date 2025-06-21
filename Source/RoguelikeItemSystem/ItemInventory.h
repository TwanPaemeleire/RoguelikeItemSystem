// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemInventory.generated.h"

class UItemData;
class UBaseItemLogic;

struct InventorySlotData
{
	class UItemData* itemData;
	int amount;
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
	void RemoveLogicInstances(InventorySlotData* slot, int amount);

	TArray<TUniquePtr<InventorySlotData>> m_Inventory{};
		
};
