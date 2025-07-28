#pragma once

#include "CoreMinimal.h"
#include "CoinItem.h"
#include "SmallCoinItem.generated.h"

// 작은 동전 아이템 클래스입니다.
// ACoinItem을 상속받습니다.
UCLASS()
class SPARTAPROJECT_API ASmallCoinItem : public ACoinItem
{
	GENERATED_BODY()

public:
	// 생성자입니다.
	ASmallCoinItem();

	// 아이템을 활성화하는 함수를 오버라이드합니다.
	virtual void ActivateItem(AActor* Activator) override;
	
};