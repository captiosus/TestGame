// Fill out your copyright notice in the Description page of Project Settings.

#include "TestProject.h"
#include "BaseFunctionLibrary.h"

TArray<UObject*> UBaseFunctionLibrary::GetSkeletalMeshes(FString Directory) {
    TSubclassOf<USkeletalMesh> ObjectClass;
    TArray<UObject*> Assets;
    
    UObjectLibrary* ObjectLibrary = UObjectLibrary::CreateLibrary(ObjectClass, false, GIsEditor);
    if (ObjectLibrary != nullptr)
    {
        ObjectLibrary->AddToRoot();
        ObjectLibrary->LoadAssetDataFromPath(TEXT("/Game/Weapons/SwordMeshes"));
        TArray<FAssetData> AssetDatas;
        ObjectLibrary->GetAssetDataList(AssetDatas);
        
        UObject* Asset;
        
        for (int32 i = 0; i < AssetDatas.Num(); ++i)
        {
            FAssetData& AssetData = AssetDatas[i];
            Asset = AssetData.GetAsset();
            if (Asset)
            {
                Assets.Add(AssetData.GetAsset());
            }
        }
    }
    return Assets;
}

