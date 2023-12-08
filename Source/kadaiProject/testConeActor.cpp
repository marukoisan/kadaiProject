// Fill out your copyright notice in the Description page of Project Settings.


#include "testConeActor.h"
#include "kadaiProjectCharacter.h" //追加
#include "DartsActor.h"            //追加
#include "Kismet/GameplayStatics.h"//追加

// Sets default values
AtestConeActor::AtestConeActor()
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
	UStaticMesh* Mesh = LoadObject<UStaticMesh>(NULL, TEXT("/Engine/BasicShapes/Cone"), NULL, LOAD_None, NULL);

	//StaticMeshをStaticMeshComponentに設定する
	StaticMesh->SetStaticMesh(Mesh);

	//StaticMeshComponentをRootComponentにAttachする
	StaticMesh->SetupAttachment(RootComponent);

	/*CollisionBoxの設定*/
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetBoxExtent(FVector(32.0f, 32.0f, 32.0f));//CollisionBoxの大きさを決める
	CollisionBox->SetCollisionProfileName("OverlapAllDynamic");//アクターのコリジョンプリセットを変更
	CollisionBox->SetupAttachment(RootComponent);

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AtestConeActor::OnOverlapBegin);//当たった瞬間のオーバーラップ

	//大きさ変更
	this->SetActorRelativeScale3D(FVector(0.25f, 0.25f, 0.25f));
	StaticMesh->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
	CollisionBox->SetRelativeScale3D(FVector(2.0f, 2.0f, 2.0f));

}

// Called when the game starts or when spawned
void AtestConeActor::BeginPlay()
{
	Super::BeginPlay();

}

void AtestConeActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, "Overlap Begin Function Called");
	ACharacter* aPlayerCharacter = UGameplayStatics::GetPlayerCharacter(this->GetWorld(), 0);//Get playerCharacter

	/*下のものはイベントグラフの中でいうCast toになります。*/
	ADartsActor* Darts = Cast<ADartsActor>(OtherActor);
	AkadaiProjectCharacter* ProjectCharacter = Cast<AkadaiProjectCharacter>(aPlayerCharacter);
	/******************************************************/



	if (Darts != nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("HiiiiiiiiT"));

		if (ProjectCharacter != nullptr)
		{
			ProjectCharacter->SetScore(variable);
			UE_LOG(LogTemp, Display, TEXT("100000000000"));
		}

	}
}



// Called every frame
//void AtestConeActor::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

