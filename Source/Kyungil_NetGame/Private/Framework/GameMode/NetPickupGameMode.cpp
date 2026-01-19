// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/GameMode/NetPickupGameMode.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"
#include "Framework/GameState/MiniGame/MiniGameStateBase.h"

void ANetPickupGameMode::DetermineGameWinner()
{
    AGameStateBase* NetGameState = GetGameState<AGameStateBase>();
    
    checkf(NetGameState, TEXT("GameState is null in DetermineGameWinner"));

    APlayerState* BestPlayerState = nullptr;
    int32 TopScore = -1;

    for (APlayerState* NetPlayerState : NetGameState->PlayerArray)
    {
        if(NetPlayerState && NetPlayerState->GetScore() > TopScore)
        {
            TopScore = NetPlayerState->GetScore();
            BestPlayerState = NetPlayerState;
        }
    }

}

void ANetPickupGameMode::InitGameState()
{
    Super::InitGameState();

    AMiniGameStateBase* MiniGameState = GetGameState<AMiniGameStateBase>();
    if(MiniGameState)
    {
        MiniGameState->SetRemainTime(GameDuration);
    }
}
