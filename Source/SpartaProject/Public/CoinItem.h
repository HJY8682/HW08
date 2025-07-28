#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "CoinItem.generated.h"

// 동전 아이템의 기본 클래스입니다.
// ABaseItem을 상속받습니다.
UCLASS()
class SPARTAPROJECT_API ACoinItem : public ABaseItem
{
	GENERATED_BODY()
	
public:
	// 생성자입니다.
	ACoinItem();

protected:
	// 동전의 점수 값입니다.
	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Item")
	int32 PointValue;

	// 아이템을 활성화하는 함수를 오버라이드합니다.
	virtual void ActivateItem(AActor* Activator) override;
	

};