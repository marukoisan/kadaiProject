// Fill out your copyright notice in the Description page of Project Settings.


#include "testConeActor.h"
#include "kadaiProjectCharacter.h" //�ǉ�
#include "DartsActor.h"            //�ǉ�
#include "Kismet/GameplayStatics.h"//�ǉ�

// Sets default values
AtestConeActor::AtestConeActor()
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
	UStaticMesh* Mesh = LoadObject<UStaticMesh>(NULL, TEXT("/Engine/BasicShapes/Cone"), NULL, LOAD_None, NULL);

	//StaticMesh��StaticMeshComponent�ɐݒ肷��
	StaticMesh->SetStaticMesh(Mesh);

	//StaticMeshComponent��RootComponent��Attach����
	StaticMesh->SetupAttachment(RootComponent);

	/*CollisionBox�̐ݒ�*/
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetBoxExtent(FVector(32.0f, 32.0f, 32.0f));//CollisionBox�̑傫�������߂�
	CollisionBox->SetCollisionProfileName("OverlapAllDynamic");//�A�N�^�[�̃R���W�����v���Z�b�g��ύX
	CollisionBox->SetupAttachment(RootComponent);

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AtestConeActor::OnOverlapBegin);//���������u�Ԃ̃I�[�o�[���b�v

	//�傫���ύX
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

	/*���̂��̂̓C�x���g�O���t�̒��ł���Cast to�ɂȂ�܂��B*/
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

