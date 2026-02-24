// Fill out your copyright notice in the Description page of Project Settings.


#include "RSMonsterWidget.h"

#include "Actor/Character/RSMonster.h"

void URSMonsterWidget::SetOwnerMonster(ARSMonster* NewOwner)
{
	OwnerMonster = NewOwner;
}

float URSMonsterWidget::GetHPPercent() const
{
	if (!OwnerMonster) return 0.f;

	return OwnerMonster->GetCurrentHP() / OwnerMonster->GetMaxHP();
}
