#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ARandomPlatformSpawner.generated.h"

// UCLASS() 매크로는 언리얼 엔진에게 이 클래스가 UObject 기반의 클래스임을 알립니다.
// 이를 통해 리플렉션, 가비지 컬렉션 등의 엔진 기능을 사용할 수 있게 됩니다.
UCLASS()
class SPARTAPROJECT_API ARandomPlatformSpawner : public AActor
{
	// GENERATED_BODY() 매크로는 언리얼 헤더 툴(UHT)이 생성한 코드를 이 위치에 포함시킵니다.
	// 리플렉션 시스템과 관련된 필수적인 코드들이 포함됩니다.
	GENERATED_BODY()

public:
	// 생성자입니다.
	ARandomPlatformSpawner();

protected:
	// 게임이 시작되거나 액터가 스폰될 때 호출되는 함수입니다.
	virtual void BeginPlay() override;

private:
	// UPROPERTY() 매크로를 사용하여 언리얼 엔진에 변수를 노출시킵니다.
	// EditAnywhere 키워드를 통해 에디터의 디테일 패널에서 값을 수정할 수 있습니다.
	// 스폰 간격을 설정합니다.
	UPROPERTY(EditAnywhere)
	float SpawnInterval;

	// 스폰될 위치의 최소값을 설정합니다.
	UPROPERTY(EditAnywhere)
	FVector2D SpawnMin;

	// 스폰될 위치의 최대값을 설정합니다.
	UPROPERTY(EditAnywhere)
	FVector2D SpawnMax;

	// 스폰될 회전하는 플랫폼의 블루프린트 클래스를 설정합니다.
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> RotatingPlatformClass;

	// 스폰될 움직이는 플랫폼의 블루프린트 클래스를 설정합니다.
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> MovingPlatformClass;

	// 스폰 타이머를 위한 핸들입니다.
	FTimerHandle SpawnTimerHandle;

	// 무작위 플랫폼을 스폰하는 함수입니다.
	void SpawnRandomPlatform();
};