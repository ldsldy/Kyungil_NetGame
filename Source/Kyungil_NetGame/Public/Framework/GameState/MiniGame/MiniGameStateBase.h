// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Framework/GameState/NetGameStateBase.h"
#include "MiniGameStateBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStartDelayTimeUpdated, float, NewStartDelayTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMiniGameTimeUpdated, float, NewRemainTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameStart);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameEnd);
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

    FORCEINLINE float GetRemainTime() { return RemainTime; }

protected:
    virtual void BeginPlay() override;

    virtual void Tick(float DeltaSeconds) override;

    UFUNCTION()
    void OnRep_RemainTime();

    UFUNCTION()
    void OnRep_StartDelayTime();

private:
    UFUNCTION(NetMulticast, Reliable)
    void Multicast_GameStarted();

    UFUNCTION(NetMulticast, Reliable)
    void Multicast_TimeOver();

public:
    FOnMiniGameTimeUpdated OnMiniGameTimeUpdated;
    FOnStartDelayTimeUpdated OnStartDelayTimeUpdated;
    FOnGameEnd OnGameEnd;
    FOnGameStart OnGameStart;

protected:
    UPROPERTY(ReplicatedUsing = OnRep_RemainTime)
    float RemainTime = 0.0f;

    UPROPERTY(EditDefaultsOnly, ReplicatedUsing = OnRep_StartDelayTime)
    float StartDelayTime = 5.0f;

    float ElapsedTime = 0.0f;

private:
    TWeakObjectPtr<class UMiniGameWidget> MiniGameWidget;
};
