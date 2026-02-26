// Fill out your copyright notice in the Description page of Project Settings.


#include "RSGameMode.h"

#include "Actor/Character/RSPlayer.h"
#include "Actor/Character/Controller/RSPlayerController.h"
#include "RSGameState.h"

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

