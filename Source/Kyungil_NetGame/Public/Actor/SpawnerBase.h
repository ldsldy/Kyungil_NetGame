// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnerBase.generated.h"

UCLASS()
class KYUNGIL_NETGAME_API ASpawnerBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpawnerBase();

protected:
	virtual void BeginPlay() override;

    UFUNCTION()
    virtual void SpawnEnable();

    UFUNCTION()
    virtual void SpawnEnd();

    UFUNCTION()
    void SpanwActor();
private:
    UFUNCTION(BlueprintCallable, Category = "Spawner")
    FVector GetRandomPointInVolume();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawner")
    TObjectPtr<class USphereComponent> SpawnerArea;

    UPROPERTY(EditDefaulTSoNLY, BlueprintReadOnly, Category = "Spawner")
    TSubclassOf<AActor> ActorToSpawn;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner")
    float SpawnDelay = 3.0f;
private:
    FTimerHandle SpawnTimerHandle;
};
