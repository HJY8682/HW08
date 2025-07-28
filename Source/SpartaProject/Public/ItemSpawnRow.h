#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemSpawnRow.generated.h"

// USTRUCT는 언리얼 엔진에서 사용자 정의 데이터 구조체를 만들 때 사용됩니다.
// BlueprintType 키워드는 이 구조체를 블루프린트에서 사용할 수 있도록 합니다.
USTRUCT(BlueprintType)	
struct FItemSpawnRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	// 아이템의 이름입니다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemName;
	// 스폰될 아이템의 클래스입니다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AActor> ItemClass;
	// 아이템의 스폰 확률입니다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnChance;
	
};