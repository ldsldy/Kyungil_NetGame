// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/GameState/LobbyGameState.h"
#include "UI/LobbyUI.h"
#include "Framework/Hud/NetHudBase.h"

void ALobbyGameState::UpdateNetPlayerStateList()
{
	Super::UpdateNetPlayerStateList();

    // 서버에서만 UI 업데이트 호출
	if (HasAuthority())
	{
		UpdateLobbyUI();
	}
}

void ALobbyGameState::OnRep_CurrentPlayerList()
{
	Super::OnRep_CurrentPlayerList();

	UpdateLobbyUI();
}

void ALobbyGameState::UpdateLobbyUI()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();

	if (!PC) return;
	if (!PC->GetHUD<ANetHudBase>()) return;

    UE_LOG(LogTemp, Warning, TEXT("ALobbyGameState::UpdateLobbyUI Called"));

	ULobbyUI* LobbyUI = Cast<ULobbyUI>(PC->GetHUD<ANetHudBase>()->GetHudWidget());
	if (LobbyUI)
	{
		LobbyUI->UpdatePlayerList();
	}
}
