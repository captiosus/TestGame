// Fill out your copyright notice in the Description page of Project Settings.

#include "TestProject.h"
#include "BaseCharacter.h"


// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

/**
 * Adds the Delta to the current Health of the character
 * @param Delta - change in health
 * @returns nothing
 **/
void ABaseCharacter::CalculateHealth(float Delta)
{
    Health += Delta;
    CalculateDead();
}

void ABaseCharacter::CalculateDead()
{
    if (Health <= 0) {
        bIsDead = false;
    } else {
        bIsDead = true;
    }
}

#if WITH_EDITOR
void ABaseCharacter::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    bIsDead = false;
    Health = 100;
    
    Super::PostEditChangeProperty(PropertyChangedEvent);
    
    CalculateDead();
}
#endif
