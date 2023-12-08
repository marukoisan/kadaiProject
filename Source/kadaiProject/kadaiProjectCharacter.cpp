// Copyright Epic Games, Inc. All Rights Reserved.

#include "kadaiProjectCharacter.h"
#include "kadaiProjectProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h" //追加
#include "Components/SceneComponent.h"    //追加
#include "Kismet/KismetMathLibrary.h" // 追加




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

	//Arrowを追加する
	Arrow1P = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrowttttt"));
	Arrow1P->SetupAttachment(Mesh1P);//アタッチする処理

	//Arrowコンポーネントの場所を変更する処理
	Arrow1P->SetRelativeLocation(FVector(90.0f, 0.0f, 130.0f));
	Arrow1P->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	//Arrow1P->AddLocalRotation(FQuat(FVector(0,0,0), UE_PI / 2));
	//Arrow1P->SetWorldRotation(FRotator(0.0f, 0.0f, 90.0f));

	/*************/

	//Input Mapping Contextを読み込み
	//DefaultMappingContext = LoadObject<UInputMappingContext>(NULL, TEXT("/Game/FirstPerson/Actions/IM_Controls"), NULL, LOAD_None, NULL);

	//Input Actionの「IA_Look」を読み込む
	LookAction = LoadObject<UInputAction>(NULL, TEXT("/Game/FirstPerson/Actions/IA_Look"), NULL, LOAD_None, NULL);

	//Input Actionの「IA_Firing」を読み込む
	FiringAction = LoadObject<UInputAction>(NULL, TEXT("/Game/FirstPerson/Actions/IA_Firing"), NULL, LOAD_None, NULL);
}

void AkadaiProjectCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Input設定を行う
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
//	//PlayerControllerを取得する
//	APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
//
//	//入力を有効にする
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

void AkadaiProjectCharacter::SetupInput()//キー入力のセットアップ
{
	//入力を有効にする
	EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	//BキーのPressedとReleasedをバインドする
	InputComponent->BindKey(EKeys::B, IE_Pressed, this, &AkadaiProjectCharacter::PressedB);
	//InputComponent->BindKey(EKeys::B, IE_Released, this, &AkadaiProjectCharacter::ReleasedB);

}

void AkadaiProjectCharacter::PressedB()//キーが入力された時の結果
{
	//アクターのパス。BP_Actorを生成したい場合後ろに .BP_Actor_C を追加する
	//FString aAssetPath = "/Script/kadaiProject.DartsActor";

	//アセットを読み込む(同期)
	//TSubclassOf<AActor>aActorClass = TSoftClassPtr<AActor>
		//(FSoftObjectPath(*aAssetPath)).LoadSynchronous();

	//位置情報
	//FTransform aTransForm;
	//Arrow1PのWorldTransformを取得する
	//const FTransform& WorldTransform = Arrow1P->GetComponentTransform();
	FVector ActorLocation = Arrow1P->GetComponentLocation();//ArrowComponentのLocationの情報を持った変数を作成する
	FRotator ActorRotator = Arrow1P->GetComponentRotation();//ArrowComponentのRotationの情報を持った変数を作成する

	//スポーンさせるための処理
	something = GetWorld()->SpawnActor<ADartsActor>(ActorLocation, ActorRotator);
	
	//スポーンさせた後にスポーンしたアクターに力を加える処理
	//something->AddActorLocalOffset

	//if (aActorClass != nullptr) 
	//{
	//	//スポーン
	//	//TObjectPtr<AActor> aActor = GetWorld()->SpawnActor<AActor>(aActorClass, aTransForm);
	//	AActor* aActor = GetWorld()->SpawnActor<AActor>(aActorClass); // スポーン処理

	//	
	//}

}

//Get関数
int AkadaiProjectCharacter::GetScore()
{
	return testscore;
}

//Set関数使うときに引きたい数字を入れる
int AkadaiProjectCharacter::SetScore(int32 testvalue)
{
	testscore = testscore - testvalue;
	return testscore;

}


//Event tickの呼び出し
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
