// Fill out your copyright notice in the Description page of Project Settings.


#include "DartsActor.h"

// Sets default values
ADartsActor::ADartsActor()
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
	UStaticMesh* Mesh = LoadObject<UStaticMesh>(NULL, TEXT("/Game/FirstPerson/DartsMesh2"), NULL, LOAD_None, NULL);

	//StaticMesh��StaticMeshComponent�ɐݒ肷��
	StaticMesh->SetStaticMesh(Mesh);

	// ArrowComponent�̈ʒu��ݒ肷��
	//Arrow->SetRelativeLocation(FVector(50.0f, 0.0f, 0.0f));
	StaticMesh->SetRelativeLocation(FVector(-321.7f, -2.8f, 0.0f));


	//StaticMeshComponent��RootComponent��Attach����
	StaticMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ADartsActor::BeginPlay()
{
	Super::BeginPlay();
	
}


