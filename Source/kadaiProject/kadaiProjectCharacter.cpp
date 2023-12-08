// Copyright Epic Games, Inc. All Rights Reserved.

#include "kadaiProjectCharacter.h"
#include "kadaiProjectProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h" //�ǉ�
#include "Components/SceneComponent.h"    //�ǉ�
#include "Kismet/KismetMathLibrary.h" // �ǉ�




//////////////////////////////////////////////////////////////////////////
// AkadaiProjectCharacter

AkadaiProjectCharacter::AkadaiProjectCharacter()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Character doesnt have a rifle at start
	bHasRifle = false;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.0f, -150.f));
	

	/*************/

	//Arrow��ǉ�����
	Arrow1P = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrowttttt"));
	Arrow1P->SetupAttachment(Mesh1P);//�A�^�b�`���鏈��

	//Arrow�R���|�[�l���g�̏ꏊ��ύX���鏈��
	Arrow1P->SetRelativeLocation(FVector(90.0f, 0.0f, 130.0f));
	Arrow1P->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	//Arrow1P->AddLocalRotation(FQuat(FVector(0,0,0), UE_PI / 2));
	//Arrow1P->SetWorldRotation(FRotator(0.0f, 0.0f, 90.0f));

	/*************/

	//Input Mapping Context��ǂݍ���
	//DefaultMappingContext = LoadObject<UInputMappingContext>(NULL, TEXT("/Game/FirstPerson/Actions/IM_Controls"), NULL, LOAD_None, NULL);

	//Input Action�́uIA_Look�v��ǂݍ���
	LookAction = LoadObject<UInputAction>(NULL, TEXT("/Game/FirstPerson/Actions/IA_Look"), NULL, LOAD_None, NULL);

	//Input Action�́uIA_Firing�v��ǂݍ���
	FiringAction = LoadObject<UInputAction>(NULL, TEXT("/Game/FirstPerson/Actions/IA_Firing"), NULL, LOAD_None, NULL);
}

void AkadaiProjectCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Input�ݒ���s��
	SetupInput();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

}

//void AkadaiProjectCharacter::SetupInput()
//{
//	//PlayerController���擾����
//	APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
//
//	//���͂�L���ɂ���
//	EnableInput(controller);
//}


//////////////////////////////////////////////////////////////////////////// Input

void AkadaiProjectCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AkadaiProjectCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AkadaiProjectCharacter::Look);
	}
}


void AkadaiProjectCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AkadaiProjectCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AkadaiProjectCharacter::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

bool AkadaiProjectCharacter::GetHasRifle()
{
	return bHasRifle;
}

void AkadaiProjectCharacter::SetupInput()//�L�[���͂̃Z�b�g�A�b�v
{
	//���͂�L���ɂ���
	EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	//B�L�[��Pressed��Released���o�C���h����
	InputComponent->BindKey(EKeys::B, IE_Pressed, this, &AkadaiProjectCharacter::PressedB);
	//InputComponent->BindKey(EKeys::B, IE_Released, this, &AkadaiProjectCharacter::ReleasedB);

}

void AkadaiProjectCharacter::PressedB()//�L�[�����͂��ꂽ���̌���
{
	//�A�N�^�[�̃p�X�BBP_Actor�𐶐��������ꍇ���� .BP_Actor_C ��ǉ�����
	//FString aAssetPath = "/Script/kadaiProject.DartsActor";

	//�A�Z�b�g��ǂݍ���(����)
	//TSubclassOf<AActor>aActorClass = TSoftClassPtr<AActor>
		//(FSoftObjectPath(*aAssetPath)).LoadSynchronous();

	//�ʒu���
	//FTransform aTransForm;
	//Arrow1P��WorldTransform���擾����
	//const FTransform& WorldTransform = Arrow1P->GetComponentTransform();
	FVector ActorLocation = Arrow1P->GetComponentLocation();//ArrowComponent��Location�̏����������ϐ����쐬����
	FRotator ActorRotator = Arrow1P->GetComponentRotation();//ArrowComponent��Rotation�̏����������ϐ����쐬����

	//�X�|�[�������邽�߂̏���
	something = GetWorld()->SpawnActor<ADartsActor>(ActorLocation, ActorRotator);
	
	//�X�|�[����������ɃX�|�[�������A�N�^�[�ɗ͂������鏈��
	//something->AddActorLocalOffset

	//if (aActorClass != nullptr) 
	//{
	//	//�X�|�[��
	//	//TObjectPtr<AActor> aActor = GetWorld()->SpawnActor<AActor>(aActorClass, aTransForm);
	//	AActor* aActor = GetWorld()->SpawnActor<AActor>(aActorClass); // �X�|�[������

	//	
	//}

}

//Get�֐�
int AkadaiProjectCharacter::GetScore()
{
	return testscore;
}

//Set�֐��g���Ƃ��Ɉ�����������������
int AkadaiProjectCharacter::SetScore(int32 testvalue)
{
	testscore = testscore - testvalue;
	return testscore;

}


//Event tick�̌Ăяo��
void AkadaiProjectCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (testscore == 0)
	{
		UKismetSystemLibrary::PrintString(
			this
			, FString::FromInt(testscore)
			, true
			, true
			, TextColor
			, Duration);
	}
	else 
	{
		UKismetSystemLibrary::PrintString(
			this
			, FString::FromInt(testscore)
			, true
			, true
			, TextColor
			, Duration);
	}
}
