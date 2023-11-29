// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockActor.h"


// Sets default values
ABlockActor::ABlockActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	//SceneComponentを作成する
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));

	//SceneComponentをRootComponentに設定する
	RootComponent = DefaultSceneRoot;

	//StaticMeshComponentを追加する
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

	//StaticMeshをLaodしてStaticMeshComponentのStaticMeshに設定する
	UStaticMesh* Mesh = LoadObject<UStaticMesh>(NULL, TEXT("/Engine/EngineMeshes/MaterialSphere"), NULL, LOAD_None, NULL);

	//StaticMeshをStaticMeshComponentに設定する
	StaticMesh->SetStaticMesh(Mesh);

	//StaticMeshComponentをRootComponentにAttachする
	StaticMesh->SetupAttachment(RootComponent);

	/*CollisionBoxの設定*/
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetBoxExtent(FVector(32.0f, 32.0f, 32.0f));//CollisionBoxの大きさを決める
	CollisionBox->SetCollisionProfileName("BlockAllDynamic");//アクターのコリジョンプリセットを変更
	CollisionBox->SetupAttachment(RootComponent);

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ABlockActor::OnOverlapBegin);//当たった瞬間のオーバーラップ
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &ABlockActor::OnOverlapEnd);//終わった瞬間のオーバーラップ
	/*ここから上が追加した項目*/

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

//関数の宣言を行っています。
void ABlockActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, "Overlap Begin Function Called");
}

void ABlockActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Overlap End Function Called");
}

// Called every frame
//void ABlockActor::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

