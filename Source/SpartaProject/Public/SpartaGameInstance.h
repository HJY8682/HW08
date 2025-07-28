#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SpartaGameInstance.generated.h"

// 게임의 전반적인 상태를 관리하는 게임 인스턴스 클래스입니다.
// 레벨이 변경되어도 유지됩니다.
UCLASS()
class SPARTAPROJECT_API USpartaGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	// 생성자입니다.
	USpartaGameInstance();

	// 총 점수입니다.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameData")
	int32 TotalScore;

	// 현재 레벨 인덱스입니다.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameData")
	int32 CurrentLevelIndex;

	// 점수를 추가하는 함수입니다.
	UFUNCTION(BlueprintCallable, Category = "GameData")
	void AddScore(int32 Amount);
};