#include "SpartaPlayerController.h"
#include "SpartaGamestate.h"
#include "SpartaGameInstance.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "kismet/GameplayStatics.h"
#include "Components/TextBlock.h"

// 생성자
ASpartaPlayerController::ASpartaPlayerController()
	:InputMappingContext(nullptr),
	MoveAction(nullptr),
	LookAction(nullptr),
	JumpAction(nullptr),
	SprintAction(nullptr),
	HUDWidgetClass(nullptr),
	HUDWidgetInstance(nullptr),
	MainMenuWidgetClass(nullptr),
	MainMenuWidgetInstance(nullptr)

{
	
}

// 게임이 시작될 때 호출되는 함수
void ASpartaPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	// Enhanced Input Subsystem에 Input Mapping Context를 추가합니다.
	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = 
			LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (InputMappingContext)
			{
				Subsystem->AddMappingContext(InputMappingContext, 0);
			}
	    }
	}

	// 현재 맵 이름이 "MenuLevel"을 포함하면 메인 메뉴를 표시합니다.
	FString CurrentMapName = GetWorld()->GetMapName();
	if (CurrentMapName.Contains("MenuLevel"))
	{
		ShowMainMenu(false);
	}
}

// HUD 위젯 인스턴스를 반환하는 함수
UUserWidget* ASpartaPlayerController::GetHUDWidget() const
{
	return HUDWidgetInstance;
}

// 메인 메뉴를 표시하는 함수
void ASpartaPlayerController::ShowMainMenu(bool bIsRestart)
{
	// 기존 HUD 위젯이 있으면 제거합니다.
	if (HUDWidgetInstance)
	{
		HUDWidgetInstance->RemoveFromParent();
		MainMenuWidgetInstance = nullptr;
	}
	
	// 기존 메인 메뉴 위젯이 있으면 제거합니다.
	if (MainMenuWidgetInstance)
	{
		MainMenuWidgetInstance->RemoveFromParent();
		MainMenuWidgetInstance = nullptr;
	}
	// 메인 메뉴 위젯 클래스가 설정되어 있으면 위젯을 생성하고 뷰포트에 추가합니다.
	if (MainMenuWidgetClass)
	{
		MainMenuWidgetInstance = CreateWidget<UUserWidget>(this, MainMenuWidgetClass);
		if (MainMenuWidgetInstance)
		{
			MainMenuWidgetInstance->AddToViewport();

			// 마우스 커서를 표시하고 입력 모드를 UI 전용으로 설정합니다.
			bShowMouseCursor = true;
			SetInputMode(FInputModeUIOnly()); 
		}

		// 재시작 여부에 따라 시작 버튼의 텍스트를 변경합니다.
		if(UTextBlock* ButtonText = Cast<UTextBlock>(MainMenuWidgetInstance->GetWidgetFromName("StartButtonText")))
		{
			if (bIsRestart)
			{
				ButtonText->SetText(FText::FromString(TEXT("Restart Game")));
			}
			else {
				ButtonText->SetText(FText::FromString(TEXT("Start Game")));
			}
		}

		// 재시작인 경우 게임 오버 애니메이션을 재생하고 총 점수를 표시합니다.
		if (bIsRestart)
		{
			UFunction* PlayAnimFunc = MainMenuWidgetInstance->FindFunction(FName("PlayGameOverAnim"));
			if (PlayAnimFunc)
			{
				MainMenuWidgetInstance->ProcessEvent(PlayAnimFunc, nullptr);
			}

			if (UTextBlock* TotalScoreText = Cast<UTextBlock>(MainMenuWidgetInstance->GetWidgetFromName("TotalScoreText")))
			{
				if (USpartaGameInstance* SpartaGameInstance = Cast<USpartaGameInstance>(UGameplayStatics::GetGameInstance(this)))
				{
					TotalScoreText->SetText(FText::FromString(
						FString::Printf(TEXT("Total Score: %d"), SpartaGameInstance->TotalScore)));
				}
			}
		}
	}
}

// 게임 HUD를 표시하는 함수
void ASpartaPlayerController::ShowGameHUD()
{
	// 기존 HUD 위젯이 있으면 제거합니다.
	if (HUDWidgetInstance)
	{
		HUDWidgetInstance->RemoveFromParent();
		HUDWidgetInstance = nullptr;
	}

	// 기존 메인 메뉴 위젯이 있으면 제거합니다.
	if (MainMenuWidgetInstance)
	{
		MainMenuWidgetInstance->RemoveFromParent();
		MainMenuWidgetInstance = nullptr;
	}
	// HUD 위젯 클래스가 설정되어 있으면 위젯을 생성하고 뷰포트에 추가합니다.
	if (HUDWidgetClass)
	{
		HUDWidgetInstance = CreateWidget<UUserWidget>(this, HUDWidgetClass);
		if (HUDWidgetInstance)
		{
			HUDWidgetInstance->AddToViewport();

			// 마우스 커서를 숨기고 입력 모드를 게임 전용으로 설정합니다.
			bShowMouseCursor = false;
			SetInputMode(FInputModeGameOnly()); 
		}

		// 게임 스테이트를 가져와 HUD를 업데이트합니다.
		ASpartaGameState* SpartaGameState = GetWorld() ? GetWorld()->GetGameState<ASpartaGameState>() : nullptr;
		if (SpartaGameState)
		{
			SpartaGameState->UpdateHUD();
		}
	}
}

// 게임을 시작하는 함수
void ASpartaPlayerController::StartGame()
{
	// 게임 인스턴스의 레벨 인덱스와 총 점수를 초기화합니다.
	if(USpartaGameInstance* SpartaGameInstance = Cast<USpartaGameInstance>(UGameplayStatics::GetGameInstance(this)))
	{
		SpartaGameInstance->CurrentLevelIndex = 0;
		SpartaGameInstance->TotalScore = 0;
	}

	// 기본 레벨을 열고 일시정지를 해제합니다.
	UGameplayStatics::OpenLevel(GetWorld(), FName("BasicLevel"));
	SetPause(false);
}
