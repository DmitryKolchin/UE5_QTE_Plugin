// Fill out your copyright notice in the Description page of Project Settings.


#include "Utilities/QTEFunctionLibrary.h"

FCreateQTE::FCreateQTE(FLatentActionInfo& LatentActionInfo, EOutputPins& OutcomePins, UQTEWidgetBase* QTEWidget, const FDataTableRowHandle& QTEBoundKeyData) :
	LatentActionInfo( LatentActionInfo ),
	Output( OutcomePins ),
	QTEWidget( QTEWidget ),
	QTEBoundKeyData( QTEBoundKeyData )
{
	if ( IsValid( QTEWidget ) )
	{
		QTEWidget->OnQTEPassed.BindLambda( [this]()
		{
			State = EQTEState::Passed;
		} );

		QTEWidget->OnQTEFailed.BindLambda( [this]()
		{
			State = EQTEState::Failed;
		} );
	}
}

void FCreateQTE::UpdateOperation(FLatentResponse& Response)
{
	switch ( State )
	{
		case EQTEState::Created:
			State = EQTEState::Ongoing;
			Output = EOutputPins::Created;
			Response.TriggerLink( LatentActionInfo.ExecutionFunction, LatentActionInfo.Linkage, LatentActionInfo.CallbackTarget );
			break;
		case EQTEState::Failed:
			Output = EOutputPins::Failed;
			Response.FinishAndTriggerIf( true, LatentActionInfo.ExecutionFunction, LatentActionInfo.Linkage, LatentActionInfo.CallbackTarget );
			break;
		case EQTEState::Passed:
			Output = EOutputPins::Passed;
			Response.FinishAndTriggerIf( true, LatentActionInfo.ExecutionFunction, LatentActionInfo.Linkage, LatentActionInfo.CallbackTarget );
			break;
		case EQTEState::Ongoing:
		default:
			break;
	}
}

UQTEWidgetBase* UQTEFunctionLibrary::CreateQTE(UObject* WorldContextObject, FLatentActionInfo LatentInfo,
	EOutputPins& OutputPins, TSubclassOf<UQTEWidgetBase> QTEWidgetClass, int32 ZOrder, FDataTableRowHandle QTEBoundKeyData)
{
	UWorld* World = WorldContextObject->GetWorld();

	if ( !IsValid( World ) )
	{
		return nullptr;
	}

	FLatentActionManager& LatentActionManager = World->GetLatentActionManager();
	FCreateQTE* CreateQTE = LatentActionManager.FindExistingAction<FCreateQTE>( LatentInfo.CallbackTarget, LatentInfo.UUID );

	if ( CreateQTE == nullptr )
	{
		UQTEWidgetBase* QTEWidget = CreateWidget<UQTEWidgetBase>( World, QTEWidgetClass );
		QTEWidget->AddToViewport( ZOrder );

		if ( !IsValid( QTEWidget ) )
		{
			return nullptr;
		}

		CreateQTE = new FCreateQTE( LatentInfo, OutputPins, QTEWidget, QTEBoundKeyData );

		LatentActionManager.AddNewAction( LatentInfo.CallbackTarget, LatentInfo.UUID, CreateQTE );

		return QTEWidget;
	}


	return nullptr;
}
