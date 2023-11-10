// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DartsActor.generated.h"

UCLASS()
class KADAIPROJECT_API ADartsActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADartsActor();

	//DartsActorÇÃUSceneComponent
	UPROPERTY(EditAnywhere)
		TObjectPtr<USceneComponent> DefaultSceneRoot;

	//Å@StaticMesh ComponentÇÃ
	UPROPERTY(EditAnywhere)
		TObjectPtr<UStaticMeshComponent> StaticMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
