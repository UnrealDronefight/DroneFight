// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DroneBase.generated.h"

UCLASS()
class ADroneBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADroneBase();

protected:
	class ADroneContainer* _droneContainer = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Drone|Move")
	float _moveSpeed = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Drone|Move")
	float _arriveRange = 0.5f;

	float _sqrArriveRange = 0.0f;

	bool _isTraceMode = false;

	FVector _targetLocation = FVector(0, 0, 0);
	FRotator _targetRotator = FRotator(0, 0, 0);

#pragma region Trace
	class AEnemyBase* _target = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Drone|Trace")
	float _searchTargetRange = 1000.0f;

	float _sqrSearchTargetRange = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Drone|Trace")
	float _droneHeight = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Drone|Trace")
	float _minRotateSpeed = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Drone|Trace")
	float _maxRotateSpeed = 300.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Drone|Trace", meta = (UIMin = "0.0", UIMax = "1.0"))
	float _rotateSpeedLerpRate = 0.7f;

	float _currentRotateSpeed = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Drone|Trace")
	float _minDistance = 50.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Drone|Trace")
	float _maxDistance = 300.0f;

	float _sqrMinDistance = 0.0f;
	float _sqrMaxDistance = 0.0f;
#pragma endregion

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void InitializeDrone(ADroneContainer* DroneContainer);

	void ChangeTraceMode(bool IsTraceMode);

	void SetTargetPosition(FVector TargetLocation, FRotator TargetRotator);

protected:
	void SearchTarget();
	void Tracing();
	
	// 장애물 회피 기능 제거
};
