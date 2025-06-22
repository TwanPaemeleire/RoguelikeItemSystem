// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemInventoryWidget.h"
#include "Components/WrapBox.h"
#include "Components/WrapBoxSlot.h"

void UItemInventoryWidget::OnItemPickup(const UItemData* itemData)
{
	UUserWidget* newSlot = CreateWidget(GetWorld(), ItemSlotWidget);
	ItemInventoryWrapBox->AddChildToWrapBox(newSlot);
}
