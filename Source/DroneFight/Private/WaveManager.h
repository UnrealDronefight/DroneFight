#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WaveManager.generated.h"

UCLASS()
class AWaveManager : public AActor
{
	GENERATED_BODY()
	AWaveManager();

private:
	int CurrentWave;
	int MaxWaves = 5;

protected:
	virtual void BeginPlay() override;
public:

	virtual void Tick(float DeltaTime) override;

	// 스폰 할 몬스터 클래스를 T 배열로 세팅

	UPROPERTY(EditAnywhere, Category = "Spawn Setting")
	TArray<TSubclassOf<AActor>> MonsterClass;

	////////////////////////////////////////////////////////////////////////////

		// 스폰 할 위치 설정(동,서,남,북)

	UPROPERTY(EditAnywhere, Category = "Spawn Position")
	TSoftObjectPtr<AActor> NorthPos;

	UPROPERTY(EditAnywhere, Category = "Spawn Position")
	TSoftObjectPtr<AActor> SouthPos;

	UPROPERTY(EditAnywhere, Category = "Spawn Position")
	TSoftObjectPtr<AActor> EastPos;

	UPROPERTY(EditAnywhere, Category = "Spawn Position")
	TSoftObjectPtr<AActor> WestPos;

	////////////////////////////////////////////////////////////////////////////

		// 몬스터를 스폰하는 함수
	UFUNCTION(BlueprintCallable, Category = "Spawn Position")
	void SpawnMonster();

	// 스폰 위치 반환 함수
	FVector SpawnPosition();

	// 밸류를 받는 맵

	UPROPERTY(BlueprintReadOnly, Category = "Value Check Debug")
	TMap<TSubclassOf<AActor>, int> MonsterClassValues;

	// 밸류를 받는 함수
	void BringMonsterValue();

	// 밸류를 내림차순으로 정렬하는 함수
	void LowStairLevel();

	// 밸류를 출력해서 테스트 하는 함수(디버그용)
	UFUNCTION(BlueprintCallable, Category = "Value Check Debug")
	void PrintMonsterClassValues();

	void SpawnMonsterValueInWave();
	
	// 웨이브 시작, 끝 함수
	UFUNCTION(BlueprintCallable, Category = "Wave Control")
	void WaveStart();

	UFUNCTION(BlueprintCallable, Category = "Wave Control")
	void WaveEnd();

	// 현재 웨이브 내 몬스터 수
	UPROPERTY(BlueprintReadOnly, Category = "Wave Control")
	int MonsterNumInWave;

	// 현재 웨이브에서 소환할 몬스터 클래스 리스트
	TArray<TSubclassOf<AActor>> MonsterClassInWave;

	void ShakeMonsterList();

	// 웨이브 시작 밸류
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave Value Control")
	int StartWaveValue = 0;

	// 웨이브 당 밸류 배수
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave Value Control")
	int MultipleWaveValue = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawn Control")
	float SpawnDelay = 1.0f;
};