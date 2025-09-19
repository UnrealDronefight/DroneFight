#include <iostream>
#include <Windows.h>

#include "WaveManager.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyBase.h"


AWaveManager::AWaveManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AWaveManager::BeginPlay()
{
	Super::BeginPlay();

	srand((unsigned int)time(NULL));

	CurrentWave = 1;// Wave ????

	BringMonsterValue();
}

void AWaveManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// ????? Spawn??? ???
void AWaveManager::SpawnMonster()
{

	FVector SpawnLocation = SpawnPosition();
	FRotator SpawnRotation = FRotator::ZeroRotator;

	int index = rand() % MonsterClass.Num();

	GetWorld()->SpawnActor<AActor>(MonsterClass[index], SpawnLocation, SpawnRotation);

	CurrentWave++;
}

// Spawn ????? ???????? ?????? ???
FVector AWaveManager::SpawnPosition()
{
	int PositionNum = rand() % 4;
	FVector ResultPos;
	switch (PositionNum)
	{
	case 0:
		ResultPos = NorthPos->GetActorLocation();
		break;
	case 1:
		ResultPos = EastPos->GetActorLocation();
		break;
	case 2:
		ResultPos = SouthPos->GetActorLocation();
		break;
	case 3:
		ResultPos = WestPos->GetActorLocation();
		break;
	}

	return ResultPos;

}

// ?????? Value?? MonsterValues ?עק?? ?????? ???
void AWaveManager::BringMonsterValue()
{
	MonsterClassValues.Empty();

	FVector SpawnLocation = FVector(5000.f, 5000.f, 5000.f);
	AActor* SpawnedActor;
	for (int index = 0; index < MonsterClass.Num(); index++)
	{
		SpawnedActor = GetWorld()->SpawnActor<AActor>(MonsterClass[index], SpawnLocation, FRotator::ZeroRotator);

		// EnemyBase?? ©¦????
		AEnemyBase* Enemy = Cast<AEnemyBase>(SpawnedActor);
		if (Enemy)
		{
			MonsterClassValues.Add(MonsterClass[index], Enemy->Monster_Value);
		}
		SpawnedActor->Destroy();
	}

	LowStairLevel();
}

//???? value???? ???????? key?? ??? ???????????? ??????? ???
void AWaveManager::LowStairLevel()
{
	TArray<TSubclassOf<AActor>> SortedKeys;
	MonsterClassValues.GetKeys(SortedKeys);
	SortedKeys.Sort([this](const TSubclassOf<AActor>& A, const TSubclassOf<AActor>& B)
		{
			return MonsterClassValues[A] > MonsterClassValues[B]; // ???????? ????
		});
	// ????? ????? ??? (??????)
	for (const TSubclassOf<AActor>& Key : SortedKeys)
	{
		int Value = MonsterClassValues[Key];
		if (Key)
		{
			FString ClassName = Key->GetName();
			UE_LOG(LogTemp, Warning, TEXT("Monster Class: %s, Value: %d"), *ClassName, Value);
		}
	}
	// ????? ? ?עק?? ?????? MonsterClass ?עק?? ????
	MonsterClass = SortedKeys;
}


// ?????? ???? ??????? Value ??? ???

void AWaveManager::PrintMonsterClassValues()
{
	for (auto& Elem : MonsterClassValues)
	{
		UClass* MonsterUClass = Elem.Key; // tsubclassof -> uclass*
		int value = Elem.Value;

		if (MonsterUClass)
		{
			FString classname = MonsterUClass->GetName(); // ????? ??? ????????
			UE_LOG(LogTemp, Warning, TEXT("monster class: %s, value: %d"), *classname, value);

			// ??? ???? ??????
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, classname + " value: " + FString::FromInt(value));
			}
		}
	}
}