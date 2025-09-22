<<<<<<< HEAD
#include "WaveManager.h"

#include <iostream>
#include <Windows.h>

=======
ï»¿#include <iostream>
#include <Windows.h>

#include "WaveManager.h"
>>>>>>> dev
#include "Kismet/GameplayStatics.h"

AWaveManager::AWaveManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AWaveManager::BeginPlay()
{
	Super::BeginPlay();

	srand((unsigned int)time(NULL));

<<<<<<< HEAD
	CurrentWave = 0;// Wave ÃÊ±âÈ­
=======
	CurrentWave = 0;// Wave ì´ˆê¸°í™”
>>>>>>> dev

	BringMonsterValue();
	WaveStart();
}

void AWaveManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
<<<<<<< HEAD
}

void AWaveManager::MonsterDeath()
{
	MonsterNumInWave--;
	if (MonsterNumInWave <= 0)
		WaveEnd();
}

// ¸ó½ºÅÍ Spawn, delay Àû¿ë
=======

	if(MonsterNumInWave <= 0)
		WaveEnd();
}


// ëª¬ìŠ¤í„° Spawn, delay ì ìš©
>>>>>>> dev
void AWaveManager::SpawnMonster()
{
	for (int index = 0; index < MonsterClassInWave.Num(); index++)
	{
<<<<<<< HEAD
		// Áö¿¬ ½Ã°£ °è»ê: index * SpawnDelay
=======
		// ì§€ì—° ì‹œê°„ ê³„ì‚°: index * SpawnDelay
>>>>>>> dev
		float DelayTime = index * SpawnDelay;

		FTimerHandle TempHandle;
		FTimerDelegate Delegate;
		Delegate.BindLambda([this, index]()
			{
				if (MonsterClassInWave.IsValidIndex(index))
				{
					FVector SpawnLoc = SpawnPosition();
					FRotator SpawnRot = FRotator::ZeroRotator;

<<<<<<< HEAD
					AEnemyBase* Enemy = GetWorld()->SpawnActor<AEnemyBase>(MonsterClassInWave[index], SpawnLoc, SpawnRot);
					if (Enemy)
					{
						Enemy->InitializeEnemy(this);
					}
				}
			});
		if (index == 0)
		{
			FVector SpawnLoc = SpawnPosition();
			FRotator SpawnRot = FRotator::ZeroRotator;
			GetWorld()->SpawnActor<AActor>(MonsterClassInWave[index], SpawnLoc, SpawnRot);
		}
		else
		// Å¸ÀÌ¸Ó ¿¹¾à
			GetWorld()->GetTimerManager().SetTimer(TempHandle, Delegate, DelayTime, false);
	}
}

// Spawn À§Ä¡ ¹İÈ¯
=======
					GetWorld()->SpawnActor<AActor>(MonsterClassInWave[index], SpawnLoc, SpawnRot);
				}
			});

		// íƒ€ì´ë¨¸ ì˜ˆì•½
		GetWorld()->GetTimerManager().SetTimer(TempHandle, Delegate, DelayTime, false);
	}
}

// Spawn ìœ„ì¹˜ ë°˜í™˜
>>>>>>> dev
FVector AWaveManager::SpawnPosition()
{
	int PositionNum = rand() % 4;
	FVector ResultPos;
	switch (PositionNum)
	{
	case 0:
		ResultPos = NorthPos->GetActorLocation();
		break;
	case 1:
		ResultPos = EastPos->GetActorLocation();
		break;
	case 2:
		ResultPos = SouthPos->GetActorLocation();
		break;
	case 3:
		ResultPos = WestPos->GetActorLocation();
		break;
	}

	return ResultPos;

}


