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
    DOREPLIFETIME(AMiniGameStateBase, Winner);
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


        RemainTime -= DeltaSeconds;
        if (OnMiniGameTimeUpdated.IsBound())
        {
            OnMiniGameTimeUpdated.Broadcast(RemainTime);
        }

        if (RemainTime <= 0)
        {
            if (OnTimerOver.IsBound())
            {
                OnTimerOver.Broadcast();
            }
            // 틱 종료
            PrimaryActorTick.SetTickFunctionEnable(false);
        }
    }
}

void AMiniGameStateBase::DetermineGameWinner()
{
    if(HasAuthority() == false)  return;
       
    APlayerState* BestPlayerState = nullptr;
    int32 TopScore = -1;
    
    for (APlayerState* NetPlayerState : PlayerArray)
    {
        AMiniGamePlayerState* MiniPlayerState = Cast<AMiniGamePlayerState>(NetPlayerState);
        if (MiniPlayerState && MiniPlayerState->GetGameScore() > TopScore)
        {
            TopScore = MiniPlayerState->GetGameScore();
            BestPlayerState = MiniPlayerState;
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

void AMiniGameStateBase::Multicast_GameStarted_Implementation()
{
    if (OnGameStart.IsBound())
    {
        OnGameStart.Broadcast();
    }
}

void AMiniGameStateBase::OnRep_Winner()
{
    if (OnTimerOver.IsBound())
    {
        OnTimerOver.Broadcast();

        // 틱 종료
        PrimaryActorTick.SetTickFunctionEnable(false);
    }
}

