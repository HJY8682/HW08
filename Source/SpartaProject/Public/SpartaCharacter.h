#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SpartaCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UWidgetComponent;
struct FInputActionValue;

// 플레이어 캐릭터 클래스입니다.
UCLASS()
class SPARTAPROJECT_API ASpartaCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// 생성자입니다.
	ASpartaCharacter();

	// 카메라를 캐릭터에 붙이기 위한 스프링 암 컴포넌트입니다.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* SpringArmComp;
	// 플레이어의 시점을 담당하는 카메라 컴포넌트입니다.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* CameraComp;

	// 캐릭터 머리 위에 표시될 위젯 컴포넌트입니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	UWidgetComponent* OverheadWidget;

	// 현재 체력을 반환하는 함수입니다.
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealth() const;

	// 체력을 증가시키는 함수입니다.
	UFUNCTION(BlueprintCallable, Category = "Health")
	void AddHealth(float Amount);
	
protected:
	// 최대 체력입니다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "health")
	float Maxhealth;
	// 현재 체력입니다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "health")
	float Health;

	// 게임이 시작되거나 캐릭터가 스폰될 때 호출됩니다.
	virtual void BeginPlay() override;
	// 플레이어 입력을 설정하는 함수입니다.
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// 데미지를 받았을 때 호출되는 함수입니다.
	virtual float TakeDamage(
		float DamageAmount, 
		struct FDamageEvent const& DamageEvent, 
		AController* EventInstigator,
		AActor* DamageCauser) override;

	// 이동 입력을 처리하는 함수입니다.
	UFUNCTION()
	void Move(const FInputActionValue& value);
	// 점프 시작 입력을 처리하는 함수입니다.
	UFUNCTION()
	void StartJump(const FInputActionValue& value);
	// 점프 종료 입력을 처리하는 함수입니다.
	UFUNCTION()
	void StopJump(const FInputActionValue& value);
	// 시점 변환 입력을 처리하는 함수입니다.
	UFUNCTION()
	void Look(const FInputActionValue& value);
	// 달리기 시작 입력을 처리하는 함수입니다.
	UFUNCTION()
	void StartSprint(const FInputActionValue& value);
	// 달리기 종료 입력을 처리하는 함수입니다.
	UFUNCTION()
	void StopSprint(const FInputActionValue& value);

	// 캐릭터가 죽었을 때 호출되는 함수입니다.
	void OnDeath();
	// 머리 위 체력바 위젯을 업데이트하는 함수입니다.
	void UpdateOverheadHP();

	// 일반 속도입니다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float NormalSpeed;
	// 달리기 속도 배율입니다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float SprintSpeedMultiplier;
	// 최종 달리기 속도입니다.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float SprintSpeed;
	
private:
};