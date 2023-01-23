// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacter.h"
#include "GameFramework/GameMode.h"
#include "RPS_GameMode.generated.h"

UCLASS()
class RPS_API ARPS_GameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ARPS_GameMode();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int PlayerScore;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int EnemyScore;

	UPROPERTY(EditAnywhere)
		TSubclassOf<APlayerCharacter> Enemy_Class;
	APlayerCharacter* Enemy;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FString CurrentResult;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FString Conclusion;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FString FinalResult;

	UFUNCTION(BlueprintCallable)
		int GetPlayerScore();

	UFUNCTION(BlueprintCallable)
		int GetEnemyScore();

	FTimerHandle Restart_Handle;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> GameStateWidget_Class;
	UUserWidget* GameStateWidget;

	ESelection EnemySelection;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		USoundBase* Rock_Sound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		USoundBase* Paper_Sound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		USoundBase* Scissors_Sound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		USoundBase* Win_Sound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		USoundBase* Lose_Sound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
		void EnemyPlay();

	UFUNCTION(BlueprintCallable)
		void GameResult(ESelection PlayerSelection);

	void RestartLevel() const;
};
