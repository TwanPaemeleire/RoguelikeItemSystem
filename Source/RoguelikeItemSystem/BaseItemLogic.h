// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseItemLogic.generated.h"

/**
 * 
 */

UCLASS()
class ROGUELIKEITEMSYSTEM_API UBaseItemLogic : public UObject
{
	GENERATED_BODY()

public:
	UBaseItemLogic() = default;
	virtual ~UBaseItemLogic() override { UE_LOG(LogTemp, Warning, TEXT("ITEM LOGIC DESTROYED")); }

	virtual void OnPickedUp() {};
	virtual void Tick(float deltaTime) {};
	virtual void OnDropped() {};
	
};
