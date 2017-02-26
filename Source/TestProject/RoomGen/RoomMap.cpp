// Fill out your copyright notice in the Description page of Project Settings.

#include "TestProject.h"
#include "RoomMap.h"

const int NUM_ROOM_FIT_TRIES = 5;

// Sets default values
ARoomMap::ARoomMap(){}

void ARoomMap::PickSpawn()
{
    if(AvailableSpawns.Num() > 0)
    {
        uint32 SpawnIndex = FMath::FRandRange(0, AvailableSpawns.Num() - 1);
        this->Spawn = AvailableSpawns[SpawnIndex];
        AddSentinels(Spawn->ConstructSentinels());
        AvailableSpawns.RemoveAt(SpawnIndex);
        Map.Add(Spawn->Location, Spawn);
        ++NumRooms;
    }
}

void ARoomMap::SetAvailableRooms()
{

	for (TActorIterator<ARoom> RoomItr(GetWorld()); RoomItr; ++RoomItr)
	{
		// Same as with the Object Iterator, access the subclass instance with the * or -> operators.
		ARoom *Room = *RoomItr;
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, Room->LevelName.ToString());
        if (Room->bIsSpawn)
        {
            this->AvailableSpawns.Add(Room);
        }
        else
        {
            this->AvailableRooms.Add(Room);
        }
	}
}

// Called when the game starts or when spawned
void ARoomMap::BeginPlay()
{
    Super::BeginPlay();
	SetAvailableRooms();
    PickSpawn();
    if (this->Spawn)
    {
       GenerateMap();
       this->Spawn->LoadRoom();
       CleanupSentinels();
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("No Spawn"));
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

void ARoomMap::CleanupSentinels()
{
    for (ARoom* Sentinel : Sentinels)
    {
        Sentinel->Unlink();
        Map.Remove(Sentinel->Location);
    }
    Sentinels.Empty();
}

void ARoomMap::GenerateMap()
{
    if (!this->Spawn)
    {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("No Spawn"));
        return;
    }
    while (AvailableRooms.Num() > 0 && Sentinels.Num() > 0 && NumRooms < MaxRooms)
    {
        uint32 RoomIndex = FMath::FRandRange(0, AvailableRooms.Num() - 1);
        ARoom *Room = AvailableRooms[RoomIndex];
        uint8 Tries = 0;
        do
        {
            uint32 SentinelIndex = FMath::FRandRange(0, Sentinels.Num() - 1);
            ARoom *Sentinel = Sentinels[SentinelIndex];
            if (Sentinel->bDoesRoomFit(Room))
            {
                Sentinel->InsertRoom(Room);
                AddSentinels(Room->ConstructSentinels());
                Sentinels.RemoveAt(SentinelIndex);
                Room->LoadRoom();
                ++NumRooms;
                break;
            }
        } while (Tries++ < NUM_ROOM_FIT_TRIES);
        AvailableRooms.RemoveAt(RoomIndex);
    }
}
