// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/GameState/MiniGame/MiniGameStateBase.h"
#include "Net/UnrealNetwork.h"
#include "Framework/PlayerState/MiniGamePlayerState.h"
#include "Framework/GameMode/NetPickupGameMode.h"

AMiniGameStateBase::AMiniGameStateBase()
{
    // 시작할 때 틱 활성화
    PrimaryActorTick.bCanEverTick = true;
}

void AMiniGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AMiniGameStateBase, RemainTime);
    DOREPLIFETIME(AMiniGameStateBase, StartDelayTime);
}

void AMiniGameStateBase::BeginPlay()
{
    Super::BeginPlay();

    if (HasAuthority())
    {
        ANetPickupGameMode* GameMode = GetWorld()->GetAuthGameMode<ANetPickupGameMode>();
        
        if (GameMode)
        {
            RemainTime = GameMode->GetGameDuration();
            if (OnMiniGameTimeUpdated.IsBound())
            {
                OnMiniGameTimeUpdated.Broadcast(RemainTime);
            }
        }
    }
}

void AMiniGameStateBase::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if (HasAuthority())
    {
        // 시작 딜레이 타이머 처리
        if(StartDelayTime > 0.f)
        {
            StartDelayTime -= DeltaSeconds;
            if(OnStartDelayTimeUpdated.IsBound())
            {
                OnStartDelayTimeUpdated.Broadcast(StartDelayTime);
            }
            if(StartDelayTime <= 0.f)
            {
                Multicast_GameStarted();
            }
            return;
        }

        // 게임 타이머 처리
        RemainTime -= DeltaSeconds;
        if (OnMiniGameTimeUpdated.IsBound())
        {
            OnMiniGameTimeUpdated.Broadcast(RemainTime);
        }

        // 타임 오버 처리
        if (RemainTime <= 0)
        {
            RemainTime = 0.0f;
            ANetPickupGameMode* GameMode = GetWorld()->GetAuthGameMode<ANetPickupGameMode>();
            GameMode->EndMiniGame();
            PrimaryActorTick.SetTickFunctionEnable(false);
            //Multicast_TimeOver();
        }
    }
}

void AMiniGameStateBase::OnRep_RemainTime()
{
    if (OnMiniGameTimeUpdated.IsBound())
    {
        OnMiniGameTimeUpdated.Broadcast(RemainTime);
    }
}

void AMiniGameStateBase::OnRep_StartDelayTime()
{
    if(OnStartDelayTimeUpdated.IsBound())
    {
        OnStartDelayTimeUpdated.Broadcast(StartDelayTime);
    }
}

void AMiniGameStateBase::Multicast_TimeOver_Implementation()
{
    if (OnGameEnd.IsBound())
    {
        OnGameEnd.Broadcast();
        // 틱 종료
        PrimaryActorTick.SetTickFunctionEnable(false);
    }
}

void AMiniGameStateBase::Multicast_GameStarted_Implementation()
{
    if (OnGameStart.IsBound())
    {
        OnGameStart.Broadcast();
    }
}