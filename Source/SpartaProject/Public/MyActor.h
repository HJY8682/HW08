#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

// 테스트용으로 생성된 액터 클래스입니다.
UCLASS()
class SPARTAPROJECT_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// 생성자입니다.
	AMyActor();

protected:
	// 게임이 시작되거나 액터가 스폰될 때 호출됩니다.
	virtual void BeginPlay() override;

public:	
	// 매 프레임마다 호출됩니다.
	virtual void Tick(float DeltaTime) override;

};