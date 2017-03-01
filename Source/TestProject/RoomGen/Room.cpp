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

FPosition::FPosition(int8 assigned_x, int8 assigned_y) :
    x(assigned_x), y(assigned_y) {}

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

ARoom& ARoom::operator+=(ARoom& Other)
{
    for (auto& Doorway : Other.Doors)
    {
        if (this->Doors[Doorway.Key] && Other.Doors[Doorway.Key])
        {
            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Clashing Doors"));
        }
        else
        {
            this->Doors.Add(Doorway.Key, Doorway.Value);
            Other.Doors[Doorway.Key]->Doors[GetOpposite(Doorway.Key)] = this;
        }
    }
    return *this;
}

bool ARoom::operator==(const ARoom& Other) const
{
    return this->LevelName == Other.LevelName;
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

void ARoom::TakePlace(ARoom *Sentinel)
{
    for (auto& Doorway : Sentinel->Doors)
    {
        Doorway.Value->Doors[GetOpposite(Doorway.Key)] = this;
        this->Doors.Add(Doorway.Key, Doorway.Value);
    }
    this->Location = Sentinel->Location;
    Sentinel->Doors.Empty();
}

TArray<ARoom*> ARoom::ConstructSentinels()
{
    TArray<ARoom*> Sentinels;
    for (auto& Doorway : this->OpenDoors)
    {
        if (!this->Doors.Contains(Doorway.Key))
        {
            ARoom* Sentinel = NewObject<ARoom>(this);
            Sentinel->Location = this->Location + GetPosition(Doorway.Key);
            this->Doors.Add(Doorway.Key, Sentinel);
            Sentinel->Doors.Add(GetOpposite(Doorway.Key), this);
            Sentinels.Add(Sentinel);
        }
    }
    return Sentinels;
}

void ARoom::LoadRoom()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, LevelName.ToString());
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Is being loaded"));
   // FLatentActionInfo LatentInfo;
   // UGameplayStatics::LoadStreamLevel(this, this->LevelName, true, true, LatentInfo);
}
