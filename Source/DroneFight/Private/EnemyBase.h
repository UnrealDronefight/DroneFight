// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGotClose, AActor*, Nexus, bool, bClose);

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

	// 계산된 Value
	UPROPERTY(BlueprintReadOnly, Category = "Monster Stats")
	int Monster_Value;

	void CalculateValue();



	// 이벤트 디스패쳐 관련
	UPROPERTY(BlueprintAssignable, Category = "Monster Events")
	FGotClose GotClose;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster Events")
	bool Close;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster Events")
	bool Hit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster Events")
	AActor* Nexus;

	UFUNCTION(BlueprintCallable, Category = "Monster Events")
	void Initialize_GotClose(bool IsClose, AActor* NexusObject);
};
