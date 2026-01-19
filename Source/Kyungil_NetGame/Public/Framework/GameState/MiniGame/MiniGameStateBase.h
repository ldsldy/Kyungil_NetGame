// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Framework/GameState/NetGameStateBase.h"
#include "MiniGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class KYUNGIL_NETGAME_API AMiniGameStateBase : public ANetGameStateBase
{
	GENERATED_BODY()

public:
    AMiniGameStateBase();
	
    virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

    void SetRemainTime(float InRemainTime) { RemainTime = InRemainTime; }

    virtual void UpdateNetPlayerStateList() override;

protected:
    virtual void Tick(float DeltaSeconds) override;

    UFUNCTION()
    void OnRep_Winner();

    UFUNCTION()
    void OnRep_RemainTime();

    virtual void OnRep_CurrentPlayerList() override;

private:
    void UpdatePlayerListUI();
    void UpdateTimerUI();

protected:
    UPROPERTY(ReplicatedUsing = OnRep_Winner)
    TWeakObjectPtr<APlayerState> Winner;

    UPROPERTY(Replicated = OnRep_RemainTime)
    float RemainTime = 0.0f;

    float ElapsedTime = 0.0f;

private:
    TWeakObjectPtr<class UMiniGameWidget> MiniGameWidget;
};
