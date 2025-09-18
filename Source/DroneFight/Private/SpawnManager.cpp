#include <iostream>
#include <Windows.h>

#include "SpawnManager.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyBase.h"


ASpawnManager::ASpawnManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASpawnManager::BeginPlay()
{
	Super::BeginPlay();

	srand((unsigned int)time(NULL));

	CurrentWave = 1;// Wave 초기화

	BringMonsterValue();
}

void ASpawnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// 몬스터를 Spawn하는 함수
void ASpawnManager::SpawnMonster()
{
	
		FVector SpawnLocation = SpawnPosition();
		FRotator SpawnRotation = FRotator::ZeroRotator;

		int index = rand() % MonsterClass.Num();

		GetWorld()->SpawnActor<AActor>(MonsterClass[index], SpawnLocation, SpawnRotation);

		CurrentWave++;
}

// Spawn 위치를 랜덤으로 반환하는 함수
FVector ASpawnManager::SpawnPosition()
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

// 몬스터의 Value를 MonsterValues 배열에 추가하는 함수
void ASpawnManager::BringMonsterValue()
{
	MonsterClassValues.Empty();

	FVector SpawnLocation = FVector (5000.f, 5000.f, 5000.f);
	AActor* SpawnedActor;
	for(int index = 0; index < MonsterClass.Num(); index++)
	{
		SpawnedActor = GetWorld()->SpawnActor<AActor>(MonsterClass[index], SpawnLocation, FRotator::ZeroRotator);

		// EnemyBase로 캐스팅
		AEnemyBase* Enemy = Cast<AEnemyBase>(SpawnedActor);
		if (Enemy)
		{
			MonsterClassValues.Add(MonsterClass[index], Enemy->Monster_Value);
		}
		SpawnedActor->Destroy();
	}

	LowStairLevel();
}

//맵을 value값을 기준으로 key와 함께 내림차순으로 정렬하는 함수
void ASpawnManager::LowStairLevel()
{
	TArray<TSubclassOf<AActor>> SortedKeys;
	MonsterClassValues.GetKeys(SortedKeys);
	SortedKeys.Sort([this](const TSubclassOf<AActor>& A, const TSubclassOf<AActor>& B)
	{
		return MonsterClassValues[A] > MonsterClassValues[B]; // 내림차순 정렬
	});
	// 정렬된 결과를 출력 (디버그용)
	for (const TSubclassOf<AActor>& Key : SortedKeys)
	{
		int Value = MonsterClassValues[Key];
		if (Key)
		{
			FString ClassName = Key->GetName();
			UE_LOG(LogTemp, Warning, TEXT("Monster Class: %s, Value: %d"), *ClassName, Value);
		}
	}
	// 정렬된 키 배열을 사용하여 MonsterClass 배열을 재구성
	MonsterClass = SortedKeys;
}


// 디버그용 몬스터 클래스별 Value 출력 함수

void ASpawnManager::PrintMonsterClassValues()
{
	for (auto& Elem : MonsterClassValues)
	{
		UClass* MonsterUClass = Elem.Key; // tsubclassof -> uclass*
		int value = Elem.Value;

		if (MonsterUClass)
		{
			FString classname = MonsterUClass->GetName(); // 클래스 이름 가져오기
			UE_LOG(LogTemp, Warning, TEXT("monster class: %s, value: %d"), *classname, value);

			// 화면에 띄우고 싶으면
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, classname + " value: " + FString::FromInt(value));
			}
		}
	}
}