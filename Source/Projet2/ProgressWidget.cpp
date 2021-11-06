// Fill out your copyright notice in the Description page of Project Settings.


#include "ProgressWidget.h"
#include "Widgets/SWidget.h"
#include "Components/Button.h"

UProgressWidget::UProgressWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
}

void UProgressWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	if (bDisplayAlarmImage)
	{
		AlarmImage->SetOpacity(cos(fAlarmImageOpacity));
		fAlarmImageOpacity += InDeltaTime;
	}
}


void UProgressWidget::NativeConstruct() {
	Super::NativeConstruct();
	if (RestartButton)
	{
		RestartButton->OnClicked.AddDynamic(this, &UProgressWidget::StartButtonClicked);
		RestartButton->SetVisibility(ESlateVisibility::Hidden);
	}
	if (MainMenuButton)
	{
		MainMenuButton->OnClicked.AddDynamic(this, &UProgressWidget::MainMenuButtonClick);
		MainMenuButton->SetVisibility(ESlateVisibility::Hidden);
	}
	if (AlarmImage)
	{
		DisplayAlarmImage();
	}

	if (ImageDefeat)
	{
		ImageDefeat->SetVisibility(ESlateVisibility::Hidden);
	}
	if (ImageVictory)
	{
		ImageVictory->SetVisibility(ESlateVisibility::Hidden);
	}

	bDisplayAlarmImage = false;
	
	UE_LOG(LogTemp, Warning, TEXT("AlarmImage %s"), AlarmImage ? TEXT("True") : TEXT("False"));
}

void UProgressWidget::UpdateProgressWidget(int CurrentScore, int MaxScore) {
	double Value = (double)CurrentScore / (double)MaxScore;
	PBProgressBar->SetPercent(Value);
}

void UProgressWidget::DisplayDeathMessage()
{
	ImageDefeat->SetVisibility(ESlateVisibility::Visible);
	DisplayButtonEndGame();
}

void UProgressWidget::DisplayVictoryMessage()
{
	ImageVictory->SetVisibility(ESlateVisibility::Visible);
	DisplayButtonEndGame();
}

void UProgressWidget::DisplayButtonEndGame()
{
	if (RestartButton)
	{
		RestartButton->SetVisibility(ESlateVisibility::Visible);
	}
	if (MainMenuButton)
	{
		MainMenuButton->SetVisibility(ESlateVisibility::Visible);
	}
	if (PBProgressBar)
	{
		PBProgressBar->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UProgressWidget::DisplayAlarmImage()
{
	bDisplayAlarmImage = true;
	fAlarmImageOpacity = 0;
}

void UProgressWidget::HideAlarmImage()
{
	bDisplayAlarmImage = false;
	fAlarmImageOpacity = 0;
}

void UProgressWidget::StartButtonClicked()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

void UProgressWidget::MainMenuButtonClick()
{
	UGameplayStatics::OpenLevel(this, FName("MainMenu"), false);
}


