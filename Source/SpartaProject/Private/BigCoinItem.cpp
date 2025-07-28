#include "BigCoinItem.h"

// 생성자
ABigCoinItem::ABigCoinItem()
{
	// 점수와 아이템 타입을 설정합니다.
	PointValue = 50;
	ItemType = "BigCoin";

}

// 아이템 활성화 함수
void ABigCoinItem::ActivateItem(AActor* Activator)
{
	// 부모 클래스의 ActivateItem 함수를 호출하여 공통 로직을 수행합니다.
	Super::ActivateItem(Activator);
}