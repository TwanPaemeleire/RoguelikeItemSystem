// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemDataManager.h"                      
#include "AssetRegistry/AssetRegistryModule.h"
#include "Engine/StreamableManager.h"                   
#include "Engine/AssetManager.h"  

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
        }
    }

    UE_LOG(LogTemp, Warning, TEXT("AMOUNT OF ITEMS LOADED: %d"), m_AllItems.Num());
}

UItemData* UItemDataManager::GetRandomItem() const
{
	return m_AllItems[0];
}