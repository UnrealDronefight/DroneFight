// Fill out your copyright notice in the Description page of Project Settings.


#include "DroneBase.h"
#include "DroneContainer.h"
#include "EnemyBase.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

// Sets default values
ADroneBase::ADroneBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADroneBase::BeginPlay()
{
	Super::BeginPlay();
	
	// 제곱 거리 미리 계산 (최적화)
	_sqrArriveRange = FMath::Pow(_arriveRange, 2);
	_sqrMinDistance = FMath::Pow(_minDistance, 2);
	_sqrMaxDistance = FMath::Pow(_maxDistance, 2);
	_sqrSearchTargetRange = FMath::Pow(_searchTargetRange, 2);
}

// Called every frame
void ADroneBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!_droneContainer)
	{
		return;
	}

	FVector _currentLocation = GetActorLocation();
	if (_isTraceMode)
	{
		Tracing();
	}
	else
	{
		// 표준 모드: 지정된 위치로 이동
		DrawDebugSphere(GetWorld(), _targetLocation, _arriveRange, 16, FColor::Yellow, false, DeltaTime * 2.0f);

		FVector _toTargetDir = _targetLocation - _currentLocation;
		FRotator _toTargetRot = _toTargetDir.Rotation();
		
		// 목표 위치에 도달했는지 확인
		if (_toTargetDir.SquaredLength() <= _sqrArriveRange)
		{
			SetActorLocation(_targetLocation);

			FVector _forward = (GetActorLocation() - _droneContainer->GetOrbitalCenter()->GetComponentLocation()).GetSafeNormal();
			FVector _up = -_droneContainer->GetActorForwardVector();

			// forward와 up 벡터를 각각 향하도록 회전 설정
			FMatrix _rotationMatrix = FRotationMatrix::MakeFromXZ(_forward, _up);
			SetActorRotation(_rotationMatrix.Rotator());
			return;
		}

		// 목표를 향해 이동 및 회전
		SetActorLocation(_currentLocation + _toTargetDir.GetSafeNormal() * _moveSpeed * DeltaTime);
		SetActorRotation(_toTargetRot);
	}
}

void ADroneBase::InitializeDrone(ADroneContainer* DroneContainer)
{
	_droneContainer = DroneContainer;
}

void ADroneBase::ChangeTraceMode(bool IsTraceMode)
{
	_isTraceMode = IsTraceMode;
}

void ADroneBase::SetTargetPosition(FVector TargetLocation, FRotator TargetRotator)
{
	_targetLocation = TargetLocation;
	_targetRotator = TargetRotator;
}

void ADroneBase::SearchTarget()
{
	// 적 배열 가져오기
	TArray<AActor*> _foundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyBase::StaticClass(), _foundActors);
	
	if (_foundActors.Num() <= 0)
	{
		// 적이 없으면 타겟 초기화
		_target = nullptr;
		return;
	}
	
	float _closestDistanceSqr = FLT_MAX;
	AEnemyBase* _closestEnemy = nullptr;
	
	for (AActor* _actor : _foundActors)
	{
		AEnemyBase* _enemy = Cast<AEnemyBase>(_actor);
		if (!_enemy)
			continue;
			
		float _distanceSqr = FVector::DistSquared(GetActorLocation(), _enemy->GetActorLocation());
		
		if (_distanceSqr <= _sqrSearchTargetRange && _distanceSqr < _closestDistanceSqr)
		{
			_closestDistanceSqr = _distanceSqr;
			_closestEnemy = _enemy;
		}
	}
	
	_target = _closestEnemy;
}

void ADroneBase::Tracing()
{
	if (!_target)
	{
		SearchTarget();
	}

	if (!_target)
	{
		UE_LOG(LogTemp, Warning, TEXT("Null"));
		return;
	}

	// 전진
	FVector _currentPosition = GetActorLocation();
	FVector _forward = GetActorForwardVector();
	float _deltaTime = GetWorld()->GetDeltaSeconds();
	SetActorLocation(_currentPosition + _forward * _moveSpeed * _deltaTime);
	
	FVector _targetPos = _target->GetActorLocation() + FVector(0, 0, _droneHeight);
	FVector _toTarget = _targetPos - _currentPosition;
	FVector _toTargetZeroZ = FVector(_toTarget.X, _toTarget.Y, 0);
	float _currentSqrDistance = _toTargetZeroZ.SquaredLength();

	// 목표 회전 속도 계산
	float _aimRotateSpeed;
	if (_isTraceMode && _currentSqrDistance <= _sqrMinDistance)
	{
		// _minDistance 범위 안에 있으면 회전 속도의 목표를 0으로 설정
		_aimRotateSpeed = 0.0f;
	}
	else
	{
		//_aimRotateSpeed = FMath::Lerp(_minRotateSpeed, _maxRotateSpeed, _rotateSpeedLerpRate);
		_aimRotateSpeed = _minRotateSpeed;
	}

	// 현재 회전 속도를 목표 회전 속도로 부드럽게 보간
	//_currentRotateSpeed = FMath::Lerp(_currentRotateSpeed, _aimRotateSpeed, _rotateSpeedLerpRate);
	
	// 현재 회전값과 목표 회전값 사이를 부드럽게 보간 (회전 속도 적용)
	FRotator _newRotation = FMath::RInterpTo(GetActorRotation(), _toTarget.GetSafeNormal().Rotation(), _deltaTime, _aimRotateSpeed);
	
	// 회전 적용
	SetActorRotation(_newRotation);
	
	// 디버그 정보
	GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::White, 
		FString::Printf(TEXT("Rotation Speed: %.2f"), _aimRotateSpeed));
		
	DrawDebugLine(GetWorld(), _currentPosition, _targetPos, FColor::Green, false, 0.1f, 0, 1.0f);

	DrawDebugSphere(GetWorld(), _targetPos, _minDistance, 16, FColor::Yellow, false, _deltaTime * 1.1f);
}