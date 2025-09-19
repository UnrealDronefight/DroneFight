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
	AEnemyBase();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Monster Stats")
	int Max_HP;

	UPROPERTY(BlueprintReadWrite, Category = "Monster Stats")
	int HP;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Monster Stats")
	int Attack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Monster Stats")
	int Defense;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Monster Stats")
	int Speed;

	// 계산된 Value
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Monster Stats")
	int Monster_Value;

	UFUNCTION()
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

public:
	int GetValue() { return Monster_Value; }
};
