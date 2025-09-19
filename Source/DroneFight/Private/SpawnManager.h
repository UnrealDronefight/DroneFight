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

	// ���� �Ǵ� ������ Ŭ������

	UPROPERTY(EditAnywhere, Category = "Spawn Setting")
	TArray<TSubclassOf<AActor>> MonsterClass;

	////////////////////////////////////////////////////////////////////////////

		// ���Ͱ� Spawn �� ��ġ Actor

	UPROPERTY(EditAnywhere, Category = "Spawn Position")
	TSoftObjectPtr<AActor> NorthPos;

	UPROPERTY(EditAnywhere, Category = "Spawn Position")
	TSoftObjectPtr<AActor> SouthPos;

	UPROPERTY(EditAnywhere, Category = "Spawn Position")
	TSoftObjectPtr<AActor> EastPos;

	UPROPERTY(EditAnywhere, Category = "Spawn Position")
	TSoftObjectPtr<AActor> WestPos;

	////////////////////////////////////////////////////////////////////////////

		// ���͸� Spawn�ϴ� �Լ�
	UFUNCTION(BlueprintCallable, Category = "Spawn Position")
	void SpawnMonster();

	// Spawn ��ġ�� �������� ��ȯ�ϴ� �Լ�
	FVector SpawnPosition();

	// ����׿� ���� Ŭ������ Value

	UPROPERTY(BlueprintReadOnly, Category = "Value Check Debug")
	TMap<TSubclassOf<AActor>, int> MonsterClassValues;

	// ���� Ŭ������ Value�� �����ϴ� �Լ�
	void BringMonsterValue();


	void LowStairLevel();
	// ����׿� ���� Ŭ������ Value ��� �Լ�
	UFUNCTION(BlueprintCallable, Category = "Value Check Debug")
	void PrintMonsterClassValues();
};