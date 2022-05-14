// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "ProceduralmeshComponent.h"
#include "TestActor.generated.h"

UCLASS()
class PTC_API ATestActor : public AActor
{
	GENERATED_BODY()

    UProceduralMeshComponent* _proceduralMesh;
	
public:	
	// Sets default values for this actor's properties
	ATestActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    virtual void OnConstruction(const FTransform& transform) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
