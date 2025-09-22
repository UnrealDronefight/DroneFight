#include "EnemyBase.h"
#include "WaveManager.h"
#include "TimerManager.h"
#include "Engine/World.h"

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

    if (GetWorld())
    {
        GetWorld()->GetTimerManager().SetTimer(
            DestroyTimerHandle,
            this,
            &AEnemyBase::DestroySelf,
            5.0f,   // 딜레이 (초)
            false   // 반복 여부
        );
    }
}

void AEnemyBase::CalculateValue()
{
    Monster_Value = Max_HP + Attack + Defense + Speed;
}

void AEnemyBase::InitializeEnemy(AWaveManager* myown)
{
    _playerController = myown;
}

void AEnemyBase::DestroySelf()
{
    if (!IsPendingKillPending())
    {
        if (_playerController != nullptr)
        {
            _playerController->MonsterDeath();

        }
        Destroy();
    }
}