// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/GameState/LobbyGameState.h"
#include "UI/LobbyUI.h"
#include "Framework/Hud/NetHudBase.h"

void ALobbyGameState::UpdateNetPlayerStateList()
{
	Super::UpdateNetPlayerStateList();

	if (HasAuthority())
	{
		UpdateLobbyUI();
	}
}

void ALobbyGameState::OnRep_CurrentPlayer()
{
	Super::OnRep_CurrentPlayer();

	UpdateLobbyUI();
}

void ALobbyGameState::UpdateLobbyUI()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();

	UE_LOG(LogTemp, Warning, TEXT("ALobbyGameState::UpdateLobbyUI Called"));

	if (!PC) return;
	if (!PC->GetHUD<ANetHudBase>()) return;

	ULobbyUI* LobbyUI = Cast<ULobbyUI>(PC->GetHUD<ANetHudBase>()->GetHudWidget());
	if (LobbyUI)
	{
		LobbyUI->UpdatePlayerList();
	}
}
