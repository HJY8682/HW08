#include "SpartaCharacter.h"
#include "SpartaplayerController.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/TextBlock.h"
#include <SpartaGameState.h>

// 생성자
ASpartaCharacter::ASpartaCharacter()
{
	// 매 틱마다 업데이트할 필요가 없으므로 비활성화합니다.
	PrimaryActorTick.bCanEverTick = false; 

	// 스프링 암 컴포넌트를 생성하고 루트 컴포넌트에 붙입니다.
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 300.0f; // 카메라와의 거리를 300으로 설정합니다.
	SpringArmComp->bUsePawnControlRotation = true; // 컨트롤러의 회전을 스프링 암에 적용합니다.

	// 카메라 컴포넌트를 생성하고 스프링 암에 붙입니다.
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false; // 카메라 자체는 컨트롤러 회전을 따라가지 않습니다.

	// 머리 위 위젯 컴포넌트를 생성하고 메시(캐릭터 모델)에 붙입니다.
	OverheadWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("OverheadWidget"));
	OverheadWidget->SetupAttachment(GetMesh()); 
	OverheadWidget->SetWidgetSpace(EWidgetSpace::Screen); // 위젯을 스크린 공간에 표시합니다.

	// 이동 속도를 설정합니다.
	NormalSpeed = 600.0f;
	SprintSpeedMultiplier = 1.7f;
	SprintSpeed = NormalSpeed * SprintSpeedMultiplier;
	GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;

	// 체력을 설정합니다.
	Maxhealth = 100.0f;
	Health = Maxhealth;
}

// 게임이 시작될 때 호출되는 함수
void ASpartaCharacter::BeginPlay()
{
	Super::BeginPlay();
	UpdateOverheadHP(); // 머리 위 체력바를 업데이트합니다.
}

// 플레이어 입력을 설정하는 함수
void ASpartaCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Enhanced Input 컴포넌트로 캐스팅합니다.
	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// 플레이어 컨트롤러를 가져옵니다.
		if (ASpartaPlayerController* PlayerController = Cast<ASpartaPlayerController>(GetController()))
		{
			// 각 입력 액션에 함수를 바인딩합니다.
			if (PlayerController->MoveAction)
			{
				EnhancedInput->BindAction(PlayerController->MoveAction, ETriggerEvent::Triggered, this, &ASpartaCharacter::Move);
			}
			
			if (PlayerController->JumpAction)
			{
				EnhancedInput->BindAction(PlayerController->JumpAction, ETriggerEvent::Triggered, this, &ASpartaCharacter::StartJump);
				EnhancedInput->BindAction(PlayerController->JumpAction, ETriggerEvent::Triggered, this, &ASpartaCharacter::StopJump);
			}
			
			if (PlayerController->LookAction)
			{
				EnhancedInput->BindAction(PlayerController->LookAction, ETriggerEvent::Triggered, this, &ASpartaCharacter::Look);
			}

			if (PlayerController->SprintAction)
			{
				EnhancedInput->BindAction(PlayerController->SprintAction, ETriggerEvent::Triggered, this, &ASpartaCharacter::StartSprint);
				EnhancedInput->BindAction(PlayerController->SprintAction, ETriggerEvent::Completed, this, &ASpartaCharacter::StopSprint);
			}
		}
	}
}

// 이동 함수
void ASpartaCharacter::Move(const FInputActionValue& value)
{
	if (!Controller) return;

	const FVector2D MoveInput = value.Get<FVector2D>();

	// 앞뒤 이동
	if (!FMath::IsNearlyZero(MoveInput.X))
	{
		AddMovementInput(GetActorForwardVector(), MoveInput.X);
	}
	// 좌우 이동
	if (!FMath::IsNearlyZero(MoveInput.Y))
	{
		AddMovementInput(GetActorRightVector(), MoveInput.Y);
	}
}

// 점프 시작 함수
void ASpartaCharacter::StartJump(const FInputActionValue& value)
{
	if (value.Get<bool>())
	{
		Jump();
	}
}

// 점프 종료 함수
void ASpartaCharacter::StopJump(const FInputActionValue& value)
{
	if (!value.Get<bool>())
	{
		StopJumping();
	}
}

// 둘러보기 함수
void ASpartaCharacter::Look(const FInputActionValue& value)
{
	FVector2D LookInput = value.Get<FVector2D>();

	AddControllerYawInput(LookInput.X); // 좌우 회전
	AddControllerPitchInput(LookInput.Y); // 상하 회전
}

// 달리기 시작 함수
void ASpartaCharacter::StartSprint(const FInputActionValue& value)
{
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	}
}

// 달리기 종료 함수
void ASpartaCharacter::StopSprint(const FInputActionValue& value)
{
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
	}
}

// 현재 체력을 반환하는 함수
float ASpartaCharacter::GetHealth() const
{
	return Health;
}

// 체력을 추가하는 함수
void ASpartaCharacter::AddHealth(float Amount)
{
	Health = FMath::Clamp(Health + Amount, 0.0f, Maxhealth);
	UpdateOverheadHP();
}

// 데미지를 받는 함수
float ASpartaCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	// 체력을 감소시키고 0과 최대 체력 사이로 값을 제한합니다.
	Health = FMath::Clamp(Health - DamageAmount, 0.0f, Maxhealth);
	UpdateOverheadHP();

	// 체력이 0 이하이면 죽음 처리 함수를 호출합니다.
	if (Health <= 0.0f)
	{
		OnDeath();
	}
	return ActualDamage;
}

// 죽음 처리 함수
void ASpartaCharacter::OnDeath()
{
	// 게임 스테이트를 가져와 게임 오버를 알립니다.
	ASpartaGameState* SpartaGameState = GetWorld() ? GetWorld()->GetGameState<ASpartaGameState>() : nullptr;
	if (SpartaGameState)
	{
		SpartaGameState->OnGameOver();
	}
}

// 머리 위 체력바 업데이트 함수
void ASpartaCharacter::UpdateOverheadHP()
{
	if (!OverheadWidget) return;

	UUserWidget* OverheadWidgetInstance = OverheadWidget->GetUserWidgetObject();
	if (!OverheadWidgetInstance) return;

	// 위젯에서 "OverHeadHP"라는 이름의 텍스트 블록을 찾아 체력 텍스트를 업데이트합니다.
	if (UTextBlock* HPText = Cast<UTextBlock>(OverheadWidgetInstance->GetWidgetFromName(TEXT("OverHeadHP"))))
	{
		HPText->SetText(FText::FromString(FString::Printf(TEXT("HP: %.0f / %.0f"), Health, Maxhealth)));
	}
}