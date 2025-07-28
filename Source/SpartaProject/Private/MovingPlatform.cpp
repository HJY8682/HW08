#include "MovingPlatform.h"
#include "Components/StaticMeshComponent.h"

// 생성자
AMovingPlatform::AMovingPlatform()
{
	// 매 틱마다 업데이트가 필요하므로 활성화합니다.
	PrimaryActorTick.bCanEverTick = true;

	// 스태틱 메시 컴포넌트를 생성하고 루트 컴포넌트로 설정합니다.
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

	// 초기 이동 속도, 방향 전환 간격, 이동 방향을 설정합니다.
	MoveSpeed = 200.f;              
	DirectionChangeInterval = 2.5f; 
	MoveDirection = 1.f;            
}

// 게임이 시작될 때 호출되는 함수
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	// 타이머를 설정하여 DirectionChangeInterval마다 FlipDirection 함수를 반복적으로 호출합니다.
	GetWorld()->GetTimerManager().SetTimer(
		DirectionTimerHandle,            
		this,                            
		&AMovingPlatform::FlipDirection, 
		DirectionChangeInterval,        
		true                             
	);
}

// 매 프레임마다 호출되는 함수
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 현재 위치를 가져옵니다.
	FVector CurrentLocation = GetActorLocation();

	// 이번 프레임에 이동할 거리를 계산합니다.
	FVector MoveOffset = FVector(MoveSpeed * DeltaTime * MoveDirection, 0.f, 0.f);

	// 계산된 거리만큼 액터를 이동시킵니다.
	SetActorLocation(CurrentLocation + MoveOffset);
}

// 이동 방향을 반전시키는 함수
void AMovingPlatform::FlipDirection()
{
	MoveDirection *= -1.f;
}