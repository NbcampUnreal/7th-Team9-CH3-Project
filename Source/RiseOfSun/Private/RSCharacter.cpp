// Fill out your copyright notice in the Description page of Project Settings.


#include "RSCharacter.h"


ARSCharacter::ARSCharacter()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	
}

// Called when the game starts or when spawned
void ARSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ARSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

