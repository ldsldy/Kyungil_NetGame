#include "Framework/Instance/NetGameInstance.h"
#include "Kismet/GameplayStatics.h"

UNetGameInstance::UNetGameInstance()
{
	ServerIP = "127.0.0.1";
}

void UNetGameInstance::Init()
{
	Super::Init();

	if (!LevelDataAsset.IsNull())
	{
		LevelDataAsset.LoadSynchronous();
	}
}

void UNetGameInstance::CreateLobbyServer(ENetGameLevelType InLevelType)
{
	checkf(!LevelDataAsset.IsNull(), TEXT("LevelDataAsset is nullptr"));

	UWorld* World = GetWorld();
	checkf(World, TEXT("World is nullptr"));

	UDataAsset_LevelData* Asset = LevelDataAsset.Get();
	checkf(Asset, TEXT("LevelDataAsset is nullptr"));

	// 로비 최대 인원은 시작하고자 하는 레벨의 최대 인원으로 설정
	FString MapPath = Asset->LobbyLevelData.GetLongPackageName();
	FString Options = FString::Printf(TEXT("listen?maxplayers=%d"),
		Asset->GetMaxPlayersByType(InLevelType)
	);

	UGameplayStatics::OpenLevel(World, FName(*MapPath), true, Options);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Create Lobby Server : %s"), *MapPath));
	}
}

void UNetGameInstance::CreateGameServer(ENetGameLevelType InLevelType)
{
	checkf(!LevelDataAsset.IsNull(), TEXT("LevelDataAsset is nullptr"));

	LevelDataAsset.LoadSynchronous();
	UWorld* World = GetWorld();
	checkf(World, TEXT("World is nullptr"));

	UDataAsset_LevelData* Asset = LevelDataAsset.Get();
	checkf(Asset, TEXT("LevelDataAsset is nullptr"));

	// 로비 인원을 데리고 게임 플레이 레벨로 이동
	FString TravelURL = FString::Printf(TEXT("%s?listen?maxplayers=%d"),
		*Asset->GetGameLevelLongNameByType(InLevelType),
		Asset->GetMaxPlayersByType(InLevelType)
	);

	World->ServerTravel(TravelURL);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Create Game Server : %s"), *TravelURL));
	}
}

void UNetGameInstance::JoinServer(FString& IPAddress)
{
	if (IPAddress.IsEmpty())
	{
		IPAddress = ServerIP;
	}

	UWorld* World = GetWorld();
	checkf(World, TEXT("World is nullptr"));

	APlayerController* PC = UGameplayStatics::GetPlayerController(World, 0);
	checkf(PC, TEXT("Player Controller is nullptr"));

	//주소로 서버 접속
	PC->ClientTravel(IPAddress, ETravelType::TRAVEL_Absolute);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Join Server : %s"), *IPAddress));
	}
}

void UNetGameInstance::DisconnectServer()
{
	checkf(!LevelDataAsset.IsNull(), TEXT("LevelDataAsset is nullptr"));

	LevelDataAsset.LoadSynchronous();
	UWorld* World = GetWorld();
	checkf(World, TEXT("World is nullptr"));

	APlayerController* PC = UGameplayStatics::GetPlayerController(World, 0);
	checkf(PC, TEXT("Player Controller is nullptr"));

	UDataAsset_LevelData* Asset = LevelDataAsset.Get();
	checkf(Asset, TEXT("LevelDataAsset is nullptr"));

	// 레벨 에셋으로 메인 메뉴 디오
	PC->ClientTravel(Asset->LobbyLevelData.GetLongPackageName(), ETravelType::TRAVEL_Absolute);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Yellow, TEXT("서버 접속 종료"));
	}
}
