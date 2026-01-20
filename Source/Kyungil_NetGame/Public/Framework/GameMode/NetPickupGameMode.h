// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Framework/GameMode/NetGameModeBase.h"
#include "NetPickupGameMode.generated.h"

/**
 * 
 */
UCLASS()
class KYUNGIL_NETGAME_API ANetPickupGameMode : public ANetGameModeBase
{
	GENERATED_BODY()
	
public:
    FORCEINLINE float GetGameDuration() const { return GameDuration; }

    void EndMiniGame();

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameMode")
    float GameDuration = 60.f; // 게임 시간 (초)
};
