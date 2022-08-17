// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SuitcasePlace.generated.h"

UCLASS()
class QUICKGAME_API ASuitcasePlace : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASuitcasePlace();

	void Interacted();
	bool GetActive();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
		class UStaticMeshComponent* mesh;	

private:
	UPROPERTY()
		bool active;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Placed", meta = (BlueprintProtected))
		bool isPlaced;
};
