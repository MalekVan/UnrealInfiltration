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
	if(TXTDeathMessage)
	{
		TXTDeathMessage->SetText(FText::FromString("Game Over"));
		TXTDeathMessage->SetVisibility(ESlateVisibility::Hidden);
	}
	if(TXTVictoryMessage)
	{
		TXTVictoryMessage->SetText(FText::FromString("Victory !"));
		TXTVictoryMessage->SetVisibility(ESlateVisibility::Hidden);
	}
	if (RestartButton)
	{
		RestartButton->OnClicked.AddDynamic(this, &UProgressWidget::StartButtonClicked);
		RestartButton->SetVisibility(ESlateVisibility::Hidden);
		RestartButton->Visibility = ESlateVisibility::Hidden;
	}
	if (AlarmImage)
	{
		DisplayAlarmImage();
	}
	UE_LOG(LogTemp, Warning, TEXT("AlarmImage %s"), AlarmImage ? TEXT("True") : TEXT("False"));
}

void UProgressWidget::UpdateProgressWidget(int CurrentScore, int MaxScore) {
	double Value = (double)CurrentScore / (double)MaxScore;
	PBProgressBar->SetPercent(Value);
}

void UProgressWidget::DisplayDeathMessage()
{
	if(TXTDeathMessage)
	{		
		TXTDeathMessage->SetVisibility(ESlateVisibility::Visible);
		DisplayButtonEndGame();
	}
}

void UProgressWidget::DisplayVictoryMessage()
{
	if(TXTVictoryMessage)
	{		
		TXTVictoryMessage->SetVisibility(ESlateVisibility::Visible);
		DisplayButtonEndGame();
	}
}

void UProgressWidget::DisplayButtonEndGame()
{
	if (RestartButton)
	{
		RestartButton->SetVisibility(ESlateVisibility::Visible);
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


