#include "SpartaGameState.h"  
#include "Kismet/GameplayStatics.h"  
#include "GameFramework/PlayerController.h"
#include "SpawnVolume.h"
#include "SpartaGameInstance.h"
#include "CoinItem.h"  
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include <SpartaPlayerController.h>

ASpartaGameState::ASpartaGameState()  
{  
	Score = 0;  
	SpawnedCoinCount = 0;  
	CollectedCoinCount = 0;  
	LevelDuration = 30.0f; 
	CurrentLevelIndex = 0; 
	MaxLevels = 3; 
	MaxWaveCount = 3;
	 
	
}  

void ASpartaGameState::BeginPlay()  
{  
	Super::BeginPlay();  
	
	StartLevel();  

	GetWorldTimerManager().SetTimer(  
		HUDUpdateTimerHandle,  
		this,  
		&ASpartaGameState::UpdateHUD,  
		0.1f,  
		true
	);
}  

int32 ASpartaGameState::GetScore() const  
{  
	return Score;  
}  

void ASpartaGameState::SetScore(int32 Amount)  
{  
	if (UGameInstance* GameInstance = GetGameInstance())  
	{  
		USpartaGameInstance* SpartaGameInstance = Cast<USpartaGameInstance>(GameInstance);  
		if (SpartaGameInstance)  
		{  
			SpartaGameInstance->AddScore(Amount);  
		}  
	} 
}  

void ASpartaGameState::StartLevel()  
{
	CurrentWaveIndex = 0;
	// HUD
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (ASpartaPlayerController* SpartaPlayerController = Cast<ASpartaPlayerController>(PlayerController))
		{
			SpartaPlayerController->ShowGameHUD(); 
		}
	}

	if (UGameInstance* GameInstance = GetGameInstance())
	{
		USpartaGameInstance* SpartaGameInstance = Cast<USpartaGameInstance>(GameInstance);
		if (SpartaGameInstance)
		{
			CurrentLevelIndex = SpartaGameInstance->CurrentLevelIndex;
		}
	}
//wave
	
	StartWave();

	GetWorldTimerManager().SetTimer(
		LevelTimerHandle,
		this,
		&ASpartaGameState::OnLevelTimeup,
		LevelDuration,
		false
		);
}
//wave
void ASpartaGameState::StartWave()
{

	
	UE_LOG(LogTemp, Warning, TEXT("Wave %d"), CurrentWaveIndex + 1);

	
	SpawnedCoinCount = 0;
	CollectedCoinCount = 0;
	
	TArray<AActor*> FoundVolumes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundVolumes);
	 
	const int32 CoinsPerWave = 5;

	
	if (FoundVolumes.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("spawnvolume ����"));
		EndWave();
		return;
	}
	
	for (int32 i = 0; i < CoinsPerWave; ++i)
	{
		
		if (FoundVolumes.Num() > 0)
		{
			ASpawnVolume* SpawnVolume = Cast<ASpawnVolume>(FoundVolumes[0]);
			if (SpawnVolume)
			{
				
				AActor* SpawnedActor = SpawnVolume->SpawnRandomItem();
				
				if (SpawnedActor && SpawnedActor->IsA(ACoinItem::StaticClass()))
				{
					SpawnedCoinCount++;
				}
			}
		}
	}
	UpdateHUD();	
}
//wave
void ASpartaGameState::EndWave()
{
	
	UE_LOG(LogTemp, Warning, TEXT("Wave %d Finish"), CurrentWaveIndex + 1);
	
	CurrentWaveIndex++;

	if (CurrentWaveIndex < MaxWaveCount)
	{
		StartWave();
	}
	else
	{
		EndLevel(); 
	}
}
void ASpartaGameState::OnLevelTimeup()  
{  
	EndLevel();  
}  

void ASpartaGameState::OnCoinCollected()  
{  
	CollectedCoinCount++;  

	UE_LOG(LogTemp, Warning, TEXT("Coin collected! Total collected: %d / %d"),  
		CollectedCoinCount,  
		SpawnedCoinCount);  
	
	if (SpawnedCoinCount > 0 && CollectedCoinCount >= SpawnedCoinCount)  
	{  
		EndWave(); 
	}  
}  

void ASpartaGameState::EndLevel()  
{  
	GetWorldTimerManager().ClearTimer(LevelTimerHandle);  
	CurrentLevelIndex++;  

	if (UGameInstance* GameInstance = GetGameInstance())
	{
		USpartaGameInstance* SpartaGameInstance = Cast<USpartaGameInstance>(GameInstance);
		if (SpartaGameInstance)
		{
			SetScore(Score);
			SpartaGameInstance->CurrentLevelIndex = CurrentLevelIndex;
		}
	}

	if (CurrentLevelIndex >= MaxLevels)  
	{  
		OnGameOver();  
		return;  
	}  
	if (LevelMapNames.IsValidIndex(CurrentLevelIndex))  
	{  
		UGameplayStatics::OpenLevel(GetWorld(), LevelMapNames[CurrentLevelIndex]);
	}  
	else
	{
		OnGameOver();
	}
}  

void ASpartaGameState::OnGameOver()  
{  
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (ASpartaPlayerController* SpartaPlayerController = Cast<ASpartaPlayerController>(PlayerController))
		{
			SpartaPlayerController->SetPause(true);
			SpartaPlayerController->ShowMainMenu(true);
		}
	}
}

void ASpartaGameState::UpdateHUD()  
{  
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())  
	{  
		if (ASpartaPlayerController* SpartaPlayerController = Cast<ASpartaPlayerController>(PlayerController))  
		{  
			if (UUserWidget* HUDWidget = SpartaPlayerController->GetHUDWidget())  
			{  
				if (UTextBlock* TimeText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("TimeText"))))  
				{  
					float RemainingTime = GetWorldTimerManager().GetTimerRemaining(LevelTimerHandle);
					TimeText->SetText(FText::FromString(FString::Printf(TEXT("Time Remaining: %.2f"), RemainingTime)));  
				}  
				if (UTextBlock* ScoreText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("ScoreText"))))  
				{  
					if (UGameInstance* GameInstance = GetGameInstance())  
					{  
						USpartaGameInstance* SpartaGameInstance = Cast<USpartaGameInstance>(GameInstance);  
						if (SpartaGameInstance)  
						{  
							ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score: %d"), SpartaGameInstance->TotalScore)));
						}  
					}  
				}
				if (UTextBlock* LevelIndexText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Level"))))  
				{  
					LevelIndexText->SetText(FText::FromString(FString::Printf(TEXT("Level: %d/%d"), CurrentLevelIndex + 1, MaxLevels)));  
				}
				if (UTextBlock* WaveText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("WaveText"))))
				{
					WaveText->SetText(FText::FromString(FString::Printf(TEXT("Wave: %d / %d"), CurrentWaveIndex + 1, MaxWaveCount)));
				}
			}  
		}  
	}  
}