// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MiniGameWidget.h"
#include "UI/PlayerScoreItemWidget.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "Framework/GameState/MiniGame/MiniGameStateBase.h"
#include "Framework/PlayerState/MiniGamePlayerState.h"

void UMiniGameWidget::NativeConstruct()
{
    Super::NativeConstruct();

    APlayerController* PC = GetOwningPlayer();

    OutComeText->SetVisibility(ESlateVisibility::Collapsed);

    AMiniGameStateBase* MiniGameState = GetWorld()->GetGameState<AMiniGameStateBase>();
    if (MiniGameState)
    {
        MiniGameState->OnMiniGameTimeUpdated.AddUniqueDynamic(this, &UMiniGameWidget::UpdateTimerText);
        MiniGameState->OnGameStatePlayerListChanged.AddUniqueDynamic(this, &UMiniGameWidget::UpdatePlayerListBox);
        MiniGameState->OnGameStart.AddUniqueDynamic(this, &UMiniGameWidget::OnGameStarted);
        MiniGameState->OnStartDelayTimeUpdated.AddUniqueDynamic(this, &UMiniGameWidget::UpdateStartDelayTimer);
    }

    if (PC->HasAuthority())
    {
        UpdatePlayerListBox();
        UpdateTimerText(MiniGameState->GetRemainTime());
    }
}

void UMiniGameWidget::NativeDestruct()
{
    AMiniGameStateBase* MiniGameState = GetWorld()->GetGameState<AMiniGameStateBase>();
    MiniGameState->OnMiniGameTimeUpdated.RemoveDynamic(this, &UMiniGameWidget::UpdateTimerText);
    MiniGameState->OnGameStatePlayerListChanged.RemoveDynamic(this, &UMiniGameWidget::UpdatePlayerListBox);

    //APlayerController* PC = GetOwningPlayer();
    //AMiniGamePlayerState* MiniGamePlayerState = PC->GetPlayerState<AMiniGamePlayerState>();
    //if (MiniGamePlayerState)
    //{
    //    MiniGamePlayerState->OnPlayerScoreChanged.RemoveDynamic(this, &UMiniGameWidget::UpdatePlayerScore);
    //}

    Super::NativeDestruct();
}

void UMiniGameWidget::UpdatePlayerListBox()
{
    if (PlayerScoreItemClass)
    {
        PlayerScoreList->ClearChildren();

        AMiniGameStateBase* GameState = GetOwningPlayer()->GetWorld()->GetGameState<AMiniGameStateBase>();
        if (!GameState) return;
        if (!PlayerScoreItemClass) return;

        //////
        int32 index = 0;
        //////
        for (APlayerState* PlayerState : GameState->PlayerArray)
        {
            ////////
            FString PlayerName = FString::FromInt(index);
            index++;
            ///////

            UPlayerScoreItemWidget* PlayerListItem = CreateWidget<UPlayerScoreItemWidget>(GetOwningPlayer(), PlayerScoreItemClass);
            PlayerListItem->SetPlayerName(PlayerName); // 현재 이름 대신 ID 사용, 너무 길어서 대체
            PlayerListItem->SetPlayerScore(0);
            PlayerScoreList->AddChild(PlayerListItem);

            AMiniGamePlayerState* MiniGamePlayerState = Cast<AMiniGamePlayerState>(PlayerState);
            PlayerScoreWidgets.Add(MiniGamePlayerState, PlayerListItem);

            // 점수 변경 델리게이트 바인딩
            // 만약 랭킹 시스템이 추가되면 여기에 추가
            MiniGamePlayerState->OnPlayerScoreChanged.RemoveDynamic(this, &UMiniGameWidget::UpdatePlayerScore);
            MiniGamePlayerState->OnPlayerScoreChanged.AddUniqueDynamic(this, &UMiniGameWidget::UpdatePlayerScore);
        }
    }
}

void UMiniGameWidget::UpdateStartDelayTimer(float RemainingDelayTime)
{
    StartDelayTimerText->SetText(FText::AsNumber(FMath::CeilToInt(RemainingDelayTime)));
}

void UMiniGameWidget::OnGameStarted()
{
    APlayerController* PC = GetOwningPlayer();

    StartDelayTimerText->SetVisibility(ESlateVisibility::Collapsed);

    // 타이밍을 위한 늦은 바인딩(게임 플레이어 스테이트와의 바인딩이 많아지면 함수로 분리)
    AMiniGamePlayerState* MiniGamePlayerState = PC->GetPlayerState<AMiniGamePlayerState>();
    if (MiniGamePlayerState)
    {
        MiniGamePlayerState->OnGameResultChanged.AddUniqueDynamic(this, &UMiniGameWidget::SetGameOutcomeText);
    }
}

void UMiniGameWidget::UpdateTimerText(float RemainingTime)
{
    if (TimerText)
    {
        int32 RemainingTimeInt = FMath::Max(0, FMath::CeilToInt(RemainingTime));
        // 초를 분:초 형식으로 변환
        int32 Minutes = RemainingTimeInt / 60;
        int32 Seconds = RemainingTimeInt % 60;
        FString TimeString = FString::Printf(TEXT("%02d : %02d"), Minutes, Seconds);
        TimerText->SetText(FText::FromString(TimeString));
    }
}

void UMiniGameWidget::SetGameOutcomeText(AMiniGamePlayerState* InPlayerState)
{
    if (OutComeText)
    {
        UE_LOG(LogTemp, Warning, TEXT("SetGameOutcomeText called."));
        EMiniGameOutcome Outcome = InPlayerState->GetGameResult();
        FString OutcomeString;
        switch (Outcome)
        {
        case EMiniGameOutcome::Victory:
            OutcomeString = TEXT("승리");
            break;
        case EMiniGameOutcome::Defeat:
            OutcomeString = TEXT("패배");
            break;
        case EMiniGameOutcome::Draw:
            OutcomeString = TEXT("무승부");
            break;
        default:
            OutcomeString = TEXT("");
            break;
        }
        OutComeText->SetText(FText::FromString(OutcomeString));
        OutComeText->SetVisibility(ESlateVisibility::Visible);
    }
}

void UMiniGameWidget::UpdatePlayerScore(AMiniGamePlayerState* InPlayerState)
{
    if (PlayerScoreWidgets.IsEmpty()) return;

    UPlayerScoreItemWidget* FoundWidget = PlayerScoreWidgets.FindRef(InPlayerState);
    if (FoundWidget)
    {
        FoundWidget->SetPlayerScore(InPlayerState->GetGameScore());
    }
}

