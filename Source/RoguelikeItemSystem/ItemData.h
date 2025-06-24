// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemData.generated.h"

class UBaseItemLogic;

/**
 * 
 */

UENUM()
enum class EItemRarity : uint8
{
	White,
	Green,
	Red,
	Orange
};


UCLASS(BlueprintType)
class ROGUELIKEITEMSYSTEM_API UItemData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	FName Name;

	UPROPERTY(EditAnywhere)
	FText Description;

	UPROPERTY(EditAnywhere)
	EItemRarity Rarity;

	UPROPERTY(EditAnywhere)
	UStaticMesh* Mesh;

	UPROPERTY(EditAnywhere)
	UMaterial* Material;

	UPROPERTY(EditAnywhere)
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere)
	bool RunsLogicParallel;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UBaseItemLogic> LogicClass;
};
