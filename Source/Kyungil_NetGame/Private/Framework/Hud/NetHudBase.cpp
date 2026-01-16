// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Hud/NetHudBase.h"
#include "Blueprint/UserWidget.h"

void ANetHudBase::BeginPlay()
{
	Super::BeginPlay();

	if (HudWidgetClass)
	{
		HudWidget = CreateWidget<UUserWidget>(GetWorld(), HudWidgetClass);

		if(HudWidget.IsValid())
		{
			HudWidget->AddToViewport();
		}
	}
}
