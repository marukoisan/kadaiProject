// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"//�{�b�N�X�R���W�����p�̒ǉ��v�f
#include "sphereActor.generated.h"

UCLASS()
class KADAIPROJECT_API AsphereActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AsphereActor();

	//DartsActor��USceneComponent
	UPROPERTY(EditAnywhere)
		TObjectPtr<USceneComponent> DefaultSceneRoot;

	//�@StaticMesh Component��
	UPROPERTY(EditAnywhere)
		TObjectPtr<UStaticMeshComponent> StaticMesh;

	//�{�b�N�X�R���W�����̕ϐ�
	/*UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TObjectPtr<USphereComponent> CollisionSphere;*/
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "variable")
		int32 variable;

protected:


public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

};
