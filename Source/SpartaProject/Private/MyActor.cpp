#include "MyActor.h"

// 생성자
AMyActor::AMyActor()
{
	// 매 틱마다 업데이트가 필요하므로 활성화합니다.
	PrimaryActorTick.bCanEverTick = true;

}

// 게임이 시작될 때 호출되는 함수
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// 매 프레임마다 호출되는 함수
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}