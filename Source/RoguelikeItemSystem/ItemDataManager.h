// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ItemData.h"   
#include "ItemDataManager.generated.h"

/**
 * 
 */
UCLASS()
class ROGUELIKEITEMSYSTEM_API UItemDataManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UItemData* GetRandomItem(const TArray<TPair<EItemRarity, int>>& weightedRarities) const;

private:
	EItemRarity GetRandomWeightedRarity(const TArray<TPair<EItemRarity, int>>& weightedRarities) const;

	TArray<UItemData*> m_AllItems;
	TMap<EItemRarity, TArray<int>> m_ItemIndicesByRarity;
};