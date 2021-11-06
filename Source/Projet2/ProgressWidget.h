// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "ProgressWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJET2_API UProgressWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UProgressWidget(const FObjectInitializer& ObjectInitializer);
	
	bool bDisplayAlarmImage ;
	float fAlarmImageOpacity;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	virtual void NativeConstruct() override;

	void UpdateProgressWidget(int CurrentScore, int MaxScore);
	
	void DisplayDeathMessage();
	void DisplayVictoryMessage();
	void DisplayButtonEndGame();
	
	void DisplayAlarmImage();
	void HideAlarmImage();
	

	//virtual bool Initialize() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* PBProgressBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* RestartButton;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    UButton* MainMenuButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* AlarmImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* ImageVictory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* ImageDefeat;

	UFUNCTION()
	void StartButtonClicked();
	UFUNCTION()
	void MainMenuButtonClick();
};