<<<<<<< HEAD
// ¸ó½ºÅÍ Value¸¦ °¡Á®¿À´Â ÇÔ¼ö
void AWaveManager::BringMonsterValue()
{
	//MonsterClassValues = ¸ó½ºÅÍ Class¿Í ¸ó½ºÅÍ Value¸¦ °¢°¢ Key°ª°ú Value°ªÀ¸·Î º¸À¯ ÁßÀÎ MapÇÔ¼ö
	MonsterClassValues.Empty();

	// ¸ó½ºÅÍÀÇ ½ºÆù ·ÎÄÉÀÌ¼ÇÀ» ¹Ş±â À§ÇÑ ¸Ê ¹Û¿¡ ÀÓ½Ã ½ºÆù
	FVector SpawnLocation = FVector(5000.f, 5000.f, 5000.f);
	//ActorÅ¬·¡½º¸¦ Æ÷ÀÎÅÍ·Î ¹Ş¾ÆµéÀÎ SpawnedActorº¯¼ö ¼±¾ğ
	AEnemyBase* SpawnedActor;

	//MapÇÔ¼ö¿¡ ³ÖÀ» classÀÇ ¼ö´Â MonsterClass.NumÀ¸·Î ¹Ş¾Æ¼­ ³Ö´Â ÀÛ¾÷
	for (int index = 0; index < MonsterClass.Num(); index++)
	{
		SpawnedActor = GetWorld()->SpawnActor<AEnemyBase>(MonsterClass[index], SpawnLocation, FRotator::ZeroRotator);
		if (SpawnedActor)
		{
			MonsterClassValues.Add(MonsterClass[index], SpawnedActor->Monster_Value);
=======
// ëª¬ìŠ¤í„° Valueë¥¼ ê°€ì ¸ì˜¤ëŠ” í•¨ìˆ˜
void AWaveManager::BringMonsterValue()
{
	MonsterClassValues.Empty();

	FVector SpawnLocation = FVector(5000.f, 5000.f, 5000.f);
	AActor* SpawnedActor;
	for (int index = 0; index < MonsterClass.Num(); index++)
	{
		SpawnedActor = GetWorld()->SpawnActor<AActor>(MonsterClass[index], SpawnLocation, FRotator::ZeroRotator);

		// EnemyBaseë¡œ ìºìŠ¤íŒ…í•˜ì—¬ Monster_Value ì ‘ê·¼
		AEnemyBase* Enemy = Cast<AEnemyBase>(SpawnedActor);
		if (Enemy)
		{
			MonsterClassValues.Add(MonsterClass[index], Enemy->GetValue());
>>>>>>> dev
		}
		SpawnedActor->Destroy();
	}

	LowStairLevel();
}

<<<<<<< HEAD
// ¸ÊÀÇ Å°¿Í ¹ë·ù ³»¸²Â÷¼ø Á¤·Ä
=======
// ë§µì˜ í‚¤ì™€ ë°¸ë¥˜ ë‚´ë¦¼ì°¨ìˆœ ì •ë ¬
>>>>>>> dev
void AWaveManager::LowStairLevel()
{
	TArray<TPair<TSubclassOf<AActor>, int>> PairArray = MonsterClassValues.Array();
	PairArray.Sort([](const TPair<TSubclassOf<AActor>, int>& A, const TPair<TSubclassOf<AActor>, int>& B)
		{
<<<<<<< HEAD
			return A.Value < B.Value; // ³»¸²Â÷¼ø Á¤·Ä
=======
			return A.Value < B.Value; // ë‚´ë¦¼ì°¨ìˆœ ì •ë ¬
>>>>>>> dev
		});
	MonsterClassValues.Empty();
	for (const auto& Pair : PairArray)
	{
		MonsterClassValues.Add(Pair.Key, Pair.Value);
	}
}

<<<<<<< HEAD
// ¿şÀÌºê ½ÃÀÛ, ³¡ ÇÔ¼ö
=======
// ì›¨ì´ë¸Œ ì‹œì‘, ë í•¨ìˆ˜
>>>>>>> dev
void AWaveManager::WaveStart()
{
	CurrentWave++;
	SpawnMonsterValueInWave();
	SpawnMonster();
}

<<<<<<< HEAD
void AWaveManager::WaveEnd() { WaveStart(); }

//ÇöÀç ¿şÀÌºê ¹ë·ù¿¡ ¸Â°Ô Á¦ÀÏ ³ôÀº ¹ë·ùºÎÅÍ ·£´ı °è»ê ÇØ¼­ Å¬·¡½º ´ç ½ºÆùÇÒ ÃÑ ¸ó½ºÅÍ ¼ö °è»ê½Ä(¸ó½ºÅÍ ¹ë·ù x ¸ó½ºÅÍ ¼ÒÈ¯ÇÒ ¿¹Á¤ÀÎ ¼ıÀÚ), ´Ü ¼ÒÈ¯ X, ¼ÒÈ¯ ¸í´Ü Á¤¸®¸¸
//°è»ê½ÄÀº Á¦ÀÏ ³ôÀº ¹ë·ù¸¦ ¸ÕÀú ¿şÀÌºê ¹ë·ù¿¡¼­ »©°í, ±× ´ÙÀ½ ³ôÀº ¹ë·ù¸¦ »©°í ±×·¸°Ô Á¦ÀÏ ³·Àº ¹ë·ù±îÁö ³»·Á°£ µÚ
//ÀÌ·±½ÄÀ¸·Î ¿şÀÌºê ¹ë·ù°¡ 0ÀÌ µÇ°Å³ª ´õ »¬ ¼ö ¾øÀ» ¶§±îÁö ¹İº¹
void AWaveManager::SpawnMonsterValueInWave()
{
	MonsterClassInWave.Empty();//ÇöÀç ¿şÀÌºêÀÇ MonsterClassInWave¸¦ NULL°ªÀ¸·Î ÃÊ±âÈ­

	// ÇöÀç ¿şÀÌºê ¹ë·ù = ¿şÀÌºê 1ÀÇ ¹ë·ù + (ÇöÀç ¿şÀÌºê°¡ ¸î¹øÂ° ¿şÀÌºêÀÎÁö - 1) * µîÂ÷¹ë·ù
	int WaveValue = StartWaveValue + (CurrentWave - 1) * MultipleWaveValue;

	// Å°(¸ó½ºÅÍ Å¬·¡½º) ¸ñ·ÏÀ» Keys¶ó´Â ¹è¿­ º¯¼ö·Î ÀüºÎ °¡Á®¿À±â
	TArray<TSubclassOf<AActor>> Keys;

	//MonsterClassValues¿¡ ¼ÒÈ¯ ½ÃÅ³ Å°(¸ğµç Å¬·¡½º)¸¦ ³Ö±â
	MonsterClassValues.GetKeys(Keys);

	// ¹İµå½Ã "³ôÀº ¹ë·ùºÎÅÍ" ¼øÈ¸ÇÏµµ·Ï ³»¸²Â÷¼ø Á¤·Ä (°ªÀÌ Å« °ÍÀÌ ¸ÕÀú)
	Keys.Sort([&](const TSubclassOf<AActor>& A, const TSubclassOf<AActor>& B) {
		return MonsterClassValues[A] > MonsterClassValues[B]; // ³»¸²Â÷¼ø
		});

	// WaveValue°¡ 0ÀÌ°Å³ª ´õ ÀÌ»ó »¬ ¼ö ¾øÀ» ¶§±îÁö ¹İº¹
	while (WaveValue > 0)
	{
		bool bAnyAddedThisPass = false;    // ÀÌ¹ø ·çÇÁ¿¡¼­ ½ÇÁ¦·Î Ãß°¡Çß´ÂÁö
		bool bAnyPossibleThisPass = false; // ÀÌ¹ø ·çÇÁ¿¡¼­ Ãß°¡ °¡´ÉÇÑ Ç×¸ñÀÌ ÀÖ¾ú´ÂÁö (decideVal > 0)

		// ³ôÀº ¹ë·ùºÎÅÍ ³·Àº ¹ë·ù±îÁö ÇÑ ¹ø ½ºÄµ
		for (int i = 0; i < Keys.Num(); ++i)
		{
			// Classº¯¼ö MonsterClassKey¿¡ Keys[]¸¦ ÃÊ±âÈ­
			TSubclassOf<AActor> MonsterClassKey = Keys[i];

			// MonsterValueInWave¿¡ Çö ClassÀÇ ¹ë·ù°ªÀ» ³Ö¾îÁÜ
			int MonsterValueInWave = MonsterClassValues[MonsterClassKey];
			
			// ³Ö¾îÁØ Å°°¡ NULL°ª, Áï ¾ø´Â °ªÀÌ¸é ÀÌ ÀüÃ¼ °úÁ¤À» ¹«½ÃÇÏ°í ´ÙÀ½ Å°ÀÇ ³Ñ¹ö·Î
			if (MonsterValueInWave <= 0) continue;

			// ÇØ´ç ¸ó½ºÅÍ·Î ¸î ¸¶¸®±îÁö °¡´ÉÇÑÁö Çö ¿şÀÌºêÀÇ ¹ë·ù / ÇöÀç Á¡ ÂïÀº ¸ó½ºÅÍÀÇ ¹ë·ù°ª
			int DecideVal = WaveValue / MonsterValueInWave; 

			// ³Ö¾îÁØ ¹ë·ù°¡ 0º¸´Ù ÀÛ°Å³ª °°Àº Áï ¹«½ÃÇØµµ µÇ´Â °úÁ¤ÀÌ¸é ÀÌ ÀüÃ¼ °úÁ¤À» ¹«½ÃÇÏ°í ´ÙÀ½ Å°ÀÇ ³Ñ¹ö·Î
=======
void AWaveManager::WaveEnd() { WaveStart();}

//í˜„ì¬ ì›¨ì´ë¸Œ ë°¸ë¥˜ì— ë§ê²Œ ì œì¼ ë†’ì€ ë°¸ë¥˜ë¶€í„° ëœë¤ ê³„ì‚° í•´ì„œ í´ë˜ìŠ¤ ë‹¹ ìŠ¤í°í•  ì´ ëª¬ìŠ¤í„° ìˆ˜ ê³„ì‚°ì‹(ëª¬ìŠ¤í„° ë°¸ë¥˜ x ëª¬ìŠ¤í„° ì†Œí™˜í•  ì˜ˆì •ì¸ ìˆ«ì), ë‹¨ ì†Œí™˜ X, ì†Œí™˜ ëª…ë‹¨ ì •ë¦¬ë§Œ
//ê³„ì‚°ì‹ì€ ì œì¼ ë†’ì€ ë°¸ë¥˜ë¥¼ ë¨¼ì € ì›¨ì´ë¸Œ ë°¸ë¥˜ì—ì„œ ë¹¼ê³ , ê·¸ ë‹¤ìŒ ë†’ì€ ë°¸ë¥˜ë¥¼ ë¹¼ê³  ê·¸ë ‡ê²Œ ì œì¼ ë‚®ì€ ë°¸ë¥˜ê¹Œì§€ ë‚´ë ¤ê°„ ë’¤
//ì´ëŸ°ì‹ìœ¼ë¡œ ì›¨ì´ë¸Œ ë°¸ë¥˜ê°€ 0ì´ ë˜ê±°ë‚˜ ë” ëº„ ìˆ˜ ì—†ì„ ë•Œê¹Œì§€ ë°˜ë³µ
void AWaveManager::SpawnMonsterValueInWave()
{
	MonsterClassInWave.Empty();
	int WaveValue = StartWaveValue + (CurrentWave - 1) * MultipleWaveValue;

	// í‚¤(ëª¬ìŠ¤í„° í´ë˜ìŠ¤) ëª©ë¡ ê°€ì ¸ì˜¤ê¸°
	TArray<TSubclassOf<AActor>> Keys;
	MonsterClassValues.GetKeys(Keys);

	// ë°˜ë“œì‹œ "ë†’ì€ ë°¸ë¥˜ë¶€í„°" ìˆœíšŒí•˜ë„ë¡ ë‚´ë¦¼ì°¨ìˆœ ì •ë ¬ (ê°’ì´ í° ê²ƒì´ ë¨¼ì €)
	Keys.Sort([&](const TSubclassOf<AActor>& A, const TSubclassOf<AActor>& B) {
		return MonsterClassValues[A] > MonsterClassValues[B]; // ë‚´ë¦¼ì°¨ìˆœ
		});

	// WaveValueê°€ 0ì´ê±°ë‚˜ ë” ì´ìƒ ëº„ ìˆ˜ ì—†ì„ ë•Œê¹Œì§€ ë°˜ë³µ
	while (WaveValue > 0)
	{
		bool bAnyAddedThisPass = false;    // ì´ë²ˆ ë£¨í”„ì—ì„œ ì‹¤ì œë¡œ ì¶”ê°€í–ˆëŠ”ì§€
		bool bAnyPossibleThisPass = false; // ì´ë²ˆ ë£¨í”„ì—ì„œ ì¶”ê°€ ê°€ëŠ¥í•œ í•­ëª©ì´ ìˆì—ˆëŠ”ì§€ (decideVal > 0)

		// ë†’ì€ ë°¸ë¥˜ë¶€í„° ë‚®ì€ ë°¸ë¥˜ê¹Œì§€ í•œ ë²ˆ ìŠ¤ìº”
		for (int32 i = 0; i < Keys.Num(); ++i)
		{
			TSubclassOf<AActor> MonsterClassKey = Keys[i];
			int MonsterValueInWave = MonsterClassValues[MonsterClassKey];
			if (MonsterValueInWave <= 0) continue;

			int DecideVal = WaveValue / MonsterValueInWave; // í•´ë‹¹ ëª¬ìŠ¤í„°ë¡œ ëª‡ ë§ˆë¦¬ê¹Œì§€ ê°€ëŠ¥í•œì§€
>>>>>>> dev
			if (DecideVal <= 0) continue;

			bAnyPossibleThisPass = true;

<<<<<<< HEAD
			// 0 ~ DecideVal »çÀÌ ·£´ıÀ¸·Î »Ì±â (0µµ Çã¿ë)
			int RandomVal = rand() % (DecideVal +1);

			// ±×·¸°Ô ±¸ÇÑ ¼ÒÈ¯ÇÒ ¸ó½ºÅÍ, °³¼ö¸¦ ±¸ÇÑ ÈÄ MonsterClassInWave¿¡ ´õÇÑ´Ù
=======
			// 0 ~ DecideVal ì‚¬ì´ ëœë¤ìœ¼ë¡œ ë½‘ê¸° (0ë„ í—ˆìš©)
			int RandomVal = FMath::RandRange(0, DecideVal) + 1;
>>>>>>> dev
			for (int j = 0; j < RandomVal; ++j)
			{
				MonsterClassInWave.Add(MonsterClassKey);
			}
			WaveValue -= RandomVal * MonsterValueInWave;
<<<<<<< HEAD
		}

		TSubclassOf<AActor> MonsterKey = Keys[Keys.Num()-1];
		if (WaveValue < MonsterClassValues[MonsterKey])
		{
			break;
		}
		
	}

	MonsterNumInWave = MonsterClassInWave.Num();
	ShakeMonsterList(); // ÃÖÁ¾ ¸®½ºÆ® ¼¯±â
}

// Fisher-Yates ¹æ½ÄÀ¸·Î ¾ÈÀüÇÏ°Ô ¼¯±â
void AWaveManager::ShakeMonsterList()
{
	int Num = MonsterClassInWave.Num();
	//TestLog´Â µğ¹ö±×¿ëÀ¸·Î ¸ğµç ¹ë·ù °ªÀ» ´Ù ´õÇÑ °ª
	int TestLog = 0;
	for (int i = Num - 1; i > 0; --i)
=======
			bAnyAddedThisPass = true;
		}

		// í•œ ë²ˆ í›‘ì—ˆëŠ”ë° ì•„ë¬´ê²ƒë„ ì¶”ê°€ë˜ì§€ ì•Šì•˜ë‹¤ë©´
		if (!bAnyAddedThisPass)
		{
			if (bAnyPossibleThisPass)
			{
				// ì•ˆì „ì¥ì¹˜: ëœë¤ìœ¼ë¡œ ëª¨ë‘ 0ì´ ë‚˜ì™€ ë²„ë ¤ì„œ ì§„í–‰ì´ ë©ˆì¶”ëŠ” ì¼€ì´ìŠ¤ ë°©ì§€
				// (ì´ ê²½ìš° ê°€ì¥ ë†’ì€ ë°¸ë¥˜ë¶€í„° ê°€ëŠ¥í•œ í•œ ë§ˆë¦¬ì”© ê°•ì œ ì¶”ê°€í•´ì„œ ì§„í–‰í•˜ê²Œ í•¨)
				for (int i = 0; i < Keys.Num(); ++i)
				{
					TSubclassOf<AActor> MonsterClassKey = Keys[i];
					int MonsterValueInWave = MonsterClassValues[MonsterClassKey];
					if (MonsterValueInWave <= 0) continue;
					if (WaveValue >= MonsterValueInWave)
					{
						MonsterClassInWave.Add(MonsterClassKey);
						WaveValue -= MonsterValueInWave;
						bAnyAddedThisPass = true;
						break; // í•œ ë§ˆë¦¬ ì¶”ê°€í•˜ê³  ë‹¤ì‹œ whileë¬¸ìœ¼ë¡œ ëŒì•„ê°€ì„œ ì¬ì‹œë„
					}
				}

				// (ë§Œì•½ ì—¬ê¸°ì„œë„ ì¶”ê°€ ëª»í•˜ë©´ ë‹¤ìŒ ifì—ì„œ ë¹ ì ¸ë‚˜ì˜´)
			}
			else
			{
				// ì´ë²ˆ íŒ¨ìŠ¤ì— ê°€ëŠ¥í•œ í•­ëª© ìì²´ê°€ ì—†ë‹¤ë©´ ë” ì´ìƒ ì±„ìš¸ ìˆ˜ ì—†ìŒ -> ì¢…ë£Œ
				break;
			}
		}
	}

	MonsterNumInWave = MonsterClassInWave.Num();
	ShakeMonsterList(); // ìµœì¢… ë¦¬ìŠ¤íŠ¸ ì„ê¸°
}

// Fisher-Yates ë°©ì‹ìœ¼ë¡œ ì•ˆì „í•˜ê²Œ ì„ê¸°
void AWaveManager::ShakeMonsterList()
{
	int Num = MonsterClassInWave.Num();
	for (int32 i = Num - 1; i > 0; --i)
>>>>>>> dev
	{
		int j = FMath::RandRange(0, i);
		MonsterClassInWave.Swap(i, j);
	}

<<<<<<< HEAD
	// µğ¹ö±× ·Î±×: °á°ú Ãâ·Â
=======
	// ë””ë²„ê·¸ ë¡œê·¸: ê²°ê³¼ ì¶œë ¥
>>>>>>> dev
	for (int i = 0; i < MonsterClassInWave.Num(); ++i)
	{
		if (MonsterClassInWave[i])
		{
<<<<<<< HEAD
			TestLog += MonsterClassValues[MonsterClassInWave[i]];
=======
>>>>>>> dev
			FString ClassName = MonsterClassInWave[i]->GetName();
			UE_LOG(LogTemp, Warning, TEXT("Shuffled Monster %d: %s"), i + 1, *ClassName);
		}
	}
<<<<<<< HEAD
	UE_LOG(LogTemp, Warning, TEXT("Total Monster Value in Wave: %d"), TestLog);
}


// ¸ó½ºÅÍ Å¬·¡½º¿Í °ªÀ» Ãâ·ÂÇØ¼­ Å×½ºÆ® ÇÏ´Â ÇÔ¼ö(µğ¹ö±×¿ë)
=======
}


// ëª¬ìŠ¤í„° í´ë˜ìŠ¤ì™€ ê°’ì„ ì¶œë ¥í•´ì„œ í…ŒìŠ¤íŠ¸ í•˜ëŠ” í•¨ìˆ˜(ë””ë²„ê·¸ìš©)
>>>>>>> dev
void AWaveManager::PrintMonsterClassValues()
{
	for (auto& Elem : MonsterClassValues)
	{
		UClass* MonsterUClass = Elem.Key; // tsubclassof -> uclass*
		int value = Elem.Value;

		if (MonsterUClass)
		{
			FString classname = MonsterUClass->GetName(); // UClass* -> FString
			UE_LOG(LogTemp, Warning, TEXT("monster class: %s, value: %d"), *classname, value);

<<<<<<< HEAD
			//	È­¸é¿¡ Ãâ·Â
=======
			//	í™”ë©´ì— ì¶œë ¥
>>>>>>> dev
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, classname + " value: " + FString::FromInt(value));
			}
		}
	}
}