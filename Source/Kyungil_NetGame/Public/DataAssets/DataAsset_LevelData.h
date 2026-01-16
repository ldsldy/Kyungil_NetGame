// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Type/NetEnum.h"
#include "DataAsset_LevelData.generated.h"

// 게임 플레이 가능한 레벨의 설정 정보
USTRUCT(BlueprintType)
struct FGameLevelConfig
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "LevelType"))
	ENetGameLevelType LevelType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UWorld> LevelWorld;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 MaxPlayers;

	bool IsValid() const
	{
		return LevelWorld != nullptr;
	}
};

/**
 * 
 */
UCLASS()
class KYUNGIL_NETGAME_API UDataAsset_LevelData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Level")
	TSoftObjectPtr<UWorld> MainMenuLevelData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Level")
	TSoftObjectPtr<UWorld> LobbyLevelData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Level")
	TArray<FGameLevelConfig> GameLevelDataArray;

public:
	UWorld* GetGameLevelWorldByType(ENetGameLevelType InLevelType) const;

	int32 GetMaxPlayersByType(ENetGameLevelType InLevelType) const;

	FString GetGameLevelLongNameByType(ENetGameLevelType InLevelType) const;
};
