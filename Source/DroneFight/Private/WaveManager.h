<<<<<<< HEAD
#pragma once
=======
ï»¿#pragma once
>>>>>>> dev

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyBase.h"
#include "WaveManager.generated.h"

UCLASS()
class AWaveManager : public AActor
{
	GENERATED_BODY()
<<<<<<< HEAD
		AWaveManager();
=======
	AWaveManager();
>>>>>>> dev

private:
	int CurrentWave;
	int MaxWaves = 5;

protected:
	virtual void BeginPlay() override;
<<<<<<< HEAD

	virtual void Tick(float DeltaTime) override;

	// ½ºÆù ÇÒ ¸ó½ºÅÍ Å¬·¡½º¸¦ T ¹è¿­·Î ¼¼ÆÃ

	UPROPERTY(EditAnywhere, Category = "Spawn Setting")
		TArray<TSubclassOf<AEnemyBase>> MonsterClass;

	////////////////////////////////////////////////////////////////////////////

		// ½ºÆù ÇÒ À§Ä¡ ¼³Á¤(µ¿,¼­,³²,ºÏ)

	UPROPERTY(EditAnywhere, Category = "Spawn Position")
		TSoftObjectPtr<AActor> NorthPos;

	UPROPERTY(EditAnywhere, Category = "Spawn Position")
		TSoftObjectPtr<AActor> SouthPos;

	UPROPERTY(EditAnywhere, Category = "Spawn Position")
		TSoftObjectPtr<AActor> EastPos;

	UPROPERTY(EditAnywhere, Category = "Spawn Position")
		TSoftObjectPtr<AActor> WestPos;

	////////////////////////////////////////////////////////////////////////////

		// ¸ó½ºÅÍ¸¦ ½ºÆùÇÏ´Â ÇÔ¼ö
	UFUNCTION(BlueprintCallable, Category = "Spawn Position")
		void SpawnMonster();

	// ½ºÆù À§Ä¡ ¹İÈ¯ ÇÔ¼ö
	FVector SpawnPosition();

	// ¹ë·ù¸¦ ¹Ş´Â ¸Ê

	UPROPERTY(BlueprintReadOnly, Category = "Value Check Debug")
		TMap<TSubclassOf<AActor>, int> MonsterClassValues;

	// ¹ë·ù¸¦ ¹Ş´Â ÇÔ¼ö
	void BringMonsterValue();

	// ¹ë·ù¸¦ ³»¸²Â÷¼øÀ¸·Î Á¤·ÄÇÏ´Â ÇÔ¼ö
	void LowStairLevel();

	// ¹ë·ù¸¦ Ãâ·ÂÇØ¼­ Å×½ºÆ® ÇÏ´Â ÇÔ¼ö(µğ¹ö±×¿ë)
	UFUNCTION(BlueprintCallable, Category = "Value Check Debug")
		void PrintMonsterClassValues();

	void SpawnMonsterValueInWave();

	// ¿şÀÌºê ½ÃÀÛ, ³¡ ÇÔ¼ö
	UFUNCTION(BlueprintCallable, Category = "Wave Control")
		void WaveStart();

	UFUNCTION(BlueprintCallable, Category = "Wave Control")
		void WaveEnd();

	// ÇöÀç ¿şÀÌºê ³» ¸ó½ºÅÍ ¼ö
	UPROPERTY(BlueprintReadOnly, Category = "Wave Control")
		int MonsterNumInWave;

	// ÇöÀç ¿şÀÌºê¿¡¼­ ¼ÒÈ¯ÇÒ ¸ó½ºÅÍ Å¬·¡½º ¸®½ºÆ®
=======
public:

	virtual void Tick(float DeltaTime) override;

	// ìŠ¤í° í•  ëª¬ìŠ¤í„° í´ë˜ìŠ¤ë¥¼ T ë°°ì—´ë¡œ ì„¸íŒ…

	UPROPERTY(EditAnywhere, Category = "Spawn Setting")
	TArray<TSubclassOf<AEnemyBase>> MonsterClass;

