#include "SnapshotSafari/Public/Animals/BaseAnimalAI.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionComponent.h"

ABaseAnimalAI::ABaseAnimalAI()
{
	PrimaryActorTick.bCanEverTick = true;

	// Création du composant de perception
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));

	// Création d'un senseur de vision
	UAISenseConfig_Sight* SightConfig = NewObject<UAISenseConfig_Sight>();
	SightConfig->SightRadius = 1000.0f; // Rayon de détection
	SightConfig->LoseSightRadius = 1100.0f; // Rayon après lequel l'animal perd la vue
	SightConfig->PeripheralVisionAngleDegrees = 90.0f; // Angle de vision

	// Ajout du senseur de vision au composant de perception
	AIPerceptionComponent->ConfigureSense(*SightConfig);

	// Ajout d'un événement pour la mise à jour de la perception
	AIPerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &ABaseAnimalAI::OnPerceptionUpdated);
}

void ABaseAnimalAI::BeginPlay()
{
	Super::BeginPlay();
	HandleLeaderDeath();
}

void ABaseAnimalAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (bIsGroupLeader)
	{
		WanderRandomly();
	}
	else
	{
		UpdateGroupMovement();
	}
}

void ABaseAnimalAI::WanderRandomly()
{
	if (AAIController* AIController = Cast<AAIController>(GetController()))
	{
		UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
		if (NavSystem)
		{
			FVector RandomLocation;
			if (NavSystem->K2_GetRandomReachablePointInRadius(GetWorld(), GetActorLocation(), RandomLocation, WanderRadius))
			{
				AIController->MoveToLocation(RandomLocation);
			}
		}
	}
}

void ABaseAnimalAI::AddToGroup(ABaseAnimalAI* NewMember)
{
	if (NewMember && !GroupMembers.Contains(NewMember))
	{
		GroupMembers.Add(NewMember);
		NewMember->GroupLeader = this;
		NewMember->bIsInGroup = true;

		AAIController* AIController = Cast<AAIController>(NewMember->GetController());
		if (AIController)
		{
			AIController->MoveToActor(this);
		}
	}
}

void ABaseAnimalAI::OnSeeOtherAnimal(AActor* OtherActor)
{
	ABaseAnimalAI* OtherAnimal = Cast<ABaseAnimalAI>(OtherActor);
	if (OtherAnimal && OtherAnimal->GetClass() == GetClass()) 
	{
		if (OtherAnimal->GroupLeader)  
		{
			GroupLeader = OtherAnimal->GroupLeader;
			GroupLeader->AddToGroup(this);
		}
		else if (!GroupLeader && !OtherAnimal->GroupLeader) 
		{
			GroupLeader = this;
			bIsGroupLeader = true;
			AddToGroup(OtherAnimal);
		}
	}
}


void ABaseAnimalAI::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	for (AActor* DetectedActor : UpdatedActors)
	{
		if (ABaseAnimalAI* OtherAnimal = Cast<ABaseAnimalAI>(DetectedActor))
		{
			// Appel de la logique d'ajout au groupe
			OnSeeOtherAnimal(DetectedActor);
		}
	}
}

void ABaseAnimalAI::UpdateGroupMovement()
{
	if (GroupLeader && !bIsGroupLeader)
	{
		AAIController* AIController = Cast<AAIController>(GetController());
		if (AIController)
		{
			FVector LeaderPosition = GroupLeader->GetActorLocation();
			FVector Offset = FVector(FMath::RandRange(-50, 50), FMath::RandRange(-50, 50), 0); 
			AIController->MoveToLocation(LeaderPosition + Offset);
		}
	}
}

void ABaseAnimalAI::HandleLeaderDeath()
{
	if (bIsGroupLeader)
	{
		if (GroupMembers.Num() > 0)
		{
			ABaseAnimalAI* NewLeader = nullptr;
			
			for (ABaseAnimalAI* Member : GroupMembers)
			{
				if (IsValid(Member))  
				{
					NewLeader = Member;
					break;
				}
			}

			if (NewLeader)
			{
				NewLeader->bIsGroupLeader = true;
				NewLeader->GroupLeader = NewLeader;

				for (ABaseAnimalAI* Member : GroupMembers)
				{
					Member->GroupLeader = NewLeader;
				}
			}
		}
	}

	GroupLeader = nullptr;
	GroupMembers.Empty();
	bIsGroupLeader = false;
}
