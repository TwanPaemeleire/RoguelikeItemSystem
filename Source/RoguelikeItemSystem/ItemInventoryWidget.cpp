// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemInventoryWidget.h"
#include "Components/WrapBox.h"
#include "Components/WrapBoxSlot.h"
#include "ItemInventorySlotWidget.h"

UItemInventorySlotWidget* UItemInventoryWidget::OnItemPickup(const UItemData* itemData)
{
	UItemInventorySlotWidget* newSlot = CreateWidget<UItemInventorySlotWidget>(GetWorld(), ItemSlotWidget);
	newSlot->SetUpItemSlot(itemData);
	ItemInventoryWrapBox->AddChildToWrapBox(newSlot);
	return newSlot;
}
