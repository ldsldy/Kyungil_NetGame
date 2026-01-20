// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/GameMode/NetPickupGameMode.h"
#include "Framework/PlayerState/MiniGamePlayerState.h"
#include "GameFramework/GameStateBase.h"

void ANetPickupGameMode::EndMiniGame()
{
    TArray<AMiniGamePlayerState*> PlayerStates;

    for (APlayerState* PS : GameState->PlayerArray)
    {
        AMiniGamePlayerState* MiniGamePS = Cast<AMiniGamePlayerState>(PS);
        if (MiniGamePS)
        {
            PlayerStates.Add(MiniGamePS);
        }
    }

    // 점수 기준으로 플레이어 정렬
    PlayerStates.Sort([](const AMiniGamePlayerState& A, const AMiniGamePlayerState& B)
    {
        return A.GetGameScore() > B.GetGameScore();
    });

    // 순위 및 결과 할당
    for (int32 i = 0; i < PlayerStates.Num(); i++)
    {
        AMiniGamePlayerState* MiniGamePS = PlayerStates[i];
        MiniGamePS->SetRank(i + 1);
        if (i == 0)
        {
            MiniGamePS->SetGameResult(EMiniGameOutcome::Victory);
        }
        else
        {
            MiniGamePS->SetGameResult(EMiniGameOutcome::Defeat);
        }
    }
}
