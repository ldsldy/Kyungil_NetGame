// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LobbyUI.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "Framework/GameState/NetGameStateBase.h"
#include "GameFramework/PlayerState.h"
#include "UI/PlayerListItemWidget.h"

void ULobbyUI::NativeConstruct()
{
	Super::NativeConstruct();

	APlayerController* PC = GetOwningPlayer();
	if (PC->HasAuthority())
	{
		StartButton->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		StartButton->SetVisibility(ESlateVisibility::Collapsed);
	}

	UpdateMaxPlayerCount(PC->GetWorld()->GetGameState<ANetGameStateBase>()->GetMaxPlayerCount());
    UpdatePlayerList();
}


// 순환 참조 위험, 파라미터로 넘겨주는 방법 고려
void ULobbyUI::UpdatePlayerList()
{
	PlayerListScrollBox->ClearChildren();

	ANetGameStateBase* GameState = GetOwningPlayer()->GetWorld()->GetGameState<ANetGameStateBase>();
	if (!GameState) return;
	if (!PlayerListItemClass) return;

	for (APlayerState* PlayerState : GameState->PlayerArray)
	{
        UE_LOG(LogTemp, Warning, TEXT("Player Name : %s"), *PlayerState->GetPlayerName());
		UPlayerListItemWidget* PlayerListItem = CreateWidget<UPlayerListItemWidget>(GetOwningPlayer(), PlayerListItemClass);
		PlayerListItem->SetPlayerNameText(PlayerState->GetPlayerName());
		PlayerListScrollBox->AddChild(PlayerListItem);
	}
	CurrentPlayerCountText->SetText(FText::AsNumber(GameState->GetCurrentPlayerCount()));
}

void ULobbyUI::UpdateMaxPlayerCount(int32 MaxPlayerCount)
{
	UE_LOG(LogTemp, Warning, TEXT("Max Player Count : %d"), MaxPlayerCount);
	MaxPlayerCountText->SetText(FText::AsNumber(MaxPlayerCount));
}
