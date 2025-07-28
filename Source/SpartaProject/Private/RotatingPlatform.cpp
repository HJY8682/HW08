#include "RotatingPlatform.h"
#include "Components/StaticMeshComponent.h"

// 생성자
ARotatingPlatform::ARotatingPlatform()
{
	// 매 틱마다 업데이트가 필요하므로 활성화합니다.
	PrimaryActorTick.bCanEverTick = true;

	// 스태틱 메시 컴포넌트를 생성하고 루트 컴포넌트로 설정합니다.
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

	// 회전 속도를 360도/초로 설정합니다.
	RotationSpeed = 360.0f;
}

// 게임이 시작될 때 호출되는 함수
void ARotatingPlatform::BeginPlay()
{
	Super::BeginPlay();
}

// 매 프레임마다 호출되는 함수
void ARotatingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 이번 프레임에 회전할 각도를 계산합니다.
	FRotator RotationDelta(0.f, RotationSpeed * DeltaTime, 0.f);

	// 계산된 각도만큼 액터를 월드 기준으로 회전시킵니다.
	AddActorWorldRotation(RotationDelta);
}