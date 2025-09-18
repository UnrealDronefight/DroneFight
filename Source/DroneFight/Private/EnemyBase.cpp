#include "EnemyBase.h"

// Sets default values
AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	HP = Max_HP;

	CalculateValue();
}

void AEnemyBase::CalculateValue()
{
	Monster_Value = Max_HP + Attack + Defense + Speed;
}