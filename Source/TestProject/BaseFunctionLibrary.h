// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "BaseFunctionLibrary.generated.h"

/**
 *
 */
UCLASS()
class TESTPROJECT_API UBaseFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
    
public:
    UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetSkeletalMeshes", Category = "Utilities"))
    static TArray<UObject*> GetSkeletalMeshes(FString Directory);
};
