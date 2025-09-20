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
	for (int index = 0; index < MonsterClassInWave.Num(); index++)
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

	// 키(몬스터 클래스) 목록 가져오기
	TArray<TSubclassOf<AActor>> Keys;
	MonsterClassValues.GetKeys(Keys);

	// 반드시 "높은 밸류부터" 순회하도록 내림차순 정렬 (값이 큰 것이 먼저)
	Keys.Sort([&](const TSubclassOf<AActor>& A, const TSubclassOf<AActor>& B) {
		return MonsterClassValues[A] > MonsterClassValues[B]; // 내림차순
		});

	// WaveValue가 0이거나 더 이상 뺄 수 없을 때까지 반복
	while (WaveValue > 0)
	{
		bool bAnyAddedThisPass = false;    // 이번 루프에서 실제로 추가했는지
		bool bAnyPossibleThisPass = false; // 이번 루프에서 추가 가능한 항목이 있었는지 (decideVal > 0)

		// 높은 밸류부터 낮은 밸류까지 한 번 스캔
		for (int32 i = 0; i < Keys.Num(); ++i)
		{
			TSubclassOf<AActor> MonsterClassKey = Keys[i];
			int MonsterValueInWave = MonsterClassValues[MonsterClassKey];
			if (MonsterValueInWave <= 0) continue;

			int DecideVal = WaveValue / MonsterValueInWave; // 해당 몬스터로 몇 마리까지 가능한지
			if (DecideVal <= 0) continue;

			bAnyPossibleThisPass = true;

			// 0 ~ DecideVal 사이 랜덤으로 뽑기 (0도 허용)
			int RandomVal = FMath::RandRange(0, DecideVal) + 1;
			for (int j = 0; j < RandomVal; ++j)
			{
				MonsterClassInWave.Add(MonsterClassKey);
			}
			WaveValue -= RandomVal * MonsterValueInWave;
			bAnyAddedThisPass = true;
		}

		// 한 번 훑었는데 아무것도 추가되지 않았다면
		if (!bAnyAddedThisPass)
		{
			if (bAnyPossibleThisPass)
			{
				// 안전장치: 랜덤으로 모두 0이 나와 버려서 진행이 멈추는 케이스 방지
				// (이 경우 가장 높은 밸류부터 가능한 한 마리씩 강제 추가해서 진행하게 함)
				for (int i = 0; i < Keys.Num(); ++i)
				{
					TSubclassOf<AActor> MonsterClassKey = Keys[i];
					int MonsterValueInWave = MonsterClassValues[MonsterClassKey];
					if (MonsterValueInWave <= 0) continue;
					if (WaveValue >= MonsterValueInWave)
					{
						MonsterClassInWave.Add(MonsterClassKey);
						WaveValue -= MonsterValueInWave;
						bAnyAddedThisPass = true;
						break; // 한 마리 추가하고 다시 while문으로 돌아가서 재시도
					}
				}

				// (만약 여기서도 추가 못하면 다음 if에서 빠져나옴)
			}
			else
			{
				// 이번 패스에 가능한 항목 자체가 없다면 더 이상 채울 수 없음 -> 종료
				break;
			}
		}
	}

	MonsterNumInWave = MonsterClassInWave.Num();
	ShakeMonsterList(); // 최종 리스트 섞기
}

// Fisher-Yates 방식으로 안전하게 섞기
void AWaveManager::ShakeMonsterList()
{
	int Num = MonsterClassInWave.Num();
	for (int32 i = Num - 1; i > 0; --i)
	{
		int j = FMath::RandRange(0, i);
		MonsterClassInWave.Swap(i, j);
	}

	// 디버그 로그: 결과 출력
	for (int i = 0; i < MonsterClassInWave.Num(); ++i)
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