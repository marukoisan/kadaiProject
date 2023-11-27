// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockActor.h"

// Sets default values
ABlockActor::ABlockActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	//SceneComponent���쐬����
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));

	//SceneComponent��RootComponent�ɐݒ肷��
	RootComponent = DefaultSceneRoot;

	//StaticMeshComponent��ǉ�����
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

	//StaticMesh��Laod����StaticMeshComponent��StaticMesh�ɐݒ肷��
	UStaticMesh* Mesh = LoadObject<UStaticMesh>(NULL, TEXT("/Engine/EngineMeshes/MaterialSphere"), NULL, LOAD_None, NULL);

	//StaticMesh��StaticMeshComponent�ɐݒ肷��
	StaticMesh->SetStaticMesh(Mesh);

	//StaticMeshComponent��RootComponent��Attach����
	StaticMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ABlockActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABlockActor::NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other,class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
	K2_DestroyActor();
}

// Called every frame
//void ABlockActor::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

