#include "SnapshotSafari/Public/AnimalController.h"

#include "AbstractNavData.h"
#include "SnapshotSafari/Public/Animal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

AAnimalController::AAnimalController()
{
	PrimaryActorTick.bCanEverTick = false;
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
}

void AAnimalController::BeginPlay()
{
	Super::BeginPlay();

	AAnimal* animal = Cast<AAnimal>(GetPawn());
	if (animal && animal->GetBehaviorTree())
	{
		BlackboardComp->InitializeBlackboard(*(animal->BehaviorTree->BlackboardAsset));
		BehaviorTreeComp->StartTree(*animal->BehaviorTree);
	}
	
}

