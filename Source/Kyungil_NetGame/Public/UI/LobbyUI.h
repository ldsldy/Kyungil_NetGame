// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyUI.generated.h"

class UButton;
class UTextBlock;
class UScrollBox;
/**
 * 
 */
UCLASS()
class KYUNGIL_NETGAME_API ULobbyUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "LobbyUI")
	void UpdatePlayerList();

	UFUNCTION(BlueprintCallable, Category = "LobbyUI")
	void UpdateMaxPlayerCount(int32 MaxPlayerCount);

protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class UPlayerListItemWidget> PlayerListItemClass;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> StartButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> CurrentPlayerCountText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> MaxPlayerCountText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UScrollBox> PlayerListScrollBox;
};
