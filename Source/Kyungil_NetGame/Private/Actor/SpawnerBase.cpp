// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/SpawnerBase.h"
#include "NavigationSystem.h"
#include "Components/SphereComponent.h"
#include "Framework/GameState/MiniGame/MiniGameStateBase.h"

ASpawnerBase::ASpawnerBase()
{
    bReplicates = true;
	PrimaryActorTick.bCanEverTick = false;

    SpawnerArea = CreateDefaultSubobject<USphereComponent>(TEXT("SpawnerArea"));
    RootComponent = SpawnerArea;
    SpawnerArea->SetSphereRadius(5000.f);
}

void ASpawnerBase::BeginPlay()
{
	Super::BeginPlay();

    if (HasAuthority())
    {
        AMiniGameStateBase* GameState = GetWorld()->GetGameState<AMiniGameStateBase>();
        if (GameState)
        {
            // 게임이 시작되면 스포너 활성화
            GameState->OnGameStart.AddDynamic(this, &ASpawnerBase::SpawnEnable);
            GameState->OnGameEnd.AddDynamic(this, &ASpawnerBase::SpawnEnd);
        }
    }
}

void ASpawnerBase::SpawnEnable()
{
    if (HasAuthority())
    {
        //if(GEngine)
        //{
        //    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("ASpawnerBase::SpawnEnable"));
        //}

        GetWorld()->GetTimerManager().SetTimer(
            SpawnTimerHandle,
            this,
            &ASpawnerBase::SpanwActor,
            SpawnDelay,
            true,
            -1.f
        );
    }
}

void ASpawnerBase::SpawnEnd()
{
    if (HasAuthority())
    {
        // 스포너 비활성화
        GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
        SpawnTimerHandle.Invalidate();
    }
}

void ASpawnerBase::SpanwActor()
{
    if (!HasAuthority()) return;
    if (!ActorToSpawn) return;

    FVector SpawnLocation = GetRandomPointInVolume();
    SpawnLocation.Z += 70.f; // 약간 띄우기

    if (GetWorld())
    {
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

        AActor* SpawnActor = GetWorld()->SpawnActor<AActor>(ActorToSpawn, SpawnLocation, FRotator::ZeroRotator, SpawnParams);
    }
}

FVector ASpawnerBase::GetRandomPointInVolume()
{
    if (!GetWorld()) return FVector::ZeroVector;

    UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
    if (!NavSys) return FVector::ZeroVector;

    FNavLocation RandomPoint;
    FVector Center = GetActorLocation();
    float Radius = SpawnerArea->GetScaledSphereRadius();

    bool bFound = NavSys->GetRandomPointInNavigableRadius(Center, Radius, RandomPoint);

    if(bFound)
    {
        return RandomPoint.Location;
    }
    return FVector::ZeroVector;
}