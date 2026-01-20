// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/GameState/NetGameStateBase.h"
#include "Framework/GameMode/NetGameModeBase.h"
#include "Net/UnrealNetwork.h"


void ANetGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ANetGameStateBase, NetPlayerStateList);
	DOREPLIFETIME(ANetGameStateBase, MaxPlayerCount);
}

void ANetGameStateBase::BeginPlay()
{
    Super::BeginPlay();

    if (HasAuthority())
    {
        ANetGameModeBase* NetGameMode = GetWorld()->GetAuthGameMode<ANetGameModeBase>();
        if (NetGameMode)
        {
            MaxPlayerCount = NetGameMode->GetMaxPlayers();

            NetGameMode->OnPlayerListUpdated.AddUniqueDynamic(this, &ANetGameStateBase::UpdateNetPlayerStateList);
            UpdateNetPlayerStateList();
        }
    }
}

void ANetGameStateBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (HasAuthority())
    {
        ANetGameModeBase* NetGameMode = GetWorld()->GetAuthGameMode<ANetGameModeBase>();
        if (NetGameMode)
        {
            NetGameMode->OnPlayerListUpdated.RemoveDynamic(this, &ANetGameStateBase::UpdateNetPlayerStateList);
        }
    }
    Super::EndPlay(EndPlayReason);
}

void ANetGameStateBase::UpdateNetPlayerStateList()
{
    if (HasAuthority())
    {
        NetPlayerStateList = PlayerArray;

        if (OnGameStatePlayerListChanged.IsBound())
        {
            OnGameStatePlayerListChanged.Broadcast();
        }
    }
}

void ANetGameStateBase::OnRep_CurrentPlayerList()
{
    if (OnGameStatePlayerListChanged.IsBound())
    {
        OnGameStatePlayerListChanged.Broadcast();
    }
}

int32 ANetGameStateBase::GetCurrentPlayerCount() const
{
	return NetPlayerStateList.Num();
}

int32 ANetGameStateBase::GetMaxPlayerCount() const
{
	return MaxPlayerCount;
}