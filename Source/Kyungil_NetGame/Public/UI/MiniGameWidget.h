// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Type/NetEnum.h"
#include "MiniGameWidget.generated.h"

class UTextBlock;
class UScrollBox;
class AMiniGamePlayerState;
class UPlayerScoreItemWidget;
class AMiniGamePlayerState;

//USTRUCT(BlueprintType)
//struct FPlayerScoreItem
//{
//    GENERATED_BODY()
//
//public:
//    int32 PlayerId;
//    UPlayerScoreItemWidget* ScoreItemWidget;
//};

/**
 * 
 */
UCLASS()
class KYUNGIL_NETGAME_API UMiniGameWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;

    UFUNCTION()
    void UpdateTimerText(float RemainingTime);
    
    UFUNCTION()
    void SetGameOutcomeText(EMiniGameOutcome Outcome);
  
    UFUNCTION()
    void UpdatePlayerListBox();
    
    UFUNCTION()
    void UpdatePlayerScore(AMiniGamePlayerState* InPlayerState);

    UFUNCTION()
    void UpdateStartDelayTimer(float RemainingDelayTime);

    UFUNCTION()
    void OnGameStarted();

private:
    void TryBindFromPlayerState();
protected:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> TimerText;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> OutComeText;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> StartDelayTimerText;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UScrollBox> PlayerScoreList;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TSubclassOf<UPlayerScoreItemWidget> PlayerScoreItemClass;

private:
    TMap<AMiniGamePlayerState*, UPlayerScoreItemWidget*> PlayerScoreWidgets;

    TWeakObjectPtr<AMiniGamePlayerState> CachedPlayerState;
};