	////////////////////////////////////////////////////////////////////////////

		// ìŠ¤í° í•  ìœ„ì¹˜ ì„¤ì •(ë™,ì„œ,ë‚¨,ë¶)

	UPROPERTY(EditAnywhere, Category = "Spawn Position")
	TSoftObjectPtr<AActor> NorthPos;

	UPROPERTY(EditAnywhere, Category = "Spawn Position")
	TSoftObjectPtr<AActor> SouthPos;

	UPROPERTY(EditAnywhere, Category = "Spawn Position")
	TSoftObjectPtr<AActor> EastPos;

	UPROPERTY(EditAnywhere, Category = "Spawn Position")
	TSoftObjectPtr<AActor> WestPos;

	////////////////////////////////////////////////////////////////////////////

		// ëª¬ìŠ¤í„°ë¥¼ ìŠ¤í°í•˜ëŠ” í•¨ìˆ˜
	UFUNCTION(BlueprintCallable, Category = "Spawn Position")
	void SpawnMonster();

	// ìŠ¤í° ìœ„ì¹˜ ë°˜í™˜ í•¨ìˆ˜
	FVector SpawnPosition();

	// ë°¸ë¥˜ë¥¼ ë°›ëŠ” ë§µ

	UPROPERTY(BlueprintReadOnly, Category = "Value Check Debug")
	TMap<TSubclassOf<AActor>, int> MonsterClassValues;

	// ë°¸ë¥˜ë¥¼ ë°›ëŠ” í•¨ìˆ˜
	void BringMonsterValue();

	// ë°¸ë¥˜ë¥¼ ë‚´ë¦¼ì°¨ìˆœìœ¼ë¡œ ì •ë ¬í•˜ëŠ” í•¨ìˆ˜
	void LowStairLevel();

	// ë°¸ë¥˜ë¥¼ ì¶œë ¥í•´ì„œ í…ŒìŠ¤íŠ¸ í•˜ëŠ” í•¨ìˆ˜(ë””ë²„ê·¸ìš©)
	UFUNCTION(BlueprintCallable, Category = "Value Check Debug")
	void PrintMonsterClassValues();

	void SpawnMonsterValueInWave();
	
	// ì›¨ì´ë¸Œ ì‹œì‘, ë í•¨ìˆ˜
	UFUNCTION(BlueprintCallable, Category = "Wave Control")
	void WaveStart();

	UFUNCTION(BlueprintCallable, Category = "Wave Control")
	void WaveEnd();

	// í˜„ì¬ ì›¨ì´ë¸Œ ë‚´ ëª¬ìŠ¤í„° ìˆ˜
	UPROPERTY(BlueprintReadOnly, Category = "Wave Control")
	int MonsterNumInWave;

	// í˜„ì¬ ì›¨ì´ë¸Œì—ì„œ ì†Œí™˜í•  ëª¬ìŠ¤í„° í´ë˜ìŠ¤ ë¦¬ìŠ¤íŠ¸
>>>>>>> dev
	TArray<TSubclassOf<AActor>> MonsterClassInWave;

	void ShakeMonsterList();

<<<<<<< HEAD
	// ¿şÀÌºê ½ÃÀÛ ¹ë·ù
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave Value Control")
		int StartWaveValue = 0;

	// ¿şÀÌºê ´ç ¹ë·ù ¹è¼ö
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave Value Control")
		int MultipleWaveValue = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawn Control")
		float SpawnDelay = 1.0f;

	public :
		void MonsterDeath();
=======
	// ì›¨ì´ë¸Œ ì‹œì‘ ë°¸ë¥˜
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave Value Control")
	int StartWaveValue = 0;

	// ì›¨ì´ë¸Œ ë‹¹ ë°¸ë¥˜ ë°°ìˆ˜
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave Value Control")
	int MultipleWaveValue = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawn Control")
	float SpawnDelay = 1.0f;
>>>>>>> dev
};