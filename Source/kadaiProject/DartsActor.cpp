// Fill out your copyright notice in the Description page of Project Settings.


#include "DartsActor.h"
#include "kadaiProjectCharacter.h"

// Sets default values
ADartsActor::ADartsActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

	/*ボックスコリジョン(CollisionBox)の設定*/
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetBoxExtent(FVector(32.0f, 32.0f, 32.0f));
	CollisionBox->SetCollisionProfileName("BlockAllDynamic");
	CollisionBox->SetupAttachment(RootComponent);
	

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ADartsActor::OnOverlapBegin);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &ADartsActor::OnOverlapEnd);
	
	
}

void ADartsActor::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
	//K2_DestroyActor();
}

void ADartsActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, "Overlap Begin Function Called");
	//K2_DestroyActor();
	
	IsShow = false;//判定をfalseに変更

	//スポーンされたアクター(ダーツ)の移動処理
	//AddActorLocalOffset(FVector(0.0f, 0.0f, 0.0f));
}

void ADartsActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Overlap End Function Called");
}

void ADartsActor::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	K2_DestroyActor();
}

// Called when the game starts or when spawned
void ADartsActor::BeginPlay()
{
	Super::BeginPlay();

	CollisionBox->OnComponentHit.AddDynamic(this, &ADartsActor::OnHit);
	
}


//Event tickの呼び出し
void ADartsActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//スポーンされたアクター(ダーツ)の移動処理
	if (IsShow == true)//tureの間なら動く
	{
		AddActorLocalOffset(FVector(5.0f, 0.0f, 0.0f));
	}
	else
	{
		AddActorLocalOffset(FVector(0.0f, 0.0f, 0.0f));
	}
	
}

