// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Framework/GameState/NetGameStateBase.h"
#include "LobbyGameState.generated.h"

/**
 * 
 */
UCLASS()
class KYUNGIL_NETGAME_API ALobbyGameState : public ANetGameStateBase
{
	GENERATED_BODY()
	
public:
	virtual void UpdateNetPlayerStateList() override;

protected:
	virtual void OnRep_CurrentPlayerList() override;

private:
	void UpdateLobbyUI();
};
