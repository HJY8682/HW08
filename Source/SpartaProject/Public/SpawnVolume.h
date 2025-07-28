#pragma once

#include "CoreMinimal.h"
#include "ItemSpawnRow.h"
#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

class UBoxComponent;

// 아이템을 스폰하는 영역을 정의하는 클래스입니다.
UCLASS()
class SPARTAPROJECT_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// 생성자입니다.
	ASpawnVolume();

	// 씬 루트 컴포넌트입니다.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	USceneComponent* Scene; 
	// 스폰 영역을 나타내는 박스 컴포넌트입니다.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	UBoxComponent* SpawningBox; 
	// 아이템 스폰 정보를 담고 있는 데이터 테이블입니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
    UDataTable* ItemDataTable; 

	// 데이터 테이블에서 무작위 아이템을 선택하여 스폰하는 함수입니다.
	UFUNCTION(BlueprintCallable, Category = "Spawning")
	AActor* SpawnRandomItem();

	// 데이터 테이블에서 무작위 아이템 정보를 가져오는 함수입니다.
	FItemSpawnRow* GetRandomItem() const;
	// 특정 아이템 클래스를 스폰하는 함수입니다.
	AActor* SpawnItem(TSubclassOf<AActor> ItemClass);
	// 스폰 영역 내에서 무작위 위치를 반환하는 함수입니다.
	FVector GetRandomPointInVolume() const;
};