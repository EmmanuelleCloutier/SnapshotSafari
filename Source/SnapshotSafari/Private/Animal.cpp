#include "SnapshotSafari/Public/Animal.h"
#include "BehaviorTree/BehaviorTree.h"

AAnimal::AAnimal()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AAnimal::BeginPlay()
{
	Super::BeginPlay();
	
}


