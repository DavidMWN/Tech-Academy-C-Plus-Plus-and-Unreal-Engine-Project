// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "SuitcasePickup.generated.h"

UCLASS()
class QUICKGAME_API ASuitcasePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASuitcasePickup();

	void Interacted();
	bool GetActive();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
		class UStaticMeshComponent* mesh;

private:
	UPROPERTY()
		bool active;

	
};
