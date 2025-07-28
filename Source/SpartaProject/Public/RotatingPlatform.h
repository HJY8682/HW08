#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotatingPlatform.generated.h"

// 회전하는 플랫폼 클래스입니다.
UCLASS()
class SPARTAPROJECT_API ARotatingPlatform : public AActor
{
	GENERATED_BODY()

public:
	// 생성자입니다.
	ARotatingPlatform();

protected:
	// 게임이 시작되거나 액터가 스폰될 때 호출됩니다.
	virtual void BeginPlay() override;

public:
	// 매 프레임마다 호출됩니다.
	virtual void Tick(float DeltaTime) override;

private:
	// 플랫폼의 외형을 나타내는 스태틱 메시 컴포넌트입니다.
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComp;

	// 회전 속도입니다.
	UPROPERTY(EditAnywhere, Category = "Rotation")
	float RotationSpeed;
};