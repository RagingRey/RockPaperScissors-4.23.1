// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 0.0f;
	CameraBoom->SocketOffset = FVector(150.0f, 500.0f, 0.0f);
	CameraBoom->bUsePawnControlRotation = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	Camera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (PlayerType == EPlayerType::Enemy)
	{
		UMaterialInstanceDynamic* EnemyMaterial;
		EnemyMaterial = this->GetMesh()->CreateAndSetMaterialInstanceDynamic(0);

		if (EnemyMaterial)
		{
			EnemyMaterial->SetVectorParameterValue("BodyColor", FLinearColor::Red);
		}

		CameraBoom->DestroyComponent(false);
		Camera->DestroyComponent(false);
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

ESelection APlayerCharacter::Play(int index)
{
	if (index == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Rock"));
		this->GetMesh()->PlayAnimation(RockAnimation, false);
		return ESelection::Rock;
	}
	else if (index == 1)
	{
		UE_LOG(LogTemp, Warning, TEXT("Paper"));
		this->GetMesh()->PlayAnimation(PaperAnimation, false);
		return ESelection::Paper;
	}
	else if (index == 2)
	{
		UE_LOG(LogTemp, Warning, TEXT("Scissors"));
		this->GetMesh()->PlayAnimation(ScissorsAnimation, false);
		return ESelection::Scissors;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Rock"));
		this->GetMesh()->PlayAnimation(RockAnimation, false);
		return ESelection::Rock;
	}
}