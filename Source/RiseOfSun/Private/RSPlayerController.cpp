// Fill out your copyright notice in the Description page of Project Settings.


#include "RSPlayerController.h"

void ARSPlayerController::BeginPlay()
{
    Super::BeginPlay();

    // 로컬 플레이어에서만 실행
    if (IsLocalController())
    {
        if (GEngine)
        {
            GEngine->Exec(GetWorld(), TEXT("r.SetRes 1920x1080w"));
        }
    }
}