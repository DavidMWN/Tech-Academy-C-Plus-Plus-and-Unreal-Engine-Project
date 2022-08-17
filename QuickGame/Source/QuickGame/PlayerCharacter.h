// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/StaticMeshActor.h"
#include "SuitcasePickup.h"
#include "SuitcasePlace.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class QUICKGAME_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void HorizMove(float value);
	void VertMove(float value);

	void HorizRot(float value);
	void VertRot(float value);

	void CheckJump();

	UPROPERTY()
		bool jumping;

	UPROPERTY()
		bool canPlace;

	UPROPERTY(EditAnywhere, Category = "Camera")
		UCameraComponent* cam;

	void Interact();

	UPROPERTY(EditAnywhere, Category = "Pickup", meta = (AllowPrivateAccess = true))
		USphereComponent* collectionRange;

	UPROPERTY(EditAnywhere, Category = "Pickup")
		AStaticMeshActor* wielded;
};
