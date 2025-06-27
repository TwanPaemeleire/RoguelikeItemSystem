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

	UItemData* GetRandomItem(const TMap<EItemRarity, int>& dropTable) const;
	UItemData* GetRandomItem(const TMap<EItemRarity, int>& dropTable, EItemCategory category) const;

private:
	EItemRarity GetRandomWeightedRarity(const TMap<EItemRarity, int>& dropTable) const;

	TArray<UItemData*> m_AllItems;
	TMap<EItemRarity, TArray<int>> m_ItemIndicesByRarity;
	TMap<EItemCategory, TMap<EItemRarity, TArray<int>>> m_ItemIndicesByCategory;
};