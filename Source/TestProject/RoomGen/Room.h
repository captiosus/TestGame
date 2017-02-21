// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Room.generated.h"

class ARoom;

//UENUM(BlueprintType)
//enum class EDoorDirection : uint8 {
//    DD_North    UMETA(DisplayName="North"),
//    DD_East     UMETA(DisplayName="East"),
//    DD_South    UMETA(DisplayName="South"),
//    DD_West     UMETA(DisplayName="West")
//} ;

UCLASS()
class TESTPROJECT_API ARoom : public AActor
{
	GENERATED_BODY()
	
public:

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Room")
    FString LevelName;

public:	
	// Sets default values for this actor's properties
	ARoom();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
    ARoom* North;
    ARoom* East;
    ARoom* South;
    ARoom* West;
};
