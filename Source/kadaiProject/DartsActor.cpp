// Fill out your copyright notice in the Description page of Project Settings.


#include "DartsActor.h"

// Sets default values
ADartsActor::ADartsActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	//SceneComponentを作成する
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));

	//SceneComponentをRootComponentに設定する
	RootComponent = DefaultSceneRoot;
	
	//StaticMeshComponentを追加する
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	
	StaticMesh->AddLocalRotation(FQuat(FVector(0, 0, 1), UE_PI / 2));//ダーツを回転させる処理
	//StaticMesh->SetWorldLocation(FVector(-321.7f, -2.8f, 0.0f));

	//StaticMeshをLaodしてStaticMeshComponentのStaticMeshに設定する
	UStaticMesh* Mesh = LoadObject<UStaticMesh>(NULL, TEXT("/Game/FirstPerson/Darts2"), NULL, LOAD_None, NULL);

	//StaticMeshをStaticMeshComponentに設定する
	StaticMesh->SetStaticMesh(Mesh);

	// ArrowComponentの位置を設定する
	//Arrow->SetRelativeLocation(FVector(50.0f, 0.0f, 0.0f));



	//StaticMeshComponentをRootComponentにAttachする
	StaticMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ADartsActor::BeginPlay()
{
	Super::BeginPlay();
	
}


