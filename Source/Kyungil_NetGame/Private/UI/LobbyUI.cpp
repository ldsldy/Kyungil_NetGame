// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LobbyUI.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "UI/PlayerListItemWidget.h"
#include "Framework/GameState/NetGameStateBase.h"
#include "GameFramework/PlayerState.h"

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
    
    // 게임 스테이트의 플레이어 리스트 변경 이벤트에 바인딩
    ANetGameStateBase* GameState = PC->GetWorld()->GetGameState<ANetGameStateBase>();
    GameState->OnGameStatePlayerListChanged.AddUniqueDynamic(this, &ULobbyUI::UpdatePlayerList);

    if (PC->HasAuthority())
    {
        UpdatePlayerList();
    }
    UpdateMaxPlayerCount(PC->GetWorld()->GetGameState<ANetGameStateBase>()->GetMaxPlayerCount());
}

void ULobbyUI::NativeDestruct()
{
    APlayerController* PC = GetOwningPlayer();
    ANetGameStateBase* GameState = PC->GetWorld()->GetGameState<ANetGameStateBase>();
    if (GameState)
    {
        GameState->OnGameStatePlayerListChanged.RemoveDynamic(this, &ULobbyUI::UpdatePlayerList);
    }
    Super::NativeDestruct();
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
        FString PlayerName = PlayerState->GetPlayerName();
		UPlayerListItemWidget* PlayerListItem = CreateWidget<UPlayerListItemWidget>(GetOwningPlayer(), PlayerListItemClass);
		PlayerListItem->SetPlayerNameText(PlayerName); // 현재 이름 대신 ID 사용, 너무 길어서 대체
		PlayerListScrollBox->AddChild(PlayerListItem);
	}
	CurrentPlayerCountText->SetText(FText::AsNumber(GameState->GetCurrentPlayerCount()));
}

void ULobbyUI::UpdateMaxPlayerCount(int32 MaxPlayerCount)
{
	MaxPlayerCountText->SetText(FText::AsNumber(MaxPlayerCount));
}
