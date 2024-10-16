// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QTEWidgetBase.generated.h"

DECLARE_DELEGATE( FQTEWidgetDelegate );

/**
 * Base C++ class for QTE widgets
 */
UCLASS()
class EASYQTE_API UQTEWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	// Delegates
	FQTEWidgetDelegate OnQTEPassed;

	FQTEWidgetDelegate OnQTEFailed;

public:
	UFUNCTION( BlueprintCallable,  Category="QTE")
	void FinishQTE(bool bPassedSuccessfully);
};
