// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item_Pickup_Score.generated.h"

UCLASS()
class KYUNGIL_NETGAME_API AItem_Pickup_Score : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem_Pickup_Score();

protected:
	virtual void BeginPlay() override;

private:
    UFUNCTION()
    void OnBeginOverlapWithPlayer(AActor* OverlappedActor, AActor* OtherActor);

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
    TObjectPtr<class USphereComponent> CollisionSphere;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
    TObjectPtr<class UStaticMeshComponent> ItemMesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
    int32 ScoreAmount = 10;
};
