// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/GameMode/NetGameModeBase.h"
#include "GameFramework/GameSession.h"
#include "Framework/GameState/NetGameStateBase.h"
#include "Kismet/GameplayStatics.h"

void ANetGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	NetLoginPlayerList.Add(NewPlayer);

	UpdatePlayerList();
}

void ANetGameModeBase::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	APlayerController* ExitingPC = Cast<APlayerController>(Exiting);
	if (ExitingPC)
	{
		NetLoginPlayerList.Remove(ExitingPC);

		UpdatePlayerList();
	}
}

void ANetGameModeBase::UpdatePlayerList()
{
	ANetGameStateBase* NetGameState = GetGameState<ANetGameStateBase>();
	if (!NetGameState) return;

	NetGameState->UpdateNetPlayerStateList();
}

int32 ANetGameModeBase::GetMaxPlayers() const
{
	return GameSession->MaxPlayers;
}

void ANetGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	int32 MaxPlayersOption = UGameplayStatics::GetIntOption(Options, TEXT("maxplayers"), 0);
	if (MaxPlayersOption > 0 && GameSession)
	{
		GameSession->MaxPlayers = MaxPlayersOption;
	}
}

void ANetGameModeBase::InitGameState()
{
	Super::InitGameState();

	// 게임 모드가 시작될 때 최대 플레이어 수를 게임 상태에 설정
	ANetGameStateBase* NetGameState = GetGameState<ANetGameStateBase>();
	if (NetGameState)
	{
		NetGameState->SetMaxPlayerCount(GetMaxPlayers());
	}
}