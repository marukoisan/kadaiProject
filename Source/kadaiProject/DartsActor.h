// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"//ボックスコリジョン用の追加要素
#include "Components/SphereComponent.h"
#include "DartsActor.generated.h"

UCLASS()
class KADAIPROJECT_API ADartsActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADartsActor();

	//DartsActorのUSceneComponent
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TObjectPtr<USceneComponent> DefaultSceneRoot;

	//　StaticMesh Componentの
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TObjectPtr<UStaticMeshComponent> StaticMesh;

	//当たり判定用の関数
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

	//ボックスコリジョンの変数
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TObjectPtr<USphereComponent> CollisionSphere;

	// Overlap
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

	//EndOverlap
	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);

	// Function that is called when the projectile hits something.
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent,
			AActor* OtherActor, 
			UPrimitiveComponent* OtherComponent, 
			FVector NormalImpulse, 
			const FHitResult& Hit);


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Tickの呼び出し
	virtual void Tick(float DeltaTime) override;

protected:


	FVector Straight;//FVector型の変数

	bool IsShow = true;
	float under = 11;
	double number = 0.8;
	float straight = 11;
	float width = 25;
	
};
