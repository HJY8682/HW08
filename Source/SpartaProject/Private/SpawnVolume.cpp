#include "SpawnVolume.h"
#include "Components/BoxComponent.h"

// 생성자
ASpawnVolume::ASpawnVolume()
{
	// 매 틱마다 업데이트할 필요가 없으므로 비활성화합니다.
	PrimaryActorTick.bCanEverTick = false;

	// 씬 컴포넌트를 생성하고 루트 컴포넌트로 설정합니다.
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);

	// 스폰 영역을 나타내는 박스 컴포넌트를 생성하고 씬 컴포넌트에 붙입니다.
	SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));
	SpawningBox->SetupAttachment(Scene);

	// 아이템 데이터 테이블을 초기화합니다.
	ItemDataTable = nullptr; 
}

// 무작위 아이템을 스폰하는 함수
AActor* ASpawnVolume::SpawnRandomItem()
{
	// 데이터 테이블에서 무작위 아이템 정보를 가져옵니다.
	if (FItemSpawnRow* SelectedItem = GetRandomItem())
	{
		// 실제 클래스를 가져와서 스폰합니다.
	    if (UClass* ActualClass = SelectedItem->ItemClass.Get())
		{
			return SpawnItem(ActualClass);
		}
	}
	return nullptr;
}

// 데이터 테이블에서 무작위 아이템 정보를 가져오는 함수
FItemSpawnRow* ASpawnVolume::GetRandomItem() const
{
	if (!ItemDataTable) return nullptr;

	// 데이터 테이블의 모든 행을 가져옵니다.
	TArray<FItemSpawnRow*> AllRows;
	static const FString ContextString = TEXT("ItemSpawnContext");

	ItemDataTable->GetAllRows(ContextString, AllRows);

	if (AllRows.IsEmpty()) return nullptr;
	
	// 모든 아이템의 스폰 확률의 합을 계산합니다.
	float TotalChance = 0.0f;
	for (const FItemSpawnRow* Row : AllRows)
	{
		if (Row)
		{
			TotalChance += Row->SpawnChance;
		}
	}

	// 0과 총 확률 사이의 무작위 값을 선택합니다.
	const float RandValue = FMath::FRandRange(0.0f, TotalChance);
	float AccumulatedChance = 0.0f;

	// 무작위 값에 해당하는 아이템을 선택합니다.
	for (FItemSpawnRow* Row : AllRows)
	{
		
			AccumulatedChance += Row->SpawnChance;
			if (AccumulatedChance >= RandValue)
			{
				return Row;
			}
		
	}
	return nullptr;
}

// 스폰 볼륨 내의 무작위 지점을 반환하는 함수
FVector ASpawnVolume::GetRandomPointInVolume() const
{
	FVector BoxExtent = SpawningBox->GetScaledBoxExtent(); 
	FVector BoxOrigin = SpawningBox->GetComponentLocation();

	return BoxOrigin + FVector(
		FMath::FRandRange(-BoxExtent.X, BoxExtent.X),
		FMath::FRandRange(-BoxExtent.Y, BoxExtent.Y),
		FMath::FRandRange(-BoxExtent.Z, BoxExtent.Z)
	);
}

// 특정 아이템 클래스를 스폰하는 함수
AActor* ASpawnVolume::SpawnItem(TSubclassOf<AActor> ItemClass)
{
	if (!ItemClass) return nullptr;

	// 월드에 아이템 액터를 스폰합니다.
	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(
		ItemClass, 
		GetRandomPointInVolume(), 
		FRotator::ZeroRotator
	);
	return SpawnedActor;
}