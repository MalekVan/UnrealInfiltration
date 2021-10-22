// Fill out your copyright notice in the Description page of Project Settings.


#include "ProgressWidget.h"
#include "Widgets/SWidget.h"
#include "Components/Button.h"

UProgressWidget::UProgressWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
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

void UProgressWidget::StartButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("Our button is working!"));
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}
