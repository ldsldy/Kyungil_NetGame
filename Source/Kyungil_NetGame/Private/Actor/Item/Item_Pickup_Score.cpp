#include "Actor/Item/Item_Pickup_Score.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "NetPlayerController.h"

AItem_Pickup_Score::AItem_Pickup_Score()
{
	PrimaryActorTick.bCanEverTick = false;
    bReplicates = true;
    SetReplicateMovement(true);

    CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
    RootComponent = CollisionSphere;
    CollisionSphere->SetSphereRadius(75.0f);
    CollisionSphere->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));

    ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
    ItemMesh->SetupAttachment(RootComponent);
    ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AItem_Pickup_Score::BeginPlay()
{
	Super::BeginPlay();
	
    OnActorBeginOverlap.AddDynamic(this, &AItem_Pickup_Score::OnBeginOverlapWithPlayer);
}

void AItem_Pickup_Score::OnBeginOverlapWithPlayer(AActor* OverlappedActor, AActor* OtherActor)
{
    if (HasAuthority())
    {
        if (ANetPlayerController* NetPlayerController = OtherActor->GetInstigatorController<ANetPlayerController>())
        {
            NetPlayerController->Server_AddGameScore(ScoreAmount);
        }

        this->Destroy();
    }
}
