// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "RoomGen/Room.h"
#include "EngineUtils.h"
#include "RoomMap.generated.h"

UCLASS()
class TESTPROJECT_API ARoomMap : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARoomMap();

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Room Map")
    TArray<FName> AvailableRooms;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Room Map")
    ARoom* Spawn;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Room Map")
    TArray<ARoom*> Sentinels;

    UPROPERTY(EditAnywhere, Category="Room Map")
    uint32 MaxRooms;

    UPROPERTY(VisibleAnywhere, Category="Room Map")
    uint32 NumRooms;

    UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Room Map")
    TMap<FPosition, ARoom*> Map;

    UFUNCTION(BlueprintCallable, Category="Room Map")
    void SetAvailableRooms();
    
    UFUNCTION(BlueprintCallable, Category="Room Map")
    void ShuffleSentinels();
    
    UFUNCTION(BlueprintCallable, Category="Room Map")
    void AddSentinels(const TArray<ARoom*>& New);
    
    UFUNCTION(BlueprintCallable, Category="Room")
    ARoom* FindRoom(const FName& Name) const;
    
protected:
    UFUNCTION(BlueprintCallable, Category="Room Map")
    virtual void BeginPlay() override;
};
