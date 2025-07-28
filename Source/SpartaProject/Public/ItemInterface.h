#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ItemInterface.generated.h"

// UINTERFACE는 언리얼 엔진의 인터페이스 클래스를 정의할 때 사용됩니다.
// MinimalAPI 키워드는 다른 모듈에서 이 인터페이스의 함수를 호출할 필요가 없을 때 사용됩니다.
UINTERFACE(MinimalAPI)
class UItemInterface : public UInterface
{
	GENERATED_BODY()
};

// 아이템이 구현해야 할 함수들을 정의하는 인터페이스입니다.
class SPARTAPROJECT_API IItemInterface
{
	GENERATED_BODY()

public:
	// 다른 액터와 오버랩되었을 때 호출될 순수 가상 함수입니다.
	UFUNCTION()
	virtual void OnItemOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult) = 0;
	// 다른 액터와의 오버랩이 끝났을 때 호출될 순수 가상 함수입니다.
	UFUNCTION()
	virtual void OnItemEndOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex) = 0;

	// 아이템을 활성화할 때 호출될 순수 가상 함수입니다.
	virtual void ActivateItem(AActor* Activator) = 0;
	// 아이템의 이름을 반환할 순수 가상 함수입니다.
	virtual FName GetItemName() const = 0;  

};