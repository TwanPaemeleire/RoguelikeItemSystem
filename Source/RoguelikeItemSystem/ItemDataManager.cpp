// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemDataManager.h"                      
#include "AssetRegistry/AssetRegistryModule.h"
#include "Engine/StreamableManager.h"                   
#include "Engine/AssetManager.h"  
#include "Algo/Accumulate.h"

void UItemDataManager::Initialize(FSubsystemCollectionBase& Collection)
{
    FAssetRegistryModule& assetRegistry = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
    FARFilter filter;
    filter.ClassPaths.Add(UItemData::StaticClass()->GetClassPathName());
    filter.PackagePaths.Add("/Game/Items");
    filter.bRecursivePaths = true;

    TArray<FAssetData> assetDatas;
    assetRegistry.Get().GetAssets(filter, assetDatas); // This doesn't actually load yet, just gathers asset data

    FStreamableManager& streamableManager = UAssetManager::GetStreamableManager();

    for (const FAssetData& AssetData : assetDatas)
    {
        // Actually load the ItemData based on the data we have in the FArray
        UObject* loadedItem = streamableManager.LoadSynchronous(AssetData.ToSoftObjectPath(), true); // Make Async??
        if (UItemData* item = Cast<UItemData>(loadedItem))
        {
            int newItemIndex = m_AllItems.Add(item);
            m_ItemIndicesByRarity.FindOrAdd(item->Rarity).Add(newItemIndex);
            TArray<EItemCategory> categories = item->Categories;
            for (const EItemCategory& category : categories)
            {
                m_ItemIndicesByCategory.FindOrAdd(category).FindOrAdd(item->Rarity).Add(newItemIndex);
            }
        }
    }

    UE_LOG(LogTemp, Warning, TEXT("AMOUNT OF ITEMS LOADED: %d"), m_AllItems.Num());
}

UItemData* UItemDataManager::GetRandomItem(const TMap<EItemRarity, int>& dropTable) const
{
    EItemRarity randomRarity = GetRandomWeightedRarity(dropTable);
    int amountOfSelectedRarity = m_ItemIndicesByRarity[randomRarity].Num();
    int randomItemIdx = FMath::RandRange(0, amountOfSelectedRarity - 1);
    return m_AllItems[m_ItemIndicesByRarity[randomRarity][randomItemIdx]];
}

UItemData* UItemDataManager::GetRandomItem(const TMap<EItemRarity, int>& dropTable, EItemCategory category) const
{
    EItemRarity randomRarity = GetRandomWeightedRarity(dropTable);
    int amountOfSelectedRarity = m_ItemIndicesByCategory[category][randomRarity].Num();
    int randomItemIdx = FMath::RandRange(0, amountOfSelectedRarity - 1);
    return m_AllItems[m_ItemIndicesByCategory[category][randomRarity][randomItemIdx]];
}

EItemRarity UItemDataManager::GetRandomWeightedRarity(const TMap<EItemRarity, int>& dropTable) const
{
    int totalWeight = Algo::Accumulate(dropTable, 0, [](int32 accumulated, const TPair<EItemRarity, int>& dropPair)
        {
            return accumulated + dropPair.Value;
        });
    int randomNumber = FMath::RandRange(0, totalWeight - 1);

    auto result = Algo::FindByPredicate(dropTable, [&randomNumber](const TPair<EItemRarity, int>& dropPair)
        {
            if (randomNumber < dropPair.Value) return true;
            randomNumber -= dropPair.Value;
            return false;
        });

    return result->Key;
}
