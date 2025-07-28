#include "MineItem.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// 생성자
AMineItem::AMineItem()
{
	// 폭발 관련 변수들을 초기화합니다.
	ExplosionDelay = 5.0f;
	ExplosionRadius = 300.0f;
	ExplosionDamage = 50.0f;
	ItemType = "Mine";
	bHasExploded = false;

	// 폭발 범위를 감지할 구체 컴포넌트를 생성하고 설정합니다.
	ExplosionCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ExplosionCollision"));
	ExplosionCollision->InitSphereRadius(ExplosionRadius);
	ExplosionCollision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	ExplosionCollision->SetupAttachment(Scene);

 }

// 아이템 활성화 함수
void AMineItem::ActivateItem(AActor* Activator)
{
	// 이미 폭발했다면 함수를 종료합니다.
	if(bHasExploded)
	{
		return;
	}
	Super::ActivateItem(Activator);

	// 폭발 지연 시간 후에 Explode 함수를 호출하도록 타이머를 설정합니다.
	GetWorld()->GetTimerManager().SetTimer(
		ExplosionTimerHandle, 
		this, 
		&AMineItem::Explode, 
		ExplosionDelay, 
		false
	);
	bHasExploded = true;
}

// 폭발 처리 함수
void AMineItem::Explode()
{
	UParticleSystemComponent* Particle = nullptr;
	// 폭발 파티클이 설정되어 있으면 파티클을 스폰합니다.
	if (ExplosionParticle)
	{
		Particle = UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(), 
			ExplosionParticle, 
			GetActorLocation(), 
			GetActorRotation(),
			false
		);
	}

	// 폭발 사운드가 설정되어 있으면 사운드를 재생합니다.
	if (ExplosionSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			GetWorld(),
			ExplosionSound, 
			GetActorLocation()
		);
	}

	// 폭발 범위 내에 있는 액터들을 가져옵니다.
	TArray<AActor*> OverlappingActors;
	ExplosionCollision->GetOverlappingActors(OverlappingActors);

	// 오버랩된 액터들 중 "Player" 태그를 가진 액터에게 데미지를 적용합니다.
	for (AActor* Actor : OverlappingActors)
	{
		if (Actor && Actor->ActorHasTag("Player"))
		{
			UGameplayStatics::ApplyDamage(
				Actor, 
				ExplosionDamage, 
				nullptr,
				this, 
				UDamageType::StaticClass()
			);

		}
	}
	// 아이템을 파괴합니다.
	DestroyItem(); 

	// 파티클이 스폰되었으면 2초 후에 파괴되도록 타이머를 설정합니다.
	if (Particle)
	{
		FTimerHandle DestroyParicleTimerHandle;

		GetWorld()->GetTimerManager().SetTimer(
			DestroyParicleTimerHandle, 
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