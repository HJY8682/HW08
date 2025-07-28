#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SpartaPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

// 플레이어의 입력을 처리하고 HUD를 관리하는 플레이어 컨트롤러 클래스입니다.
UCLASS()
class SPARTAPROJECT_API ASpartaPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	// 생성자입니다.
	ASpartaPlayerController();

	// 입력 매핑 컨텍스트입니다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* InputMappingContext;
	// 이동 입력 액션입니다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* MoveAction;
	// 보기 입력 액션입니다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* LookAction;
	// 점프 입력 액션입니다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* JumpAction;
	// 달리기 입력 액션입니다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* SprintAction;
	// HUD 위젯 클래스입니다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<UUserWidget> HUDWidgetClass;
	// 생성된 HUD 위젯 인스턴스입니다.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HUD")
	UUserWidget* HUDWidgetInstance;
	// 메인 메뉴 위젯 클래스입니다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu")
	TSubclassOf<UUserWidget> MainMenuWidgetClass;
	// 생성된 메인 메뉴 위젯 인스턴스입니다.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Menu")
	UUserWidget* MainMenuWidgetInstance;

	// HUD 위젯을 반환하는 함수입니다.
	UFUNCTION(BlueprintCallable, Category = "HUD")
	UUserWidget* GetHUDWidget() const;

	// 게임 HUD를 표시하는 함수입니다.
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void ShowGameHUD();
	// 메인 메뉴를 표시하는 함수입니다.
	UFUNCTION(BlueprintCallable, Category = "Menu")
	void ShowMainMenu(bool bIsRestart);
	// 게임을 시작하는 함수입니다.
	UFUNCTION(BlueprintCallable, Category = "Menu")
	void StartGame();

protected:
	// 게임이 시작될 때 호출됩니다.
	virtual void BeginPlay() override;

};