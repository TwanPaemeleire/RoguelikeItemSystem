// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
//#include "InventoryComponent.generated.h"

class UItemData;
class UBaseItemLogic;

struct InventorySlotData
{
	class UItemData* itemData;
	int amount;
	TArray< TUniquePtr<UBaseItemLogic>> itemLogicInstances;
};

class ROGUELIKEITEMSYSTEM_API Inventory //: public UActorComponent
{
public:
	Inventory();
	~Inventory();
	Inventory(const Inventory&) = delete;
	Inventory& operator=(const Inventory&) = delete;

	void PickupItem(UItemData* data);
	void DropItem(UItemData* data, int amount);
	void DropItemAll(UItemData* data);

	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	TArray<TUniquePtr<InventorySlotData>> m_Inventory{};
	int m_InventoryIndex{ 0 };
};
