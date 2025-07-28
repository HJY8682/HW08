#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemInterface.h"
#include "BaseItem.generated.h"

class USphereComponent;

// 모든 아이템의 기반이 되는 클래스입니다.
// IItemInterface를 상속받아 아이템 관련 함수를 구현합니다.
UCLASS()
class SPARTAPROJECT_API ABaseItem : public AActor, public IItemInterface
{
	GENERATED_BODY()
	
public:	
	// 생성자입니다.
	ABaseItem();

protected:
	// 아이템의 종류를 나타내는 이름입니다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FName ItemType; 

	// 아이템의 루트 컴포넌트입니다.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Components")
	USceneComponent* Scene; 
	// 아이템과의 충돌을 감지하는 구체 컴포넌트입니다.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Components")
	USphereComponent* Collision;
	// 아이템의 외형을 나타내는 스태틱 메시 컴포넌트입니다.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Components")
	UStaticMeshComponent* StaticMesh;

	// 아이템을 획득했을 때 재생될 파티클 효과입니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item|Effects")
	UParticleSystem* PickupParticle; 
	// 아이템을 획득했을 때 재생될 사운드입니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item|Effects")
	USoundBase* PickupSound; 

	// 다른 액터와 오버랩되었을 때 호출되는 함수입니다.
	virtual void OnItemOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult) override;
	// 다른 액터와의 오버랩이 끝났을 때 호출되는 함수입니다.
	virtual void OnItemEndOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex) override;
	// 아이템을 활성화하는 함수입니다.
	virtual void ActivateItem(AActor* Activator) override; 
	// 아이템의 이름을 반환하는 함수입니다.
	virtual FName GetItemName() const override;

	// 아이템을 파괴하는 함수입니다.
	virtual void DestroyItem();

	
};