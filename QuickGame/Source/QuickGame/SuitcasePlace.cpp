// Fill out your copyright notice in the Description page of Project Settings.


#include "SuitcasePlace.h"

// Sets default values
ASuitcasePlace::ASuitcasePlace()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	active = true;
	isPlaced = false;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh)"));
	mesh->SetupAttachment(RootComponent);
}

void ASuitcasePlace::Interacted()
{
	isPlaced = true;
	active = false;
	mesh->SetHiddenInGame(false);
}

bool ASuitcasePlace::GetActive()
{
	return active;
}

