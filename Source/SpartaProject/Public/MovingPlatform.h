#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

// UCLASS() 매크로는 언리얼 엔진에게 이 클래스가 UObject 기반의 클래스임을 알립니다.
// 이를 통해 리플렉션, 가비지 컬렉션 등의 엔진 기능을 사용할 수 있게 됩니다.
UCLASS()
class SPARTAPROJECT_API AMovingPlatform : public AActor
{
	// GENERATED_BODY() 매크로는 언리얼 헤더 툴(UHT)이 생성한 코드를 이 위치에 포함시킵니다.
	// 리플렉션 시스템과 관련된 필수적인 코드들이 포함됩니다.
	GENERATED_BODY()

public:
	// 이 액터의 속성에 대한 기본값을 설정하는 생성자입니다.
	AMovingPlatform();

protected:
	// 게임이 시작되거나 액터가 스폰될 때 호출되는 함수입니다.
	virtual void BeginPlay() override;
	// 매 프레임마다 호출되는 함수입니다.
	virtual void Tick(float DeltaTime) override;

private:
	// UPROPERTY 매크로는 멤버 변수를 언리얼 엔진의 리플렉션 시스템에 노출시킵니다.
	// VisibleAnywhere 키워드는 이 프로퍼티를 에디터의 디테일 패널에서 볼 수 있게 하지만, 수정은 할 수 없게 합니다.
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComp; // 플랫폼의 외형을 나타내는 스태틱 메시 컴포넌트입니다.

	// EditAnywhere 키워드는 이 프로퍼티를 에디터의 디테일 패널에서 보고 수정할 수 있게 합니다.
	// Category = "Movement"는 이 프로퍼티를 디테일 패널의 "Movement" 카테고리 아래에 그룹화합니다.
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveSpeed; // 플랫폼의 이동 속도를 결정합니다.

	UPROPERTY(EditAnywhere, Category = "Movement")
	float DirectionChangeInterval; // 플랫폼이 방향을 바꾸는 시간 간격을 설정합니다.

	// FTimerHandle은 타이머를 관리하기 위한 구조체입니다.
	FTimerHandle DirectionTimerHandle; // 방향 전환 타이머를 위한 핸들입니다.

	float MoveDirection; // 현재 플랫폼의 이동 방향을 나타냅니다. (예: 1.0f 또는 -1.0f)

	// 플랫폼의 이동 방향을 반전시키는 함수입니다.
	void FlipDirection();
};