#include "BaseItem.h"
#include "Components/SphereComponent.h"
#include "kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// 생성자
ABaseItem::ABaseItem()
{
	// 매 틱마다 업데이트할 필요가 없으므로 비활성화합니다.
	PrimaryActorTick.bCanEverTick = false;

	// 씬 컴포넌트를 생성하고 루트 컴포넌트로 설정합니다.
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);

	// 충돌을 위한 구체 컴포넌트를 생성하고 씬 컴포넌트에 붙입니다.
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	Collision->SetupAttachment(Scene);

	// 스태틱 메시 컴포넌트를 생성하고 충돌 컴포넌트에 붙입니다.
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(Collision);

	// 오버랩 이벤트에 함수를 바인딩합니다.
	Collision->OnComponentBeginOverlap.AddDynamic(this, &ABaseItem::OnItemOverlap);
	Collision->OnComponentEndOverlap.AddDynamic(this, &ABaseItem::OnItemEndOverlap);

}

// 아이템 오버랩 시작 시 호출되는 함수
void ABaseItem::OnItemOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	// 오버랩된 액터가 "Player" 태그를 가지고 있는지 확인합니다.
	if (OtherActor && OtherActor->ActorHasTag("Player"))
	{
		// 디버그 메시지를 출력하고 아이템을 활성화합니다.
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Overlap")));
		ActivateItem(OtherActor);
	}
}

// 아이템 오버랩 종료 시 호출되는 함수 (현재는 비어 있음)
void ABaseItem::OnItemEndOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
}

// 아이템을 활성화하는 함수
void ABaseItem::ActivateItem(AActor* Activator) 
{
	UParticleSystemComponent* Particle = nullptr;

	// 픽업 파티클이 설정되어 있으면 파티클을 스폰합니다.
	if (PickupParticle)
	{
		Particle = UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			PickupParticle,
			GetActorLocation(),
			GetActorRotation(),
			true
		);
	}
	// 픽업 사운드가 설정되어 있으면 사운드를 재생합니다.
	if (PickupSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			this,
			PickupSound,
			GetActorLocation()
		); 
	}
	// 파티클이 스폰되었으면 2초 후에 파괴되도록 타이머를 설정합니다.
	if (Particle)
	{
		FTimerHandle DestroyParticleTimerHandle;

		GetWorld()->GetTimerManager().SetTimer(
			DestroyParticleTimerHandle,
			[Particle]()
			{
				if (Particle)
				{
					Particle->DestroyComponent();
				}
			},
			2.0f, 
			false
		);
	}
}

// 아이템 이름을 반환하는 함수
FName ABaseItem::GetItemName() const 
{
	return ItemType;

}

// 아이템을 파괴하는 함수
void ABaseItem::DestroyItem()
{
	Destroy();
}
