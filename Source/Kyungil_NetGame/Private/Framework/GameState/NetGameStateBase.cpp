// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/GameState/NetGameStateBase.h"
#include "Net/UnrealNetwork.h"

ANetGameStateBase::ANetGameStateBase()
{

}

void ANetGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ANetGameStateBase, NetPlayerStateList);
	DOREPLIFETIME(ANetGameStateBase, MaxPlayerCount);
}

void ANetGameStateBase::UpdateNetPlayerStateList()
{
	NetPlayerStateList = PlayerArray;
}

void ANetGameStateBase::OnRep_CurrentPlayer()
{

}

int32 ANetGameStateBase::GetCurrentPlayerCount() const
{
	return NetPlayerStateList.Num();
}

int32 ANetGameStateBase::GetMaxPlayerCount() const
{
	return MaxPlayerCount;
}