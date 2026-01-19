// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MiniGameWidget.h"
#include "UI/PlayerScoreItemWidget.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "Framework/PlayerState/MiniGamePlayerState.h"

void UMiniGameWidget::NativeConstruct()
{
    Super::NativeConstruct();

    OutComeText->SetVisibility(ESlateVisibility::Collapsed);
}

void UMiniGameWidget::UpdateTimerText(int32 RemainingTime)
{
    if (TimerText)
    {
        // 초를 분:초 형식으로 변환
        int32 Minutes = RemainingTime / 60;
        int32 Seconds = RemainingTime % 60;
        FString TimeString = FString::Printf(TEXT("%02d : %02d"), Minutes, Seconds);
        TimerText->SetText(FText::FromString(TimeString));
    }
}

void UMiniGameWidget::SetGameOutcomeText(EMiniGameOutcome Outcome)
{
    if (OutComeText)
    {
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

void UMiniGameWidget::AddPlayerScoreItem(const AMiniGamePlayerState* InPlayerState, int32 Score)
{
    if (PlayerScoreItemClass)
    {
        UPlayerScoreItemWidget* NewScoreItem = CreateWidget<UPlayerScoreItemWidget>(GetWorld(), PlayerScoreItemClass);
        if (NewScoreItem)
        {
            NewScoreItem->SetPlayerName(InPlayerState->GetPlayerName());
            NewScoreItem->SetPlayerScore(Score);
            PlayerScoreList->AddChild(NewScoreItem);
            PlayerScores.Add(FPlayerScoreItem{ InPlayerState, NewScoreItem });
        }
    }
}

void UMiniGameWidget::UpdatePlayerScore(const AMiniGamePlayerState* InPlayerState, int32 NewScore)
{
    if (PlayerScores.IsEmpty()) return;

    for (FPlayerScoreItem& Item : PlayerScores)
    {
        if (&Item.PlayerState == &InPlayerState)
        {
            if (Item.ScoreItemWidget)
            {
                Item.ScoreItemWidget->SetPlayerScore(NewScore);
            }
            break;
        }
    }
}

