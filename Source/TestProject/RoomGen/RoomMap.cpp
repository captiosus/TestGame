// Fill out your copyright notice in the Description page of Project Settings.

#include "TestProject.h"
#include "RoomMap.h"


// Sets default values
ARoomMap::ARoomMap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    ASpawn spawn_room;
    this->spawn = &spawn_room;
}

ARoomMap::ARoomMap(int8 size) : max_rooms(size)
{
    PrimaryActorTick.bCanEverTick = true;
    ASpawn spawn_room;
    this->spawn = &spawn_room;
}

// Called when the game starts or when spawned
void ARoomMap::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARoomMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARoomMap::AddRooms()
{
    ARoom* sentinel;
    while (this->num_rooms < this->max_rooms)
    {
        sentinel = this->sentinels[FMath::FRandRange(0, this->sentinels.Num() - 1)];
        
    }
}

void AddRoom(ARoom* sentinel)
{
    
}
