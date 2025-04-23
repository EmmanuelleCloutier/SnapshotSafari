// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Animal.generated.h"

UCLASS()
class SNAPSHOTSAFARI_API AAnimal : public ACharacter
{
	GENERATED_BODY()

public:
	AAnimal();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, Category = "AI")
	class UBehaviorTree* BehaviorTree;

	UFUNCTION(BlueprintCallable)
	UBehaviorTree* GetBehaviorTree() { return BehaviorTree; }
};
