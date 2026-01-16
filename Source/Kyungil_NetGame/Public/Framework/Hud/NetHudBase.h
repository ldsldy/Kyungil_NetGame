// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "NetHudBase.generated.h"

/**
 * 
 */
UCLASS()
class KYUNGIL_NETGAME_API ANetHudBase : public AHUD
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	FORCEINLINE TWeakObjectPtr<UUserWidget> GetHudWidget() const { return HudWidget; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> HudWidgetClass;

private:
	UPROPERTY()
	TWeakObjectPtr<UUserWidget> HudWidget;
	
};
