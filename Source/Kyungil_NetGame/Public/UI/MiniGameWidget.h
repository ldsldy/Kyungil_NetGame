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

USTRUCT(BlueprintType)
struct FPlayerScoreItem
{
    GENERATED_BODY()

public:
    const AMiniGamePlayerState* PlayerState;
    UPlayerScoreItemWidget* ScoreItemWidget;
};

/**
 * 
 */
UCLASS()
class KYUNGIL_NETGAME_API UMiniGameWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    void UpdateTimerText(int32 RemainingTime);
    void SetGameOutcomeText(EMiniGameOutcome Outcome);
    void AddPlayerScoreItem(const AMiniGamePlayerState* InPlayerState, int32 Score);
    void UpdatePlayerScore(const AMiniGamePlayerState* InPlayerState, int32 NewScore);

protected:
    virtual void NativeConstruct() override;

protected:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> TimerText;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> OutComeText;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UScrollBox> PlayerScoreList;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TSubclassOf<UPlayerScoreItemWidget> PlayerScoreItemClass;

private:
    TArray<FPlayerScoreItem> PlayerScores;
};
