// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"//�{�b�N�X�R���W�����p�̒ǉ��v�f
#include "DartsActor.generated.h"

UCLASS()
class KADAIPROJECT_API ADartsActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADartsActor();

	//DartsActor��USceneComponent
	UPROPERTY(EditAnywhere)
		TObjectPtr<USceneComponent> DefaultSceneRoot;

	//�@StaticMesh Component��
	UPROPERTY(EditAnywhere)
		TObjectPtr<UStaticMeshComponent> StaticMesh;

	//�����蔻��p�̊֐�
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

	//�{�b�N�X�R���W�����̕ϐ�
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TObjectPtr<UBoxComponent> CollisionBox;

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

	//Tick�̌Ăяo��
	virtual void Tick(float DeltaTime) override;

protected:


	FVector Straight;//FVector�^�̕ϐ�

	bool IsShow = true;

	
};
