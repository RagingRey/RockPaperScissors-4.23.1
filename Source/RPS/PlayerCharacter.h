// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "PlayerCharacter.generated.h"

UENUM(BlueprintType)
enum class EPlayerType : uint8
{
	Player,
	Enemy
};

UENUM(BlueprintType)
enum class ESelection : uint8
{
	Rock,
	Paper,
	Scissors
};

UCLASS()
class RPS_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
		USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
		UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EPlayerType PlayerType = EPlayerType::Player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimationAsset* RockAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimationAsset* PaperAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimationAsset* ScissorsAnimation;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
		ESelection Play(int index);
};
