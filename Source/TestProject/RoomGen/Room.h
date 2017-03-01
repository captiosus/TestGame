// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Room.generated.h"

UENUM(BlueprintType)
enum class EDoorDirection : uint8 {
    DD_North    UMETA(DisplayName="North"),
    DD_East     UMETA(DisplayName="East"),
    DD_South    UMETA(DisplayName="South"),
    DD_West     UMETA(DisplayName="West")
};

USTRUCT(BlueprintType)
struct FPosition{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, Category="Room")
    int8 x;
    UPROPERTY(VisibleAnywhere, Category="Room")
    int8 y;

    FPosition(int8 newx=0, int8 newy=0);
    FPosition operator+(const FPosition& Other);
    FPosition& operator+=(const FPosition& Other);
    bool operator==(const FPosition& Other) const;
} ;

inline uint32 GetTypeHash(const FPosition& Position)
{
    uint32 Hashed(0);
    (Hashed += Position.x >> 16) += Position.y;
    return Hashed;
}

EDoorDirection GetOpposite(const EDoorDirection& Direction);
FPosition GetPosition(const EDoorDirection& Direction);

class ARoom;

UCLASS()
class TESTPROJECT_API ARoom : public AActor
{
	GENERATED_BODY()

public:
	ARoom();// Sets defaults for this object
    ARoom& operator+=(ARoom& Other);
    bool operator==(const ARoom& Other) const;
    bool operator!=(const ARoom& Other) const;

    UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category="Room")
    FName LevelName;

    UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category="Room")
    bool bIsSpawn;

    UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Room")
    FPosition Location;

    UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Room")
    TMap<EDoorDirection, ARoom*> Doors;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Room")
    TMap<EDoorDirection, bool>  OpenDoors;

    UFUNCTION(BlueprintCallable, Category="Room")
    bool bDoesRoomFit(ARoom *Room) const;

    UFUNCTION(BlueprintCallable, Category="Room")
    void TakePlace(ARoom *Sentinel);

    UFUNCTION(BlueprintCallable, Category="Room")
    TArray<ARoom*> ConstructSentinels();

    UFUNCTION(BlueprintCallable, Category="Room")
    void LoadRoom();
};
