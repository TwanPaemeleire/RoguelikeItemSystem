#include "Inventory.h"
#include "ItemData.h"
#include "BaseItemLogic.h"

Inventory::Inventory()
{
}

Inventory::~Inventory()
{
}

//void Inventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	for (TUniquePtr<InventorySlotData>& slot : m_Inventory)
//	{
//		for (TUniquePtr<UBaseItemLogic>& itemLogic : slot->itemLogicInstances)
//		{
//			itemLogic->Tick(DeltaTime);
//		}
//	}
//}

void Inventory::PickupItem(UItemData* data)
{
	TUniquePtr<InventorySlotData>* foundInventorySlot = Algo::FindByPredicate(m_Inventory, [&](TUniquePtr<InventorySlotData>& slotData)
		{
			return data->Name.CompareIndexes(slotData->itemData->Name) == 0;
		});

	if (foundInventorySlot)
	{
		++foundInventorySlot->Get()->amount;
		//foundInventorySlot->Get()->itemLogicInstances.Emplace(MakeUnique<UBaseItemLogic>(this, data->LogicClass));
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
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("First pickup of %s, now holding %d"),
				*newSlotInfo->itemData->Name.ToString(),
				newSlotInfo->amount));
		}
		m_Inventory.Emplace(MoveTemp(newSlotInfo));
	}
}

void Inventory::DropItem(UItemData* data, int amount)
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

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Dropped %d of %s, now holding %d"),
					amount, *slot->itemData->Name.ToString(), slot->amount));
		}
	}
}

void Inventory::DropItemAll(UItemData* data)
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
