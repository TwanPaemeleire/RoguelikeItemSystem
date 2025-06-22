// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemInventorySlotWidget.generated.h"


class UImage;
class UTextBlock;
class UItemData;
/**
 * 
 */
UCLASS()
class ROGUELIKEITEMSYSTEM_API UItemInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetUpItemSlot(const UItemData* itemData);
	void UpdateItemSlot(int amount);

	UPROPERTY(meta = (BindWidget))
	UImage* ItemIcon;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Amount;
	
};
