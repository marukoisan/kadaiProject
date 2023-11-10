// Fill out your copyright notice in the Description page of Project Settings.


#include "DartsActor.h"

// Sets default values
ADartsActor::ADartsActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	//SceneComponent‚ğì¬‚·‚é
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));

	//SceneComponent‚ğRootComponent‚Éİ’è‚·‚é
	RootComponent = DefaultSceneRoot;
	
	//StaticMeshComponent‚ğ’Ç‰Á‚·‚é
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

	//StaticMesh‚ğLaod‚µ‚ÄStaticMeshComponent‚ÌStaticMesh‚Éİ’è‚·‚é
	UStaticMesh* Mesh = LoadObject<UStaticMesh>(NULL, TEXT("/Game/FirstPerson/DartsMesh2"), NULL, LOAD_None, NULL);

	//StaticMesh‚ğStaticMeshComponent‚Éİ’è‚·‚é
	StaticMesh->SetStaticMesh(Mesh);

	// ArrowComponent‚ÌˆÊ’u‚ğİ’è‚·‚é
	//Arrow->SetRelativeLocation(FVector(50.0f, 0.0f, 0.0f));
	StaticMesh->SetRelativeLocation(FVector(-321.7f, -2.8f, 0.0f));


	//StaticMeshComponent‚ğRootComponent‚ÉAttach‚·‚é
	StaticMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ADartsActor::BeginPlay()
{
	Super::BeginPlay();
	
}


