// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/AuraUserWidget.h"

void UAuraUserWidget::SetWidgetController(UObject* widget_controller)
{
	WidgetController = widget_controller;
	WidgetControllerSet();
}

void UAuraUserWidget::WidgetControllerSet()
{
}
