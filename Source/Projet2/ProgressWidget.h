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
	bool bDisplayAlarmImage;
	float fAlarmImageOpacity;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
public:
	UProgressWidget(const FObjectInitializer& ObjectInitializer);

	
	virtual void NativeConstruct() override;

	void UpdateProgressWidget(int CurrentScore, int MaxScore);
	
	void DisplayDeathMessage();
	void DisplayVictoryMessage();
	void DisplayButtonEndGame();
	
	void DisplayAlarmImage();
	void HideAlarmImage();
	

	//virtual bool Initialize() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TXTDeathMessage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TXTVictoryMessage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* PBProgressBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* RestartButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BinWidget))
	UImage* AlarmImage;

	UFUNCTION()
	void StartButtonClicked();
};
