// Fill out your copyright notice in the Description page of Project Settings.


#include "testActor.h"
#include "kadaiProjectCharacter.h" //追加
#include "DartsActor.h"            //追加
#include "Kismet/GameplayStatics.h"//追加



// Sets default values
AtestActor::AtestActor()
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
	UStaticMesh* Mesh = LoadObject<UStaticMesh>(NULL, TEXT("/Engine/EngineMeshes/Cube"), NULL, LOAD_None, NULL);

	//StaticMeshをStaticMeshComponentに設定する
	StaticMesh->SetStaticMesh(Mesh);

	//StaticMeshComponentをRootComponentにAttachする
	StaticMesh->SetupAttachment(RootComponent);

	/*CollisionBoxの設定*/
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetBoxExtent(FVector(150.0f, 150.0f, 150.0f));//CollisionBoxの大きさを決める
	CollisionBox->SetCollisionProfileName("OverlapAllDynamic");//アクターのコリジョンプリセットを変更
	CollisionBox->SetupAttachment(RootComponent);

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AtestActor::OnOverlapBegin);//当たった瞬間のオーバーラップ

	//大きさ変更
	this->SetActorRelativeScale3D(FVector(0.25f, 0.25f, 0.25f));




}

void AtestActor::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
}

// Called when the game starts or when spawned
void AtestActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AtestActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, "Overlap Begin Function Called");
	ACharacter* aPlayerCharacter = UGameplayStatics::GetPlayerCharacter(this->GetWorld(), 0);

	/*下のものはイベントグラフの中でいうCast toになります。*/
	ADartsActor* Darts = Cast<ADartsActor>(OtherActor);
	AkadaiProjectCharacter* ProjectCharacter = Cast<AkadaiProjectCharacter>(aPlayerCharacter);

	


	if (Darts != nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("HiiiiiiiiT"));
		
		/*if (ProjectCharacter != nullptr)
		{
			ProjectCharacter->GetScore();
		}*/

	}
}

// Called every frame
//void AtestActor::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

