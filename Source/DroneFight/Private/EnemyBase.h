// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TimerManager.h" // FTimerHandle
#include "EnemyBase.generated.h"

UCLASS()
class AEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemyBase();
	AWaveManager* _playerController = nullptr;

protected:
	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster Stats")
	int Max_HP;

	UPROPERTY(BlueprintReadWrite, Category = "Monster Stats")
	int HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster Stats")
	int Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster Stats")
	int Defense;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster Stats")
	int Speed;

	// 계산된 Value
	UPROPERTY(BlueprintReadOnly, Category = "Monster Stats")
	int Monster_Value;

	void CalculateValue();

	//------------------------------------------------------------------------

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster Events")
	bool Close;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster Events")
	bool Hit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster Events", meta = (ExposeOnSpawn = true))
	AActor* Nexus;

	UFUNCTION(BlueprintCallable, Category = "Monster Events")

	void InitializeEnemy(AWaveManager* myown);

	UFUNCTION(BlueprintCallable, Category = "Monster Events")

	void DestroySelf();//5초 후 자신 삭제

private:
	FTimerHandle DestroyTimerHandle;
};
