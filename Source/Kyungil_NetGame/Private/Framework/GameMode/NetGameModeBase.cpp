// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/GameMode/NetGameModeBase.h"
#include "GameFramework/GameSession.h"
#include "Kismet/GameplayStatics.h"

//#include "Framework/GameState/NetGameStateBase.h"

void ANetGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	NetLoginPlayerList.Add(NewPlayer);

    if (OnPlayerListUpdated.IsBound())
    {
        OnPlayerListUpdated.Broadcast();
    }
}

void ANetGameModeBase::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	APlayerController* ExitingPC = Cast<APlayerController>(Exiting);
	if (ExitingPC)
	{
		NetLoginPlayerList.Remove(ExitingPC);

        if (OnPlayerListUpdated.IsBound())
        {
            OnPlayerListUpdated.Broadcast();
        }
	}
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

int32 ANetGameModeBase::GetMaxPlayers() const
{
    return GameSession->MaxPlayers;
}