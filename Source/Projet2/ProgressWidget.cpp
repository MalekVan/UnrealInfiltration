// Fill out your copyright notice in the Description page of Project Settings.


#include "ProgressWidget.h"

UProgressWidget::UProgressWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
}

void UProgressWidget::NativeConstruct() {
	Super::NativeConstruct();
	if(TXTDeathMessage)
	{
		TXTDeathMessage->SetText(FText::FromString("You are dead..."));
		TXTDeathMessage->SetVisibility(ESlateVisibility::Hidden);
	}
	if(TXTVictoryMessage)
	{
		TXTVictoryMessage->SetText(FText::FromString("You survived !"));
		TXTVictoryMessage->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UProgressWidget::UpdateProgressWidget(int CurrentScore, int MaxScore) {
	double value = (double)CurrentScore / (double)MaxScore;
	PBProgressBar->SetPercent(value);
}

void UProgressWidget::DisplayDeathMessage()
{
	if(TXTDeathMessage)
	{		
		TXTDeathMessage->SetVisibility(ESlateVisibility::Visible);
	}
}

void UProgressWidget::DisplayVictoryMessage()
{
	if(TXTVictoryMessage)
	{		
		TXTVictoryMessage->SetVisibility(ESlateVisibility::Visible);
	}
}