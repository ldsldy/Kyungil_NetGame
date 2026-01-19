// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/GameState/MiniGame/MiniGameStateBase.h"
#include "Net/UnrealNetwork.h"
#include "Framework/Hud/NetHudBase.h"
#include "UI/MiniGameWidget.h"
#include "Framework/PlayerState/MiniGamePlayerState.h"

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
}

void AMiniGameStateBase::UpdateNetPlayerStateList()
{
    Super::UpdateNetPlayerStateList();

    if (HasAuthority())
    {

    }
}

void AMiniGameStateBase::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    RemainTime -= DeltaSeconds;
    if (HasAuthority())
    {
        UpdateTimerUI();
    }
}

void AMiniGameStateBase::OnRep_Winner()
{
    if(Winner.IsValid())
    {
        UE_LOG(LogTemp, Warning, TEXT("Winner is %s"), *Winner->GetPlayerName());
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No winner."));
    }
}

void AMiniGameStateBase::OnRep_RemainTime()
{
    UpdateTimerUI();
}

void AMiniGameStateBase::OnRep_CurrentPlayerList()
{
    UpdatePlayerListUI();
}

void AMiniGameStateBase::UpdatePlayerListUI()
{
    APlayerController* PC = GetWorld()->GetFirstPlayerController();
    if (!PC) return;
    if (!PC->GetHUD<ANetHudBase>()) return;
    if (!MiniGameWidget.IsValid())
    {
        MiniGameWidget = Cast<UMiniGameWidget>(PC->GetHUD<ANetHudBase>()->GetHudWidget());
    }
    if (MiniGameWidget.IsValid())
    {
        AMiniGamePlayerState* MiniPlayerState = PC->GetPlayerState<AMiniGamePlayerState>();
        MiniGameWidget->AddPlayerScoreItem(MiniPlayerState, 0);
    }
}


void AMiniGameStateBase::UpdateTimerUI()
{
    APlayerController* PC = GetWorld()->GetFirstPlayerController();
    if (!PC) return;
    if (!PC->GetHUD<ANetHudBase>()) return;

    if (!MiniGameWidget.IsValid())
    {
        MiniGameWidget = Cast<UMiniGameWidget>(PC->GetHUD<ANetHudBase>()->GetHudWidget());
    }
    if (MiniGameWidget.IsValid())
    {
        MiniGameWidget->UpdateTimerText(RemainTime);
    }
}
