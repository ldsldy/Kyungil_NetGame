// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NetCharacterBase.generated.h"

UCLASS()
class KYUNGIL_NETGAME_API ANetCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ANetCharacterBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
