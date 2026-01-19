// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerScoreItemWidget.h"
#include "Components/TextBlock.h"

void UPlayerScoreItemWidget::SetPlayerName(const FString& InPlayerName)
{
    if (PlayerNameText)
    {
        PlayerNameText->SetText(FText::FromString(InPlayerName));
    }
}

void UPlayerScoreItemWidget::SetPlayerScore(int32 InPlayerScore)
{
    if (ScoreText)
    {
        ScoreText->SetText(FText::AsNumber(InPlayerScore));
    }
}