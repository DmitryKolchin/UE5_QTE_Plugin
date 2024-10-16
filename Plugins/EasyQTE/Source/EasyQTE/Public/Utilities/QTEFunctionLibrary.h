// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UI/QTEWidgetBase.h"
#include "QTEFunctionLibrary.generated.h"

class UQTEWidgetBase;

UENUM()
enum class EQTEState : uint8
{
	Created,
	Ongoing,
	Passed,
	Failed
};

UENUM()
enum class EOutputPins : uint8
{
	Created,
	Passed,
	Failed
};

class FCreateQTE : public FPendingLatentAction
{
private:
	// Current QTE state
	EQTEState State = EQTEState::Created;

	// Bound key data
	FDataTableRowHandle QTEBoundKeyData;

	// Created widget reference
	UQTEWidgetBase* QTEWidget;

public:
	// Latent action info
	FLatentActionInfo LatentActionInfo;
	EOutputPins& Output;

	FCreateQTE(FLatentActionInfo& LatentActionInfo, EOutputPins& OutcomePins, UQTEWidgetBase* QTEWidget, const FDataTableRowHandle& QTEBoundKeyData);

	virtual void UpdateOperation(FLatentResponse& Response) override;
};

/**
 * 
 */
UCLASS()
class EASYQTE_API UQTEFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION( BlueprintCallable, meta=(WorldContext="WorldContextObject", Latent, LatentInfo="LatentInfo", ExpandEnumAsExecs="OutputPins"), Category="QTE" )
	static UPARAM( DisplayName = "QTE Widget" ) UQTEWidgetBase* CreateQTE(UObject* WorldContextObject,
	                                                                      FLatentActionInfo LatentInfo,
	                                                                      EOutputPins& OutputPins,
	                                                                      TSubclassOf<UQTEWidgetBase>
	                                                                      QTEWidgetClass,
	                                                                      int32 ZOrder = 0,
	                                                                      FDataTableRowHandle QTEBoundKeyData = FDataTableRowHandle());
};
