// Fill out your copyright notice in the Description page of Project Settings.

#include "TestProject.h"
#include "LevelMap.h"
#include <vector>

// Sets default values
ALevelMap::ALevelMap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALevelMap::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALevelMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

std::vector<Room> ALevelMap::GenerateRooms()
{
    
}
