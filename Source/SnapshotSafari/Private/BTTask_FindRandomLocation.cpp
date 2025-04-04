#include "BTTask_FindRandomLocation.h"
#include "AnimalController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

UBTTask_FindRandomLocation::UBTTask_FindRandomLocation()
{
	NodeName = "FindRandomLocation";
}

EBTNodeResult::Type
UBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAnimalController* AnimalController = Cast<AAnimalController>(OwnerComp.GetAIOwner());
	if (!AnimalController) return EBTNodeResult::Failed;

	APawn* AIPawn = AnimalController->GetPawn();
	if (!AIPawn) return EBTNodeResult::Failed;

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(AIPawn->GetWorld());
	if (!NavSystem) return EBTNodeResult::Failed;

	FVector Origin = AIPawn->GetActorLocation();
	FNavLocation NavLocation;
	
	if (NavSystem->GetRandomPointInNavigableRadius(Origin, 1000.0f, NavLocation))

	{
		AnimalController->GetBlackboardComponent()->SetValueAsVector("PatrolLocation", NavLocation.Location);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}