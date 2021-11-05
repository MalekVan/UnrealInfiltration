// Fill out your copyright notice in the Description page of Project Settings.
#include "GameHUD.h"

void AGameHUD::BeginPlay() {
	Super::BeginPlay();

	if (ProgressWidgetClass) {
		ProgressWidget = CreateWidget<UProgressWidget>(GetWorld(), ProgressWidgetClass);
		if (ProgressWidget) {
			ProgressWidget->AddToViewport();
		}
	}
<<<<<<< Updated upstream
	if (AlarmWidgetClass)
	{
		
	}
	if (InteractWidgetClass) {
		InteractWidget = CreateWidget<UProgressWidget>(GetWorld(), InteractWidgetClass);
		if (InteractWidget) {
			InteractWidget->AddToViewport();
		}
	}
=======
>>>>>>> Stashed changes
}

void AGameHUD::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}


void AGameHUD::UpdateProgressBar(int CurrentScore, int MaxScore) {
	if (ProgressWidget) {
		ProgressWidget->UpdateProgressWidget(CurrentScore, MaxScore);
	}
}

void AGameHUD::DisplayDeathMessage() {
	if(ProgressWidget)
	{
		ProgressWidget->DisplayDeathMessage();
	}
}

void AGameHUD::DisplayVictoryMessage() {
	if(ProgressWidget)
	{
		ProgressWidget->DisplayVictoryMessage();
	}
}