#include <iostream>
#include <Windows.h>

#include "WaveManager.h"
#include "Kismet/GameplayStatics.h"

AWaveManager::AWaveManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AWaveManager::BeginPlay()
{
	Super::BeginPlay();

	srand((unsigned int)time(NULL));

	CurrentWave = 0;// Wave 초기화

	BringMonsterValue();
	WaveStart();
}

void AWaveManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(MonsterNumInWave <= 0)
		WaveEnd();
}


// 몬스터 Spawn, delay 적용
void AWaveManager::SpawnMonster()
{
	for (int32 index = 0; index < MonsterClassInWave.Num(); index++)
	{
		// 지연 시간 계산: index * SpawnDelay
		float DelayTime = index * SpawnDelay;

		FTimerHandle TempHandle;
		FTimerDelegate Delegate;
		Delegate.BindLambda([this, index]()
			{
				if (MonsterClassInWave.IsValidIndex(index))
				{
					FVector SpawnLoc = SpawnPosition();
					FRotator SpawnRot = FRotator::ZeroRotator;

					GetWorld()->SpawnActor<AActor>(MonsterClassInWave[index], SpawnLoc, SpawnRot);
				}
			});

		// 타이머 예약
		GetWorld()->GetTimerManager().SetTimer(TempHandle, Delegate, DelayTime, false);
	}
}

// Spawn 위치 반환
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


// 몬스터 Value를 가져오는 함수
void AWaveManager::BringMonsterValue()
{
	MonsterClassValues.Empty();

	FVector SpawnLocation = FVector(5000.f, 5000.f, 5000.f);
	AActor* SpawnedActor;
	for (int index = 0; index < MonsterClass.Num(); index++)
	{
		SpawnedActor = GetWorld()->SpawnActor<AActor>(MonsterClass[index], SpawnLocation, FRotator::ZeroRotator);

		// EnemyBase로 캐스팅하여 Monster_Value 접근
		AEnemyBase* Enemy = Cast<AEnemyBase>(SpawnedActor);
		if (Enemy)
		{
			MonsterClassValues.Add(MonsterClass[index], Enemy->GetValue());
		}
		SpawnedActor->Destroy();
	}

	LowStairLevel();
}

// 맵의 키와 밸류 내림차순 정렬
void AWaveManager::LowStairLevel()
{
	TArray<TPair<TSubclassOf<AActor>, int>> PairArray = MonsterClassValues.Array();
	PairArray.Sort([](const TPair<TSubclassOf<AActor>, int>& A, const TPair<TSubclassOf<AActor>, int>& B)
		{
			return A.Value < B.Value; // 내림차순 정렬
		});
	MonsterClassValues.Empty();
	for (const auto& Pair : PairArray)
	{
		MonsterClassValues.Add(Pair.Key, Pair.Value);
	}
}

// 웨이브 시작, 끝 함수
void AWaveManager::WaveStart()
{
	CurrentWave++;
	SpawnMonsterValueInWave();
	SpawnMonster();
}

void AWaveManager::WaveEnd() { WaveStart();}

//현재 웨이브 밸류에 맞게 제일 높은 밸류부터 랜덤 계산 해서 클래스 당 스폰할 총 몬스터 수 계산식(몬스터 밸류 x 몬스터 소환할 예정인 숫자), 단 소환 X, 소환 명단 정리만
//계산식은 제일 높은 밸류를 먼저 웨이브 밸류에서 빼고, 그 다음 높은 밸류를 빼고 그렇게 제일 낮은 밸류까지 내려간 뒤
//이런식으로 웨이브 밸류가 0이 되거나 더 뺄 수 없을 때까지 반복
void AWaveManager::SpawnMonsterValueInWave()
{
	MonsterClassInWave.Empty();
	int WaveValue = StartWaveValue + (CurrentWave - 1) * MultipleWaveValue;

	TArray<TSubclassOf<AActor>> Keys;
	MonsterClassValues.GetKeys(Keys);
	while (WaveValue > 0)
	{
		bool ValueReduced = false; // 이번 반복에서 값이 줄었는지 확인하는 플래그
		for (int i = Keys.Num() - 1; i >= 0; i--)
		{
			TSubclassOf<AActor> MonsterClassKey = Keys[i];
			int MonsterValueInWave = MonsterClassValues[MonsterClassKey];
			if (WaveValue >= MonsterValueInWave)
			{
				int decideVal = WaveValue / MonsterValueInWave;
				int randomVal = rand() % decideVal + 1; // 1 ~ decideVal 사이의 랜덤 값
				for (int j = 0; j < randomVal; j++)
				{
					MonsterClassInWave.Add(MonsterClassKey);
					WaveValue -= MonsterValueInWave;
					ValueReduced = true; // 값이 줄었음을 표시
				}
				break; // 가장 높은 밸류부터 다시 시작
			}
		}
		if (!ValueReduced)
		{
			break; // 더 이상 값을 줄일 수 없으면 종료
		}
	}
	MonsterNumInWave = MonsterClassInWave.Num();
	ShakeMonsterList(); // 몬스터 클래스 리스트를 무작위로 섞기
}

// TArray로 모아놓은 MonsterClassInWave를 무작위로 섞기
void AWaveManager::ShakeMonsterList()
{
 	int Num = MonsterClassInWave.Num();
	for (int i = 0; i < Num; i++)
	{
		int SwapIndex = rand() % Num;
		if (i != SwapIndex)
		{
			MonsterClassInWave.Swap(i, SwapIndex);
		}
	}
	//MosterClassInWave 내역 알 수 있도록 UE_LOG에 보이게 하기
	for (int i = 0; i < MonsterClassInWave.Num(); i++)
	{
		if (MonsterClassInWave[i])
		{
			FString ClassName = MonsterClassInWave[i]->GetName();
			UE_LOG(LogTemp, Warning, TEXT("Shuffled Monster %d: %s"), i + 1, *ClassName);
		}
	}
}


// 몬스터 클래스와 값을 출력해서 테스트 하는 함수(디버그용)
void AWaveManager::PrintMonsterClassValues()
{
	for (auto& Elem : MonsterClassValues)
	{
		UClass* MonsterUClass = Elem.Key; // tsubclassof -> uclass*
		int value = Elem.Value;

		if (MonsterUClass)
		{
			FString classname = MonsterUClass->GetName(); // UClass* -> FString
			UE_LOG(LogTemp, Warning, TEXT("monster class: %s, value: %d"), *classname, value);

			//	화면에 출력
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, classname + " value: " + FString::FromInt(value));
			}
		}
	}
}