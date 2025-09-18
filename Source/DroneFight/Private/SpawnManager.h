#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnManager.generated.h"

UCLASS()
class ASpawnManager : public AActor
{
	GENERATED_BODY()
	ASpawnManager();

private:
	int CurrentWave;
	int MaxWaves = 5;

protected:
	virtual void BeginPlay() override;
public:

	virtual void Tick(float DeltaTime) override;

	// 스폰 되는 몬스터의 클래스들

	UPROPERTY(EditAnywhere, Category = "Spawn Setting")
	TArray<TSubclassOf<AActor>> MonsterClass;

////////////////////////////////////////////////////////////////////////////
	
	// 몬스터가 Spawn 될 위치 Actor

	UPROPERTY(EditAnywhere, Category = "Spawn Position")
	TSoftObjectPtr<AActor> NorthPos;

	UPROPERTY(EditAnywhere, Category = "Spawn Position")
	TSoftObjectPtr<AActor> SouthPos;

	UPROPERTY(EditAnywhere, Category = "Spawn Position")
	TSoftObjectPtr<AActor> EastPos;

	UPROPERTY(EditAnywhere, Category = "Spawn Position")
	TSoftObjectPtr<AActor> WestPos;

////////////////////////////////////////////////////////////////////////////

	// 몬스터를 Spawn하는 함수
	UFUNCTION(BlueprintCallable, Category = "Spawn Position")
	void SpawnMonster();

	// Spawn 위치를 랜덤으로 반환하는 함수
	FVector SpawnPosition();

	// 디버그용 몬스터 클래스별 Value

	UPROPERTY(BlueprintReadOnly, Category = "Value Check Debug")
	TMap<TSubclassOf<AActor>, int> MonsterClassValues;

	// 몬스터 클래스별 Value를 세팅하는 함수
	void BringMonsterValue();

	
	void LowStairLevel();
	// 디버그용 몬스터 클래스별 Value 출력 함수
	UFUNCTION(BlueprintCallable, Category = "Value Check Debug")
	void PrintMonsterClassValues();
};