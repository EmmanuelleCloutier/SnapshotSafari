#pragma once

#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "AnimalController.generated.h"

UCLASS()
class SNAPSHOTSAFARI_API AAnimalController : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	AAnimalController();

	UPROPERTY(EditAnywhere, Category = "AI")
	class UBehaviorTreeComponent* BehaviorTreeComp;

	UPROPERTY(EditAnywhere, Category = "AI")
	class UBlackboardComponent* BlackboardComp;
};
