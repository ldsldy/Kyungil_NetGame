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
    DOREPLIFETIME(AMiniGamePlayerState, OutCome);
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
        UE_LOG(LogTemp, Warning, TEXT("[CLIENT] OnRep_GameScore: %d"), GameScore);
        OnPlayerScoreChanged.Broadcast(this);
    }
}

void AMiniGamePlayerState::AddGameScore_Internal(int32 ScoreToAdd)
{
    UE_LOG(LogTemp, Warning, TEXT("[SERVER] AddScore: %d -> %d"), GameScore, GameScore + ScoreToAdd);
    GameScore += ScoreToAdd;
    OnRep_GameScore();
}

void AMiniGamePlayerState::OnRep_OutCome()
{
    if (OnGameOutComeChanged.IsBound())
    {
        OnGameOutComeChanged.Broadcast(OutCome);
    }
}