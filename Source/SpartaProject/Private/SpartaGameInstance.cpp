#include "SpartaGameInstance.h"

// 생성자
USpartaGameInstance::USpartaGameInstance()
{
	// 총 점수와 현재 레벨 인덱스를 초기화합니다.
	TotalScore = 0;
	CurrentLevelIndex = 0;
}

// 점수를 추가하는 함수
void USpartaGameInstance::AddScore(int32 Amount)
{
	TotalScore += Amount;
	// 로그를 출력하여 점수 변화를 확인합니다.
	UE_LOG(LogTemp, Warning, TEXT("Score added: %d, Total Score: %d"), Amount, TotalScore);
}
