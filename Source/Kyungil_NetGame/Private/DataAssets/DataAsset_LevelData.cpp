// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/DataAsset_LevelData.h"

int32 UDataAsset_LevelData::GetMaxPlayerByType(ENetGameLevelType InLevelType) const
{
	for (const FGameLevelConfig& LevelConfig : GameLevelDataArray)
	{
		if (LevelConfig.IsValid() && LevelConfig.LevelType == InLevelType)
		{
			return LevelConfig.MaxPlayers;
		}
	}
	return 0;
}

FString UDataAsset_LevelData::GetGameLevelLongNameByType(ENetGameLevelType InLevelType) const
{
	for (const FGameLevelConfig& LevelConfig : GameLevelDataArray)
	{
		if (LevelConfig.IsValid() && LevelConfig.LevelType == InLevelType)
		{
			UE_LOG(LogTemp, Warning, TEXT("Level Long Name : %s"), *LevelConfig.LevelWorld.GetLongPackageName());
			return LevelConfig.LevelWorld.GetLongPackageName();
		}
	}
	return FString();
}
