// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/NetCharacterBase.h"

// Sets default values
ANetCharacterBase::ANetCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANetCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANetCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANetCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

