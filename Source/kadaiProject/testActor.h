// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"//ボックスコリジョン用の追加要素
#include "testActor.generated.h"

UCLASS()
class KADAIPROJECT_API AtestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AtestActor();

	//DartsActorのUSceneComponent
	UPROPERTY(EditAnywhere)
		TObjectPtr<USceneComponent> DefaultSceneRoot;

	//　StaticMesh Componentの
	UPROPERTY(EditAnywhere)
		TObjectPtr<UStaticMeshComponent> StaticMesh;

	virtual void NotifyHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TObjectPtr<UBoxComponent> CollisionBox;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Overlap
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

protected:


public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

};
