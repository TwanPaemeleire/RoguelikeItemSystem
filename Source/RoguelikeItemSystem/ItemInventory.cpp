// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemInventory.h"
#include "ItemData.h"
#include "BaseItemLogic.h"
#include "ItemInventoryWidget.h"
#include "ItemInventorySlotWidget.h"
#include "ItemDataManager.h"

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
	FInventorySlotData* foundInventorySlot = Algo::FindByPredicate(m_Inventory, [&](const FInventorySlotData& slotData)
		{
			return data->Name.CompareIndexes(slotData.itemData->Name) == 0;
		});

	if (foundInventorySlot)
	{
		++foundInventorySlot->amount;
		if (data->RunsLogicParallel)
		{
			UBaseItemLogic* NewLogic = NewObject<UBaseItemLogic>(this, foundInventorySlot->itemData->LogicClass);
			NewLogic->OnPickedUp();
			foundInventorySlot->itemLogicInstances.Emplace(NewLogic);
		}
		else
		{
			foundInventorySlot->itemLogicInstances[0]->OnPickedUp();
		}


		foundInventorySlot->widget->UpdateItemSlot(foundInventorySlot->amount);
		
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Added %s, now holding %d"),
				*foundInventorySlot->itemData->Name.ToString(),
				foundInventorySlot->amount));
		}
	}
	else
	{
		FInventorySlotData newSlotInfo;
		newSlotInfo.amount = 1;
		newSlotInfo.itemData = data;

		UBaseItemLogic* newLogic = NewObject<UBaseItemLogic>(this, newSlotInfo.itemData->LogicClass);
		newLogic->OnPickedUp();
		newSlotInfo.itemLogicInstances.Emplace(newLogic);

		newSlotInfo.widget = ItemInventoryWidget->OnItemPickup(newSlotInfo.itemData);

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("First pickup of %s, now holding %d"),
				*newSlotInfo.itemData->Name.ToString(),
				newSlotInfo.amount));
		}
		m_Inventory.Emplace(newSlotInfo);
	}
}

void UItemInventory::DropItem(UItemData* data, int amount)
{
	int32 index = m_Inventory.IndexOfByPredicate([&](const FInventorySlotData& slotData)
		{
			return data->Name.CompareIndexes(slotData.itemData->Name) == 0;
		});

	if (index != INDEX_NONE)
	{
		FInventorySlotData* slot = &m_Inventory[index];

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
	int32 index = m_Inventory.IndexOfByPredicate([&](const FInventorySlotData& slotData)
		{
			return data->Name.CompareIndexes(slotData.itemData->Name) == 0;
		});

	if (index != INDEX_NONE)
	{
		if (m_Inventory[index].itemData->RunsLogicParallel)
		{
			for (TObjectPtr<UBaseItemLogic>& itemLogic : m_Inventory[index].itemLogicInstances)
			{
				itemLogic->OnDropped();
			}
		}
		else
		{
			for (int amountIdx = 0; amountIdx < m_Inventory[index].amount; ++amountIdx)
			{
				m_Inventory[index].itemLogicInstances[0]->OnDropped();
			}
		}

		ItemInventoryWidget->OnItemFullyDropped(m_Inventory[index].widget);
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Dropped all %s"),
				*m_Inventory[index].itemData->Name.ToString()));
		}
		m_Inventory.RemoveAt(index);
	}
}


// Called when the game starts
void UItemInventory::BeginPlay()
{
	Super::BeginPlay();

	// ...	
	ItemInventoryWidget = CreateWidget<UItemInventoryWidget>(GetWorld(), ItemInventoryWidgetClass, TEXT("ItemInventory")); // Bind ownership to player instead of world in future?
	ItemInventoryWidget->AddToViewport();

	UItemDataManager* manager = GetWorld()->GetGameInstance()->GetSubsystem<UItemDataManager>();
	UItemData* item = manager->GetRandomItem();
	PickupItem(item);
	PickupItem(item);
	PickupItem(item);
	PickupItem(item);
	DropItem(item, 2);
	DropItem(item, 4);
}


// Called every frame
void UItemInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	for (FInventorySlotData& slot : m_Inventory)
	{
		for (TObjectPtr<UBaseItemLogic>& itemLogic : slot.itemLogicInstances)
		{
			itemLogic->Tick(DeltaTime);
		}
	}
}

void UItemInventory::RemoveLogicInstances(FInventorySlotData* slot, int amount)
{
	for (int logicIdx = 0; logicIdx < amount; ++logicIdx)
	{
		if (slot->itemData->RunsLogicParallel) slot->itemLogicInstances[logicIdx]->OnDropped();
		else slot->itemLogicInstances[0]->OnDropped();
	}
	if (slot->itemData->RunsLogicParallel) slot->itemLogicInstances.RemoveAt(0, amount);
}

