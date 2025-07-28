#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "MineItem.generated.h"

// 지뢰 아이템 클래스입니다.
// ABaseItem을 상속받습니다.
UCLASS()
class SPARTAPROJECT_API AMineItem : public ABaseItem
{
	GENERATED_BODY()
	
public:
	// 생성자입니다.
	AMineItem();

	// 폭발 범위를 감지하기 위한 구체 컴포넌트입니다.
	USphereComponent* ExplosionCollision;

	// 폭발 파티클 효과입니다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Effects")
	UParticleSystem* ExplosionParticle;
	// 폭발 사운드입니다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Effects")
	USoundBase* ExplosionSound;

	// 폭발 지연 시간입니다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	float ExplosionDelay;

	// 폭발 반경입니다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	float ExplosionRadius;

	// 폭발 데미지입니다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	float ExplosionDamage;
	
	// 폭발했는지 여부를 나타내는 변수입니다.
	bool bHasExploded;

	// 폭발 타이머 핸들입니다.
	FTimerHandle ExplosionTimerHandle;

	// 아이템을 활성화하는 함수를 오버라이드합니다.
	virtual void ActivateItem(AActor* Activator) override;

	// 폭발을 처리하는 함수입니다.
	void Explode();
};