// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ENetGameLevelType : uint8
{
	Menu		UMETA(DisplayName = "Menu"),
	Lobby		UMETA(DisplayName = "Lobby"),
	GamePlay01	UMETA(DisplayName = "GamePlay"),
};


UENUM(BlueprintType)
enum class EMiniGameOutcome : uint8
{
    None	UMETA(DisplayName = "None"),
    Victory	UMETA(DisplayName = "Victory"),
    Defeat	UMETA(DisplayName = "Defeat"),
    Draw	UMETA(DisplayName = "Draw"),
};