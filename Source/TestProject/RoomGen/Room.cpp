// Fill out your copyright notice in the Description page of Project Settings.

#include "TestProject.h"
#include "Room.h"

EDoorDirection GetOpposite(const EDoorDirection& Direction)
{
    switch (Direction) {
    case EDoorDirection::DD_North:  return EDoorDirection::DD_South;    break;
    case EDoorDirection::DD_East:   return EDoorDirection::DD_West;     break;
    case EDoorDirection::DD_South:  return EDoorDirection::DD_North;    break;
    case EDoorDirection::DD_West:   return EDoorDirection::DD_East;     break;
    default:                        throw 1;                            break;
    }
}

FPosition GetPosition(const EDoorDirection& Direction)
{
    switch (Direction) {
    case EDoorDirection::DD_North:  return FPosition(0, 1);       break;
    case EDoorDirection::DD_East:   return FPosition(1, 0);       break;
    case EDoorDirection::DD_South:  return FPosition(0, -1);      break;
    case EDoorDirection::DD_West:   return FPosition(-1, 0);      break;
    default:                        throw 1;                      break;
    }
}

FPosition::FPosition(int8 newx, int8 newy)
{
    this->x = newx;
    this->y = newy;
}

FPosition::FPosition(const FPosition& Other)
{
    this->x = Other.x;
    this->y = Other.y;
}

FPosition FPosition::operator+(const FPosition& Other)
{
    return *new FPosition(this->x + Other.x, this->y + Other.y);
}

FPosition& FPosition::operator+=(const FPosition& Other)
{
    this->x += Other.x;
    this->y += Other.y;
    return *this;
}

bool FPosition::operator==(const FPosition& Other) const
{
    return this->x == Other.x && this->y == Other.y;
}

// Sets default values
ARoom::ARoom()
{
    this->OpenDoors.Add(EDoorDirection::DD_North, true);
    this->OpenDoors.Add(EDoorDirection::DD_East, true);
    this->OpenDoors.Add(EDoorDirection::DD_South, true);
    this->OpenDoors.Add(EDoorDirection::DD_West, true);
}

ARoom::ARoom(const FPosition& MapLocation) : Location(MapLocation) { ARoom(); }

ARoom& ARoom::operator+=(ARoom& Other)
{
    if (*this != Other)
    {
        throw 1;
    }
    for (auto& Doorway : Other.Doors)
    {
        if (this->Doors[Doorway.Key] && Other.Doors[Doorway.Key])
        {
            throw 1;
        }
        this->Doors.Add(Doorway.Key, Doorway.Value);
        Other.Doors[Doorway.Key]->Doors[GetOpposite(Doorway.Key)] = this;
    }
    return *this;
}

bool ARoom::operator==(const ARoom& Other) const
{
    return this->Location == Other.Location;
}
bool ARoom::operator !=(const ARoom& Other) const
{
    return !(*this == Other);
}

//Sentinel Method for determining if a room is a valid fit for the current position
bool ARoom::bDoesRoomFit(ARoom* Room) const
{
    // Checks each existing connection for an open match in new room
    for( auto& Doorway : this->Doors )
    {
        if (!Room->OpenDoors[Doorway.Key])
        {
            return false;
        }
    }
    return true;
}

void ARoom::InsertRoom(ARoom *Room)
{
    for (auto& Doorway : this->Doors)
    {
        Doorway.Value->Doors[GetOpposite(Doorway.Key)] = Room;
        Room->Doors.Add(Doorway.Key, Doorway.Value);
        this->Doors[Doorway.Key] = NULL;
    }
    Room->Location = this->Location;
}

void ARoom::Unlink()
{
    for (auto& Doorway : this->Doors)
    {
        Doorway.Value->Doors.RemoveAt(GetOpposite(Doorway.Key));
    }
    this->Doors.Empty();
}

TArray<ARoom*> ARoom::ConstructSentinels()
{
    TArray<ARoom*> Sentinels;
    for (auto& Doorway : this->OpenDoors)
    {
        if (!this->Doors.Contains(Doorway.Key))
        {
            this->Doors.Add(Doorway.Key, NewObject<ARoom>(this));
            this->Doors[Doorway.Key]->Location = this->Location + GetPosition(Doorway.Key);
            Sentinels.Add(this->Doors[Doorway.Key]);
        }
    }
    return Sentinels;
}

void ARoom::LoadRooms() const
{
   for (auto& Doorway : this->Doors)
   {
       Doorway.Value->LoadRoom();
   }
}

void ARoom::LoadRoom()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, LevelName.ToString());
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Is being loaded"));
   // FLatentActionInfo LatentInfo;
   // UGameplayStatics::LoadStreamLevel(this, this->LevelName, true, true, LatentInfo);
}
