// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerScoreItemWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class KYUNGIL_NETGAME_API UPlayerScoreItemWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    void SetPlayerName(const FString& InPlayerName);
    void SetPlayerScore(int32 InPlayerScore);

protected:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> PlayerNameText;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> ScoreText;
};
