// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	bUseControllerRotationYaw = false;

	cam = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	cam->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	cam->SetRelativeLocation(FVector(0, 0, 40));

	jumping = false;

	canPlace = false;

	collectionRange = CreateDefaultSubobject<USphereComponent>(TEXT("CollectionRange"));
	collectionRange->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	collectionRange->SetSphereRadius(100.0f);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (wielded)
	{
		wielded->SetActorHiddenInGame(true);
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (jumping)
	{
		Jump();
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("Horizontal", this, &APlayerCharacter::HorizMove);
	InputComponent->BindAxis("Vertical", this, &APlayerCharacter::VertMove);

	InputComponent->BindAxis("HorizRotation", this, &APlayerCharacter::HorizRot);
	InputComponent->BindAxis("VertRotation", this, &APlayerCharacter::VertRot);

	InputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::CheckJump);
	InputComponent->BindAction("Jump", IE_Released, this, &APlayerCharacter::CheckJump);

	InputComponent->BindAction("Pickup", IE_Pressed, this, &APlayerCharacter::Interact);
}

void APlayerCharacter::HorizMove(float value)
{
	if (value)
	{
		AddMovementInput(GetActorRightVector(), value);
	}
}

void APlayerCharacter::VertMove(float value)
{
	if (value)
	{
		AddMovementInput(GetActorForwardVector(), value);
	}
}

void APlayerCharacter::HorizRot(float value)
{
	if (value)
	{
		AddActorLocalRotation(FRotator(0, value, 0));
	}
}

void APlayerCharacter::VertRot(float value)
{
	if (value)
	{
		float temp = cam->GetRelativeRotation().Pitch + value;

		if (temp < 65 && temp > -65)
		{
			cam->AddLocalRotation(FRotator(value, 0, 0));
		}
	}
}

void APlayerCharacter::CheckJump()
{
	if (jumping)
	{
		jumping = false;
	}
	else
	{
		jumping = true;
	}
}

void APlayerCharacter::Interact()
{
	TArray<AActor*> inRangeItems;
	collectionRange->GetOverlappingActors(inRangeItems);

	for (int i = 0; i < inRangeItems.Num(); i++)
	{
		if (!canPlace)
		{
			ASuitcasePickup* const testItem = Cast<ASuitcasePickup>(inRangeItems[i]);

			if (IsValid(testItem) && testItem->GetActive())
			{
				testItem->Interacted();

				if (wielded)
				{
					wielded->SetActorHiddenInGame(false);
					canPlace = true;
				}
			}
		}

		if (canPlace)
		{
			ASuitcasePlace* const testItem2 = Cast<ASuitcasePlace>(inRangeItems[i]);

			if (IsValid(testItem2) && testItem2->GetActive())
			{
				testItem2->Interacted();

				if (wielded)
				{
					wielded->SetActorHiddenInGame(true);
					canPlace = false;
				}
			}
		}
	}
}