// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Type/NetEnum.h"
#include "MiniGamePlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerScoreChanged, AMiniGamePlayerState*, InPlayerState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameResultChanged, AMiniGamePlayerState*, InPlayerState);
/**
 * 
 */
UCLASS()
class KYUNGIL_NETGAME_API AMiniGamePlayerState : public APlayerState
{
	GENERATED_BODY()

public:
    AMiniGamePlayerState();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    UFUNCTION(BlueprintCallable, Category = "MiniGamePlayerState")
    FORCEINLINE int32 GetGameScore() const { return GameScore; }

    UFUNCTION(BlueprintCallable, Category = "MiniGamePlayerState")
    FORCEINLINE EMiniGameOutcome GetGameResult() const { return GameResult; }

    void AddGameScore_Internal(int32 ScoreToAdd);

    void SetGameResult(EMiniGameOutcome NewResult);
    void SetRank(int32 NewRank) { Rank = NewRank; }
protected:
    virtual void BeginPlay() override;

    UFUNCTION()
    virtual void OnRep_GameScore();

    UFUNCTION()
    virtual void OnRep_GameResult();

public:
    FOnPlayerScoreChanged OnPlayerScoreChanged;
    FOnGameResultChanged OnGameResultChanged;

protected:
    UPROPERTY(ReplicatedUsing = OnRep_GameScore)
    int32 GameScore = 0;

    UPROPERTY(ReplicatedUsing = OnRep_GameResult)
    EMiniGameOutcome GameResult = EMiniGameOutcome::None;

    UPROPERTY(Replicated)
    int32 Rank = -1;
};
