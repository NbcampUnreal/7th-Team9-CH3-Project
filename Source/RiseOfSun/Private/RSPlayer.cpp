// Fill out your copyright notice in the Description page of Project Settings.


#include "RSPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

ARSPlayer::ARSPlayer()
{
	PrimaryActorTick.bCanEverTick = true;
	
	InitializationPlayerMesh();
	InitializationPlayerCamera();
}

void ARSPlayer::BeginPlay()
{
	Super::BeginPlay();
}

void ARSPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARSPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

FDamageResult ARSPlayer::Attack(ARSCharacter* Target)
{
	FDamageResult result = ARSCharacter::Attack(Target);
	return result;
}

void ARSPlayer::InitializationPlayerMesh()
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh>
		PlayerSkeletalMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Asset/Character/QuantumCharacter/Mesh/SKM_QuantumCharacter.SKM_QuantumCharacter'"));

	if (PlayerSkeletalMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(PlayerSkeletalMesh.Object);
		GetMesh()->SetWorldLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));
	}
}

void ARSPlayer::InitializationPlayerCamera()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	if (SpringArm)
	{
		SpringArm->SetupAttachment(RootComponent);
		SpringArm->SetWorldLocation(FVector(0, 0, 55));
		SpringArm->TargetArmLength = 100;
		SpringArm->SocketOffset = FVector(0, 40, 30);
	}
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	if (Camera)
	{
		Camera->SetupAttachment(SpringArm);
	}
}
