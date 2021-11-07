// Fill out your copyright notice in the Description page of Project Settings.


#include "ProgressWidget.h"
#include "Widgets/SWidget.h"
#include "Components/Button.h"

UProgressWidget::UProgressWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
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
	if (MainMenuButton2)
	{
		MainMenuButton2->OnClicked.AddDynamic(this, &UProgressWidget::MainMenuButtonClick);
		MainMenuButton2->SetVisibility(ESlateVisibility::Hidden);
	}
	if (ResumeButton)
	{
		ResumeButton->OnClicked.AddDynamic(this, &UProgressWidget::ResumeGame);
		ResumeButton->SetVisibility(ESlateVisibility::Hidden);
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

	HideAlarmImage();
	
	
}

void UProgressWidget::UpdateProgressWidget(int CurrentScore, int MaxScore) {
	double Value = (double)CurrentScore / (double)MaxScore;
	PBProgressBar->SetPercent(Value);
}

void UProgressWidget::DisplayDeathMessage()
{
	ImageDefeat->SetVisibility(ESlateVisibility::Visible);
	PBProgressBar->SetVisibility(ESlateVisibility::Hidden);
	ImageProgressBar->SetVisibility(ESlateVisibility::Hidden);
	DisplayButtonEndGame();
}

void UProgressWidget::DisplayVictoryMessage()
{
	ImageVictory->SetVisibility(ESlateVisibility::Visible);
	PBProgressBar->SetVisibility(ESlateVisibility::Hidden);
	ImageProgressBar->SetVisibility(ESlateVisibility::Hidden);
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
	AlarmImage->SetOpacity(0);
	fAlarmImageOpacity = 0;
}

void UProgressWidget::HideAlarmImage()
{
	bDisplayAlarmImage = false;
	AlarmImage->SetOpacity(0);
	fAlarmImageOpacity = 0;
}

void UProgressWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	if (bDisplayAlarmImage)
	{
		AlarmImage->SetOpacity(cos(GetWorld()->GetTimeSeconds() * 5)/2 + 0.5 );
	}
}

void UProgressWidget::StartButtonClicked()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

void UProgressWidget::MainMenuButtonClick()
{
	UGameplayStatics::OpenLevel(this, FName("MainMenu"), false);
}

void UProgressWidget::DisplayPauseMenu()
{
	MainMenuButton2->SetVisibility(ESlateVisibility::Visible);
	ResumeButton->SetVisibility(ESlateVisibility::Visible);
}

void UProgressWidget::ResumeGame()
{
	MainMenuButton2->SetVisibility(ESlateVisibility::Hidden);
	ResumeButton->SetVisibility(ESlateVisibility::Hidden);	
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
	GetWorld()->GetFirstPlayerController()->bEnableClickEvents = false;
	GetWorld()->GetFirstPlayerController()->bEnableMouseOverEvents = false;
	UGameplayStatics::SetGamePaused(GetWorld(), false);
}


