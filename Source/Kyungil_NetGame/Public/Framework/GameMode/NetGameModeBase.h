// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NetGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerListUpdated);

/**
 * 
 */
UCLASS()
class KYUNGIL_NETGAME_API ANetGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;
	
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	void UpdatePlayerList();
	int32 GetMaxPlayers() const;

public:
    FOnPlayerListUpdated OnPlayerListUpdated;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NetGameModeBase")
	TArray<APlayerController*> NetLoginPlayerList;
};
