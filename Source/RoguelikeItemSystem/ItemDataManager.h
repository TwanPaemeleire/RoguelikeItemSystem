// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ItemDataManager.generated.h"

class UItemData;

/**
 * 
 */
UCLASS()
class ROGUELIKEITEMSYSTEM_API UItemDataManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UItemData* GetRandomItem() const;

private:
	TArray<UItemData*> m_AllItems;
};