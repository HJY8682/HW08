#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "HealingItem.generated.h"

// 체력 회복 아이템 클래스입니다.
// ABaseItem을 상속받습니다.
UCLASS()
class SPARTAPROJECT_API AHealingItem : public ABaseItem
{
	GENERATED_BODY()

public:
	// 생성자입니다.
	AHealingItem();

	// 회복량입니다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 HealingAmount;

	// 아이템을 활성화하는 함수를 오버라이드합니다.
	virtual void ActivateItem(AActor* Activator) override;
	
};