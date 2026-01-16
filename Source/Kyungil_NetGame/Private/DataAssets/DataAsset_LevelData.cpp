// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/DataAsset_LevelData.h"

UWorld* UDataAsset_LevelData::GetGameLevelWorldByType(ENetGameLevelType InLevelType) const
{
	for (const FGameLevelConfig& LevelConfig : GameLevelDataArray)
	{
		if(LevelConfig.IsValid() && LevelConfig.LevelType == InLevelType)
		{
			return LevelConfig.LevelWorld.LoadSynchronous();
		}
	}
	return nullptr;
}

int32 UDataAsset_LevelData::GetMaxPlayersByType(ENetGameLevelType InLevelType) const
{
	for(const FGameLevelConfig& LevelConfig : GameLevelDataArray)
	{
		if(LevelConfig.IsValid() && LevelConfig.LevelType == InLevelType)
		{
			return LevelConfig.MaxPlayers;
		}
	}
	return 1;
}

FString UDataAsset_LevelData::GetGameLevelLongNameByType(ENetGameLevelType InLevelType) const
{
	for (const FGameLevelConfig& LevelConfig : GameLevelDataArray)
	{
		if (LevelConfig.IsValid() && LevelConfig.LevelType == InLevelType)
		{
			return LevelConfig.LevelWorld.GetLongPackageName();
		}
	}
	return FString();
}
