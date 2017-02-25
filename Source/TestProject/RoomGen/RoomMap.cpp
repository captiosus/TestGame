// Fill out your copyright notice in the Description page of Project Settings.

#include "TestProject.h"
#include "RoomMap.h"

const int NUM_ROOM_FIT_TRIES = 5;
const FString ROOMS_PATH = TEXT("/Game/Rooms");


// Sets default values
ARoomMap::ARoomMap(){}

void ARoomMap::SetAvailableRooms()
{
	for (TActorIterator<ARoom> RoomItr(GetWorld()); RoomItr; ++RoomItr)
	{
		// Same as with the Object Iterator, access the subclass instance with the * or -> operators.
		ARoom *Room = *RoomItr;
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, Room->LevelName.ToString());
	}
}

ARoom* ARoomMap::FindRoom(const FName& Name) const
{
    for(TActorIterator<ARoom> RoomItr(GetWorld()); RoomItr; ++RoomItr)
    {
        ARoom *Room = *RoomItr;
        if (Room->LevelName == Name)
        {
            return Room;
        }
    }
    return nullptr;
}

// Called when the game starts or when spawned
void ARoomMap::BeginPlay()
{
    Super::BeginPlay();
	SetAvailableRooms();
    if (this->Spawn)
    {
//        GenerateRooms();
        this->Spawn->LoadRoom();
    }
}

// Fisher-Yates algorithm for shuffling an array in place in O(n) time
void ARoomMap::ShuffleSentinels()
{
    uint32 ShuffleIndex;
    ARoom* Swapper;
    for (int32 i = 0; i < Sentinels.Num(); ++i )
    {
        ShuffleIndex = FMath::FRandRange(0, i);
        if (i != ShuffleIndex)
        {
            Swapper = Sentinels[i];
            Sentinels[i] = Sentinels[ShuffleIndex];
            Sentinels[i] = Swapper;
        }
    }
}

void ARoomMap::AddSentinels(const TArray<ARoom*>& New)
{
    for(auto& RoomSentinel : New)
    {
        if (Map.Contains(RoomSentinel->Location))
        {
            *Map[RoomSentinel->Location] += *RoomSentinel;
        }else{
            Map.Add(RoomSentinel->Location, RoomSentinel);
            Sentinels.Add(RoomSentinel);
        }
    }
    ShuffleSentinels();
}
