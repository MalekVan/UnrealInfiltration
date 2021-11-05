// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ProgressWidget.h"
#include "Components/WidgetComponent.h"
#include "GameHUD.generated.h"

/**
 * 
 */
UCLASS()
class PROJET2_API AGameHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void UpdateProgressBar(int CurrentScore, int MaxScore);

	UFUNCTION()
	void DisplayDeathMessage();
	
	UFUNCTION()
	void DisplayVictoryMessage();

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> ProgressWidgetClass;
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> AlarmWidgetClass;

	UProgressWidget* ProgressWidget;
};
