#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "SpartaGameMode.generated.h"

// 게임의 규칙을 정의하는 게임 모드 클래스입니다.
UCLASS()
class SPARTAPROJECT_API ASpartaGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	// 생성자입니다.
	ASpartaGameMode();

};