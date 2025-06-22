// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemInventoryWidget.generated.h"

class UItemData;
class UWrapBox;

/**
 * 
 */
UCLASS()
class ROGUELIKEITEMSYSTEM_API UItemInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void OnItemPickup(const UItemData* itemData);
private:

	UPROPERTY(meta = (BindWidget))
	UWrapBox* ItemInventoryWrapBox;

	UPROPERTY(EditAnywhere, Category="ItemInventory")
	TSubclassOf<UUserWidget> ItemSlotWidget;
};
