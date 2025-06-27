// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "ItemData.h"  

#include "ChestData.generated.h"

/**
 * 
 */
UCLASS()
class ROGUELIKEITEMSYSTEM_API UChestData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere)
	TMap<EItemRarity, int> DropTable;

	UPROPERTY(EditAnywhere)
	bool IsNonDefaultChest;

	UPROPERTY(EditAnywhere)
	EItemCategroy ChestCategory;

	UPROPERTY(EditAnywhere)
	UStaticMesh* Mesh;

	UPROPERTY(EditAnywhere)
	UMaterial* Material;
};
