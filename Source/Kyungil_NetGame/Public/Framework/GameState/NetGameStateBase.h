// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "NetGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class KYUNGIL_NETGAME_API ANetGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	ANetGameStateBase();

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable, Category = "NetGameStateBase")
	int32 GetCurrentPlayerCount() const;

	UFUNCTION(BlueprintCallable, Category = "NetGameStateBase")
	int32 GetMaxPlayerCount() const;

	UFUNCTION(BlueprintCallable, Category = "NetGameStateBase")
	FORCEINLINE void SetMaxPlayerCount(int32 InMaxPlayerCount) { MaxPlayerCount = InMaxPlayerCount; }

	virtual void UpdateNetPlayerStateList();

protected:
	UFUNCTION()
	virtual void OnRep_CurrentPlayerList();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NetGameStateBase", ReplicatedUsing = OnRep_CurrentPlayerList)
	TArray<APlayerState*> NetPlayerStateList;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NetGameStateBase", Replicated)
	int32 MaxPlayerCount = 1;
};
