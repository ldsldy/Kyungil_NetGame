// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "DataAssets/DataAsset_LevelData.h"
#include "NetGameInstance.generated.h"

/**
 *  레벨 전환 및 네트워크 관련 기능을 담당하는 게임 인스턴스 클래스
 */
UCLASS()
class KYUNGIL_NETGAME_API UNetGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UNetGameInstance();
	
	virtual void Init() override;

	// 로비 서버 생성
	UFUNCTION(BlueprintCallable, Category = "Network")
	void CreateLobbyServer(ENetGameLevelType InLevelTypeForPlayerCount);

	// 게임 서버 생성
	UFUNCTION(BlueprintCallable, Category = "Network")
	void CreateGameServer(ENetGameLevelType InLevelType);

	// 서버 참여
	UFUNCTION(BlueprintCallable, Category = "Network")
	void JoinServer(FString& IPAddress);

	// 서버 연결 종료
	UFUNCTION(BlueprintCallable, Category = "Network")
	void DisconnectServer();

	FORCEINLINE const FString& GetServerIP() const { return ServerIP; }
public:
	UPROPERTY(EditDefaultsOnly, Category = "Network|Level")
	TSoftObjectPtr<UDataAsset_LevelData> LevelDataAsset;

	UPROPERTY(EditDefaultsOnly, Category = "Network")
	FString ServerIP;
};
