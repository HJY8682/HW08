#include "SpartaGameMode.h"
#include "SpartaCharacter.h"
#include "SpartaPlayerController.h"
#include "SpartaGameState.h"

// 생성자
ASpartaGameMode::ASpartaGameMode()
{
	// 기본 폰, 플레이어 컨트롤러, 게임 스테이트 클래스를 설정합니다.
	DefaultPawnClass = ASpartaCharacter::StaticClass();
	PlayerControllerClass = ASpartaPlayerController::StaticClass();
    GameStateClass = ASpartaGameState::StaticClass();
}
