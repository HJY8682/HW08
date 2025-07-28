#include "CoinItem.h"
#include "Engine/World.h"
#include "SpartaGameState.h"

// 생성자
ACoinItem::ACoinItem()
{
	// 점수와 아이템 타입을 초기화합니다.
	PointValue = 0;
	ItemType = "DefaultCoin";

}

// 아이템 활성화 함수
void ACoinItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);
	// 활성화한 액터가 "Player" 태그를 가지고 있는지 확인합니다.
	if (Activator && Activator->ActorHasTag("Player"))
	{
		// 월드와 게임 스테이트를 가져옵니다.
		if (UWorld* World = GetWorld())
		{
			if(ASpartaGameState* GameState = World->GetGameState<ASpartaGameState>())
			{
				// 점수를 추가하고 코인 획득을 알립니다.
				GameState->SetScore(PointValue);
				GameState->OnCoinCollected();
			}
		}
		// 아이템을 파괴합니다.
		DestroyItem();
	}
	
}