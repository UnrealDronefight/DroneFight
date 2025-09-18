// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"

UCLASS()
class AEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemyBase();

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

	// °è»êµÈ Value
	UPROPERTY(BlueprintReadOnly, Category = "Monster Stats")
	int Monster_Value;

	void CalculateValue();
};
