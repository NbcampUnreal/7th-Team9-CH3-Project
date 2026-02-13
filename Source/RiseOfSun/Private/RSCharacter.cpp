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

FDamageResult ARSCharacter::Attack(ARSCharacter* Target)
{
	int32 Damage = Stat.AttackDamage; //TODO : 무기 공격력 받아와야 할 듯
	int32 FinalDamage = Target->HitDamage(Damage);
	FDamageResult result;
	result.Attacker = this;
	result.Target = Target;
	result.Damage = FinalDamage;

	return result;
}

int32 ARSCharacter::HitDamage(int32 DamageAmount)
{
	int32 Damage = DamageAmount - Stat.Defense;
	Damage = std::max(Damage, 0);

	Stat.CurrentHealth -= Damage;
	Stat.CurrentHealth = std::max(Stat.CurrentHealth, 0.0f);

	return Damage;
}

