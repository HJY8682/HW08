#include "ARandomPlatformSpawner.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"

// 생성자
ARandomPlatformSpawner::ARandomPlatformSpawner()
{
	// 매 틱마다 업데이트할 필요가 없으므로 비활성화합니다.
	PrimaryActorTick.bCanEverTick = false; 

	// 플랫폼 스폰 간격을 3초로 설정합니다.
	SpawnInterval = 3.f;

	// 플랫폼이 스폰될 X, Y 좌표의 최소, 최대 범위를 설정합니다.
	SpawnMin = FVector2D(-500.f, -500.f);
	SpawnMax = FVector2D(500.f, 500.f);
}

// 게임이 시작될 때 호출되는 함수
void ARandomPlatformSpawner::BeginPlay()
{
	Super::BeginPlay();

	// 타이머를 설정하여 SpawnInterval마다 SpawnRandomPlatform 함수를 반복적으로 호출합니다.
	GetWorld()->GetTimerManager().SetTimer(
		SpawnTimerHandle,                 
		this,                             
		&ARandomPlatformSpawner::SpawnRandomPlatform, 
		SpawnInterval,                     
		true                               
	);
}

// 무작위 플랫폼을 스폰하는 함수
void ARandomPlatformSpawner::SpawnRandomPlatform()
{
	// 50% 확률로 회전하는 플랫폼 또는 움직이는 플랫폼을 선택합니다.
	TSubclassOf<AActor> PlatformToSpawn = FMath::RandBool() ? RotatingPlatformClass : MovingPlatformClass;

	// 스폰할 플랫폼 클래스가 유효하지 않으면 함수를 종료합니다.
	if (!PlatformToSpawn) return;

	// 설정된 범위 내에서 무작위 X, Y 좌표를 생성합니다.
	float RandX = FMath::FRandRange(SpawnMin.X, SpawnMax.X);
	float RandY = FMath::FRandRange(SpawnMin.Y, SpawnMax.Y);

	// 스폰될 Z 좌표는 스포너 액터의 Z 좌표와 동일하게 설정합니다.
	float SpawnZ = GetActorLocation().Z;

	// 최종 스폰 위치를 결정합니다.
	FVector SpawnLocation(RandX, RandY, SpawnZ);

	// 월드에 새로운 플랫폼 액터를 스폰합니다.
	GetWorld()->SpawnActor<AActor>(PlatformToSpawn, SpawnLocation, FRotator::ZeroRotator);
}