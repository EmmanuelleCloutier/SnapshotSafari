#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseAnimalAI.generated.h"

UCLASS()
class SNAPSHOTSAFARI_API ABaseAnimalAI : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseAnimalAI();

protected:
	virtual void BeginPlay() override;

public:
	// Référence vers le leader du groupe
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grouping")
	ABaseAnimalAI* GroupLeader = nullptr;

	// Liste des membres du groupe
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grouping")
	TArray<ABaseAnimalAI*> GroupMembers;

	// Indique si cet animal est un leader
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grouping")
	bool bIsGroupLeader = false;

	// Détection d'autres animaux
	UFUNCTION(BlueprintCallable, Category = "AI")
	void OnSeeOtherAnimal(AActor* OtherActor);

	UFUNCTION()
	void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);

	// Mise à jour des déplacements en groupe
	void UpdateGroupMovement();

	// Ajout d'un membre au groupe
	void AddToGroup(ABaseAnimalAI* NewMember);

	// Gestion de la mort du leader
	virtual void HandleLeaderDeath();

	// Mouvement aléatoire en dehors d'un groupe
	void WanderRandomly();

	virtual void Tick(float DeltaTime) override;

protected:
	// Rayon maximal de déplacement en errance
	UPROPERTY(EditAnywhere, Category = "AI")
	float WanderRadius = 1000.0f;

	// Rayon de détection d'autres animaux
	UPROPERTY(EditAnywhere, Category = "AI")
	float DetectionRadius = 500.0f;

	// Indique si l'animal est en groupe
	UPROPERTY(VisibleAnywhere, Category = "AI")
	bool bIsInGroup = false;
	
	// Composant de perception de l'IA
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	UAIPerceptionComponent* AIPerceptionComponent;

};
