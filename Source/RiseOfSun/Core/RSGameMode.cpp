// Fill out your copyright notice in the Description page of Project Settings.


#include "RSGameMode.h"

#include "Actor/Character/RSPlayer.h"
#include "Actor/Character/Controller/RSPlayerController.h"
#include "RSGameState.h"
#include "Actor/Spawn/RSMonsterSpawnVolume.h"
#include "Kismet/GameplayStatics.h"
#include "Widget/RSMainMenuWidget.h"


ARSGameMode::ARSGameMode()
{
	static ConstructorHelpers::FClassFinder<ARSPlayer>
		PlayerCharacter(TEXT("/Script/Engine.Blueprint'/Game/BluePrint/Character/BP_RSPlayer.BP_RSPlayer_C'"));
	
	if (PlayerCharacter.Class)//예외처리
	{
		DefaultPawnClass = PlayerCharacter.Class;
		
	}
	PlayerControllerClass = ARSPlayerController::StaticClass();
	DefaultPawnClass = ARSPlayerController::StaticClass();
	GameStateClass = ARSGameMode::StaticClass();
}

void  ARSGameMode::OnPlayerDied()
{
	if (!MenuClass)
	{
		UE_LOG(LogTemp, Error, TEXT("MenuClass is null"));
		return;
	}

	URSMainMenuWidget* Widget = CreateWidget<URSMainMenuWidget>(GetWorld(), MenuClass);
	if (!Widget)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create menu widget"));
		return;
	}
	// 게임오버 UI
	TArray<AActor*> FoundVolumes;
	UGameplayStatics::GetAllActorsOfClass(
		GetWorld(),
		ARSMonsterSpawnVolume::StaticClass(),
		FoundVolumes
	);

	for (AActor* Actor : FoundVolumes)
	{
		ARSMonsterSpawnVolume* Volume = Cast<ARSMonsterSpawnVolume>(Actor);
		if (Volume)
		{
			Volume->StopSpawning();
		}
	}
	

	Widget->MenuMode = EMenuMode::GameOver;
	Widget->AddToViewport();
}

void ARSGameMode::GameClear()
{
	URSMainMenuWidget* Widget = CreateWidget<URSMainMenuWidget>(GetWorld(), MenuClass);
	
	Widget->MenuMode = EMenuMode::GameClear;
	Widget->AddToViewport();
	
	
}

