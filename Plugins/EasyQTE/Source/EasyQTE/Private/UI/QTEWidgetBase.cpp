// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/QTEWidgetBase.h"

void UQTEWidgetBase::FinishQTE(bool bPassed)
{
	if ( bPassed && OnQTEPassed.IsBound() )
	{
		OnQTEPassed.Execute();
		return;
	}

	if ( !bPassed && OnQTEFailed.IsBound() )
	{
		OnQTEFailed.Execute();
		return;
	}
}
