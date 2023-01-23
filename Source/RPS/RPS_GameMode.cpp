// Fill out your copyright notice in the Description page of Project Settings.


#include "RPS_GameMode.h"

#include "TimerManager.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

ARPS_GameMode::ARPS_GameMode()
{
	PlayerScore = 0;
	EnemyScore = 0;
}

void ARPS_GameMode::BeginPlay()
{
	if (Enemy_Class)
	{
		Enemy = Cast<APlayerCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), Enemy_Class));
	}

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->bShowMouseCursor = true;
	PlayerController->SetInputMode(FInputModeUIOnly());
}

int ARPS_GameMode::GetPlayerScore()
{
	return PlayerScore;
}

int ARPS_GameMode::GetEnemyScore()
{
	return EnemyScore;
}

void ARPS_GameMode::EnemyPlay()
{
	if (Enemy)
	{
		EnemySelection = Enemy->Play(FMath::RandRange(0, 2));
	}
}

void ARPS_GameMode::GameResult(ESelection PlayerSelection)
{
	if (PlayerSelection == ESelection::Rock && EnemySelection == ESelection::Paper)
	{
		EnemyScore++;
		CurrentResult = "You chose Rock, Enemy chose Paper";
		Conclusion = "Paper covers Rock!";
		UGameplayStatics::PlaySound2D(GetWorld(), Paper_Sound);
	}
	else if (PlayerSelection == ESelection::Rock && EnemySelection == ESelection::Scissors)
	{
		PlayerScore++;
		CurrentResult = "You chose Rock, Enemy chose Scissors";
		Conclusion = "Rock Breaks Scissors!";
		UGameplayStatics::PlaySound2D(GetWorld(), Rock_Sound);
	}
	else if (PlayerSelection == ESelection::Paper && EnemySelection == ESelection::Rock)
	{
		PlayerScore++;
		CurrentResult = "You chose Paper, Enemy chose Rock";
		Conclusion = "Paper covers Rock!";
		UGameplayStatics::PlaySound2D(GetWorld(), Paper_Sound);
	}
	else if (PlayerSelection == ESelection::Paper && EnemySelection == ESelection::Scissors)
	{
		EnemyScore++;
		CurrentResult = "You chose Paper, Enemy chose Scissors";
		Conclusion = "Scissors cuts Paper!";
		UGameplayStatics::PlaySound2D(GetWorld(), Scissors_Sound);
	}
	else if (PlayerSelection == ESelection::Scissors && EnemySelection == ESelection::Rock)
	{
		EnemyScore++;
		CurrentResult = "You chose Scissors, Enemy chose Rock";
		Conclusion = "Rock Breaks Scissors!";
		UGameplayStatics::PlaySound2D(GetWorld(), Rock_Sound);
	}
	else if (PlayerSelection == ESelection::Scissors && EnemySelection == ESelection::Paper)
	{
		PlayerScore++;
		CurrentResult = "You chose Scissors, Enemy chose Paper";
		Conclusion = "Scissors cuts Paper!";
		UGameplayStatics::PlaySound2D(GetWorld(), Scissors_Sound);
	}
	else if (PlayerSelection == EnemySelection)
	{
		CurrentResult = "You and the enemy chose the same thing.";
		Conclusion = "";
	}


	if (PlayerScore == 3 || EnemyScore == 3)
	{
		FinalResult = (PlayerScore > EnemyScore) ? "You Win!" : "You Lose!";

		if(FinalResult.Equals("You Win!"))
		{
			UGameplayStatics::PlaySound2D(GetWorld(), Win_Sound);
		}
		else
		{
			UGameplayStatics::PlaySound2D(GetWorld(), Lose_Sound);
		}

		if (GameStateWidget_Class)
		{
			GameStateWidget = CreateWidget(GetWorld(), GameStateWidget_Class);
			GameStateWidget->AddToViewport();
		}

		GetWorldTimerManager().SetTimer(Restart_Handle, this, &ARPS_GameMode::RestartLevel, 3.5f, false);
	}
}

void ARPS_GameMode::RestartLevel() const
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}
