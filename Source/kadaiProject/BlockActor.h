// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlockActor.generated.h"

UCLASS()
class KADAIPROJECT_API ABlockActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlockActor();

	//DartsActorÇÃUSceneComponent
	UPROPERTY(EditAnywhere)
		TObjectPtr<USceneComponent> DefaultSceneRoot;

	//Å@StaticMesh ComponentÇÃ
	UPROPERTY(EditAnywhere)
		TObjectPtr<UStaticMeshComponent> StaticMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Destroy the actor */
	//UFUNCTION(BlueprintCallable, Category = "Utilities", meta = (Keywords = "Delete", DisplayName = "DestroyActor", ScriptName = "DestroyActor"))
	//	virtual void K2_DestroyActor();
public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	virtual void NotifyHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

};
