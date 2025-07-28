#include "HealingItem.h"
#include "SpartaCharacter.h"

// 생성자
AHealingItem::AHealingItem()
{
	// 회복량과 아이템 타입을 설정합니다.
	HealingAmount = 20.0f;
	ItemType = "HealingItem";
}

// 아이템 활성화 함수
void AHealingItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);
	// 활성화한 액터가 "Player" 태그를 가지고 있는지 확인합니다.
	if (Activator && Activator->ActorHasTag("Player"))
	{
		// 플레이어 캐릭터로 캐스팅하여 체력을 회복시킵니다.
		if (ASpartaCharacter* PlayerCharacter = Cast<ASpartaCharacter>(Activator))
		{
			PlayerCharacter->AddHealth(HealingAmount);
		}
		// 아이템을 파괴합니다.
		DestroyItem();
	}
	
}
