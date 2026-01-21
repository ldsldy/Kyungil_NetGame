// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/PlayerState/MiniGamePlayerState.h"
#include "Net/UnrealNetwork.h"

AMiniGamePlayerState::AMiniGamePlayerState()
{
    bReplicates = true;
}

void AMiniGamePlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AMiniGamePlayerState, GameScore);
    DOREPLIFETIME(AMiniGamePlayerState, GameResult);
    DOREPLIFETIME(AMiniGamePlayerState, Rank);
}

void AMiniGamePlayerState::BeginPlay()
{
    Super::BeginPlay();
    GameScore = 0;
}

void AMiniGamePlayerState::OnRep_GameScore()
{
    if (OnPlayerScoreChanged.IsBound())
    {
        OnPlayerScoreChanged.Broadcast(this);
    }
}

void AMiniGamePlayerState::AddGameScore_Internal(int32 ScoreToAdd)
{
    if (HasAuthority())
    {
        GameScore += ScoreToAdd;
        OnRep_GameScore();
    }
}

void AMiniGamePlayerState::SetGameResult(EMiniGameOutcome NewResult)
{
    if (HasAuthority())
    {
        GameResult = NewResult;
        OnRep_GameResult();
    }
}

void AMiniGamePlayerState::OnRep_GameResult()
{
    if (OnGameResultChanged.IsBound())
    {
        OnGameResultChanged.Broadcast(this);
    }
}