// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemInventory.h"
#include "ItemData.h"
#include "BaseItemLogic.h"

// Sets default values for this component's properties
UItemInventory::UItemInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UItemInventory::PickupItem(UItemData* data)
{
	TUniquePtr<InventorySlotData>* foundInventorySlot = Algo::FindByPredicate(m_Inventory, [&](TUniquePtr<InventorySlotData>& slotData)
		{
			return data->Name.CompareIndexes(slotData->itemData->Name) == 0;
		});

	if (foundInventorySlot)
	{
		++foundInventorySlot->Get()->amount;

		UBaseItemLogic* NewLogic = NewObject<UBaseItemLogic>(this, foundInventorySlot->Get()->itemData->LogicClass);
		foundInventorySlot->Get()->itemLogicInstances.Emplace(NewLogic);
		
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Added %s, now holding %d"),
				*foundInventorySlot->Get()->itemData->Name.ToString(),
				foundInventorySlot->Get()->amount));
		}
	}
	else
	{
		TUniquePtr<InventorySlotData> newSlotInfo = MakeUnique<InventorySlotData>();
		newSlotInfo.Get()->amount = 1;
		newSlotInfo.Get()->itemData = data;

		UBaseItemLogic* NewLogic = NewObject<UBaseItemLogic>(this, newSlotInfo->itemData->LogicClass);
		newSlotInfo->itemLogicInstances.Emplace(NewLogic);

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("First pickup of %s, now holding %d"),
				*newSlotInfo->itemData->Name.ToString(),
				newSlotInfo->amount));
		}
		m_Inventory.Emplace(MoveTemp(newSlotInfo));
	}
}

void UItemInventory::DropItem(UItemData* data, int amount)
{
	int32 index = m_Inventory.IndexOfByPredicate([&](const TUniquePtr<InventorySlotData>& slotData)
		{
			return data->Name.CompareIndexes(slotData->itemData->Name) == 0;
		});

	if (index != INDEX_NONE)
	{
		InventorySlotData* slot = m_Inventory[index].Get();

		if (amount >= slot->amount)
		{
			DropItemAll(data);
			return;
		}

		slot->amount -= amount;
		RemoveLogicInstances(slot, amount);

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Dropped %d of %s, now holding %d"),
				amount, *slot->itemData->Name.ToString(), slot->amount));
		}
	}
}

void UItemInventory::DropItemAll(UItemData* data)
{
	int32 index = m_Inventory.IndexOfByPredicate([&](const TUniquePtr<InventorySlotData>& slotData)
		{
			return data->Name.CompareIndexes(slotData->itemData->Name) == 0;
		});

	if (index != INDEX_NONE)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Dropped all %s"),
				*m_Inventory[index]->itemData->Name.ToString()));
		}
		m_Inventory.RemoveAt(index);
	}
}


// Called when the game starts
void UItemInventory::BeginPlay()
{
	Super::BeginPlay();

	// ...	
}


// Called every frame
void UItemInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	for (TUniquePtr<InventorySlotData>& slot : m_Inventory)
	{
		for (TObjectPtr<UBaseItemLogic>& itemLogic : slot->itemLogicInstances)
		{
			itemLogic->Tick(DeltaTime);
		}
	}
}

void UItemInventory::RemoveLogicInstances(InventorySlotData* slot, int amount)
{
	amount = FMath::Clamp(amount, 0, slot->itemLogicInstances.Num());
	slot->itemLogicInstances.RemoveAt(0, amount);
}

