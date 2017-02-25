// Fill out your copyright notice in the Description page of Project Settings.

#include "TestProject.h"
#include "RoomMap.h"

const int NUM_ROOM_FIT_TRIES = 5;
const FString ROOMS_PATH = TEXT("/Game/Rooms");


// Sets default values
ARoomMap::ARoomMap(){}

void ARoomMap::SetAvailableRooms()
{
    auto ObjectLibrary = UObjectLibrary::CreateLibrary(UWorld::StaticClass(), false, true);
    ObjectLibrary->LoadAssetDataFromPath(ROOMS_PATH);
    TArray<FAssetData> AssetDatas;
    ObjectLibrary->GetAssetDataList(AssetDatas);
    
    FName name;
    for (int32 i = 0; i < AssetDatas.Num(); ++i)
    {
        FAssetData& AssetData = AssetDatas[i];
        name = AssetData.AssetName;
        this->AvailableRooms.Add(name);
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
    for (uint32 i = 0; i < Sentinels.Num(); ++i )
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
