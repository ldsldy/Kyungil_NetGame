// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerListItemWidget.h"
#include "Components/TextBlock.h"

void UPlayerListItemWidget::SetPlayerNameText(const FString& InPlayerName)
{
	if (PlayerNameText)
	{
		PlayerNameText->SetText(FText::FromString(InPlayerName));
	}
}
