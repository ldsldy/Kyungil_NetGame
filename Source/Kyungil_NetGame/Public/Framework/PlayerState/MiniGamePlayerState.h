// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Type/NetEnum.h"
#include "MiniGamePlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerScoreChanged, AMiniGamePlayerState*, InPlayerState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameOutComeChanged, EMiniGameOutcome, NewOutcome);
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

    void AddGameScore_Internal(int32 ScoreToAdd);
protected:
    virtual void BeginPlay() override;

    UFUNCTION()
    virtual void OnRep_GameScore();

    UFUNCTION()
    virtual void OnRep_OutCome();

public:
    FOnPlayerScoreChanged OnPlayerScoreChanged;
    FOnGameOutComeChanged OnGameOutComeChanged;

protected:
    UPROPERTY(ReplicatedUsing = OnRep_GameScore)
    int32 GameScore = 0;

    UPROPERTY(ReplicatedUsing = OnRep_OutCome)
    EMiniGameOutcome OutCome = EMiniGameOutcome::None;
};
