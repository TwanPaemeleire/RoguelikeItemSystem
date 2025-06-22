// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemInventorySlotWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "ItemData.h"

void UItemInventorySlotWidget::SetUpItemSlot(const UItemData* itemData)
{
	ItemIcon->SetBrushFromTexture(itemData->Icon);
	Amount->SetText(FText::FromString(FString::Printf(TEXT("X1"))));
}

void UItemInventorySlotWidget::UpdateItemSlot(int amount)
{
	Amount->SetText(FText::FromString(FString::Printf(TEXT("X%d"), amount)));
}
