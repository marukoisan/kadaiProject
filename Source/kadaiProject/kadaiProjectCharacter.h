// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once


#include "InputAction.h"                        // 追加
#include "InputActionValue.h"                   // 追加
#include "EnhancedInputComponent.h"             // 追加
#include "EnhancedInputSubsystems.h"            // 追加
#include "DartsActor.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/ArrowComponent.h"			// 追加
#include "kadaiProjectCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UAnimMontage;
class USoundBase;

UCLASS(config=Game)
class AkadaiProjectCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	

public:
	AkadaiProjectCharacter();

protected:
	virtual void BeginPlay();

public:
		
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** Bool for AnimBP to switch to another animation set */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool bHasRifle;

	/** Setter to set the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetHasRifle(bool bNewHasRifle);

	/** Getter for the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool GetHasRifle();
		
	//プレイヤーの前にダーツを出すためのArrowComponent
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= Arrow)
		TObjectPtr<UArrowComponent> Arrow1P;//Arrow変数を作成
	
	//ScoreのGet関数
	int GetScore();

	//ScoreのSet関数
	int SetScore(int32 testvalue);

	int ProductSetScore(int32 value, int32 product);

	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/* MappingContext */
	//UPROPERTY(EditAnywhere, Category = Input)
	//	class UInputMappingContext* DefaultMappingContext;

	/* Action Input */
	UPROPERTY(EditAnywhere, Category = Input)
		class UInputAction* ActionInput;

	/* Axis Input */
	UPROPERTY(EditAnywhere, Category = Input)
		class UInputAction* AxisInput;

	/*  Firing Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPribateAccess = "true"))
		class UInputAction* FiringAction;

	/***********/

	/* Characterのコントロール */
	void ControlCharacter(const FInputActionValue& Value);
	/***********/


	

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

private:
	//Input設定
	void SetupInput();

	//Input Eventイベントハンドラー関数
	void PressedB();//Bキーを押したら
	//void ReleasedB();//Bキーを離したら

		//メンバ変数
	ADartsActor* something;
	
	//合計の点数を持っている
	int32 testscore = 100;

	
	const float Duration = 10.0f;

	const FLinearColor TextColor = FLinearColor(0.0, 0.66, 1.0);

};

