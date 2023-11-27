// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockActor.h"

// Sets default values
ABlockActor::ABlockActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	//SceneComponentÇçÏê¨Ç∑ÇÈ
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));

	//SceneComponentÇRootComponentÇ…ê›íËÇ∑ÇÈ
	RootComponent = DefaultSceneRoot;

	//StaticMeshComponentÇí«â¡Ç∑ÇÈ
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

	//StaticMeshÇLaodÇµÇƒStaticMeshComponentÇÃStaticMeshÇ…ê›íËÇ∑ÇÈ
	UStaticMesh* Mesh = LoadObject<UStaticMesh>(NULL, TEXT("/Engine/EngineMeshes/MaterialSphere"), NULL, LOAD_None, NULL);

	//StaticMeshÇStaticMeshComponentÇ…ê›íËÇ∑ÇÈ
	StaticMesh->SetStaticMesh(Mesh);

	//StaticMeshComponentÇRootComponentÇ…AttachÇ∑ÇÈ
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

