// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerListItemWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class KYUNGIL_NETGAME_API UPlayerListItemWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetPlayerNameText(const FString& InPlayerName);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> PlayerNameText;
};
