// Copyright Epic Games, Inc. All Rights Reserved.

#include "kadaiProjectCharacter.h"
#include "kadaiProjectProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h" //�ǉ�


//////////////////////////////////////////////////////////////////////////
// AkadaiProjectCharacter

AkadaiProjectCharacter::AkadaiProjectCharacter()
{
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
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

}

void AkadaiProjectCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

}

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
	FString aAssetPath = "/Script/CoreUObject.Class'/Script/kadaiProject.DartsActor'";

	//�A�Z�b�g��ǂݍ���(����)
	TSubclassOf<AActor>aActorClass = TSoftClassPtr<AActor>
		(FSoftObjectPath(*aAssetPath)).LoadSynchronous();

	//�ʒu���
	FTransform aTransForm;
	
	if (aActorClass != nullptr) 
	{
		//�X�|�[��
		TObjectPtr<AActor> aActor = GetWorld()->SpawnActor<AActor>(aActorClass, aTransForm);
	}

}