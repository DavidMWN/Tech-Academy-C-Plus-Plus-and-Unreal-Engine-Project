// Fill out your copyright notice in the Description page of Project Settings.


#include "SuitcasePickup.h"
#include "SuitcasePlace.h"

// Sets default values
ASuitcasePickup::ASuitcasePickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	active = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh)"));
	mesh->SetupAttachment(RootComponent);
}

void ASuitcasePickup::Interacted()
{
	active = false;
	SetActorHiddenInGame(true);


}

bool ASuitcasePickup::GetActive()
{
	return active;
}

