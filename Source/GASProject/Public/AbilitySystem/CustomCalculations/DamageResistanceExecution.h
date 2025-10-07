// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "DamageResistanceExecution.generated.h"

/**
 * 
 */
UCLASS()
class GASPROJECT_API UDamageResistanceExecution : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
public:
	UDamageResistanceExecution();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;

protected:
	
	UPROPERTY(EditDefaultsOnly, Category= "Damage")
	TArray<FGameplayEffectAttributeCaptureDefinition> DamageCaptureDefs;
	
	UPROPERTY(EditDefaultsOnly, Category= "Damage")
	TArray<FGameplayEffectAttributeCaptureDefinition> ResistanceCaptureDefs;
};
