// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/PlayerState/MiniGamePlayerState.h"
#include "Net/UnrealNetwork.h"

void AMiniGamePlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AMiniGamePlayerState, GameScore);
    DOREPLIFETIME(AMiniGamePlayerState, OutCome);
}

void AMiniGamePlayerState::AddGameScore(int32 ScoreToAdd)
{
    if (HasAuthority())
    {
        UE_LOG(LogTemp, Warning, TEXT("[SERVER] AddScore: %d -> %d"), GameScore, GameScore + ScoreToAdd);
        GameScore += ScoreToAdd;
        OnPlayerScoreChanged.Broadcast(this);
    }
    else
    {
        Multicast_AddGameScore(ScoreToAdd);
    }
}

void AMiniGamePlayerState::Multicast_AddGameScore_Implementation(int32 ScoreToAdd)
{
    if (HasAuthority())
    {
        GameScore += ScoreToAdd;
        UE_LOG(LogTemp, Warning, TEXT("[SERVER] AddScore: %d -> %d"), GameScore, GameScore + ScoreToAdd);
        OnPlayerScoreChanged.Broadcast(this);
    }
}

void AMiniGamePlayerState::BeginPlay()
{
    Super::BeginPlay();
    GameScore = 0;
}

void AMiniGamePlayerState::OnRep_GameScore()
{
    UE_LOG(LogTemp, Warning, TEXT("[CLIENT] OnRep_GameScore: %d"), GameScore);

    if (OnPlayerScoreChanged.IsBound())
    {
        UE_LOG(LogTemp, Warning, TEXT("[CLIENT] OnRep_GameScore: %d"), GameScore);
        OnPlayerScoreChanged.Broadcast(this);
    }
}

void AMiniGamePlayerState::OnRep_OutCome()
{
    if (OnGameOutComeChanged.IsBound())
    {
        OnGameOutComeChanged.Broadcast(OutCome);
    }
}
