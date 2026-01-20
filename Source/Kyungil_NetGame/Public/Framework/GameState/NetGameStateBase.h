// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "NetGameStateBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameStatePlayerListChanged);
/**
 * 
 */
UCLASS()
class KYUNGIL_NETGAME_API ANetGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable, Category = "NetGameStateBase")
	int32 GetCurrentPlayerCount() const;

	UFUNCTION(BlueprintCallable, Category = "NetGameStateBase")
	int32 GetMaxPlayerCount() const;

protected:
    virtual void BeginPlay() override;

    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    UFUNCTION()
    virtual void UpdateNetPlayerStateList();


	UFUNCTION()
	virtual void OnRep_CurrentPlayerList();

public:
    FOnGameStatePlayerListChanged OnGameStatePlayerListChanged;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NetGameStateBase", ReplicatedUsing = OnRep_CurrentPlayerList)
	TArray<APlayerState*> NetPlayerStateList;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NetGameStateBase", Replicated)
	int32 MaxPlayerCount = 1;
};
