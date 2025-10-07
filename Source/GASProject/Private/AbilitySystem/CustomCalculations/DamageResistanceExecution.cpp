// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/CustomCalculations/DamageResistanceExecution.h"

#include "AbilitySystem/AttributeSets/GasBaseAttributeSet.h"

UDamageResistanceExecution::UDamageResistanceExecution()
{
	// Danos
	DamageCaptureDefs.Add(FGameplayEffectAttributeCaptureDefinition(UGasBaseAttributeSet::GetAttackAttribute(), EGameplayEffectAttributeCaptureSource::Source, true));
	DamageCaptureDefs.Add(FGameplayEffectAttributeCaptureDefinition(UGasBaseAttributeSet::GetPhysicalDamageAttribute(), EGameplayEffectAttributeCaptureSource::Source, true));
	DamageCaptureDefs.Add(FGameplayEffectAttributeCaptureDefinition(UGasBaseAttributeSet::GetFireDamageAttribute(), EGameplayEffectAttributeCaptureSource::Source, true));
	DamageCaptureDefs.Add(FGameplayEffectAttributeCaptureDefinition(UGasBaseAttributeSet::GetWaterDamageAttribute(), EGameplayEffectAttributeCaptureSource::Source, true));
	DamageCaptureDefs.Add(FGameplayEffectAttributeCaptureDefinition(UGasBaseAttributeSet::GetWindDamageAttribute(), EGameplayEffectAttributeCaptureSource::Source, true));
	DamageCaptureDefs.Add(FGameplayEffectAttributeCaptureDefinition(UGasBaseAttributeSet::GetEarthDamageAttribute(), EGameplayEffectAttributeCaptureSource::Source, true));
	DamageCaptureDefs.Add(FGameplayEffectAttributeCaptureDefinition(UGasBaseAttributeSet::GetLightningDamageAttribute(), EGameplayEffectAttributeCaptureSource::Source, true));
	DamageCaptureDefs.Add(FGameplayEffectAttributeCaptureDefinition(UGasBaseAttributeSet::GetPoisonDamageAttribute(), EGameplayEffectAttributeCaptureSource::Source, true));
	DamageCaptureDefs.Add(FGameplayEffectAttributeCaptureDefinition(UGasBaseAttributeSet::GetParalysisDamageAttribute(), EGameplayEffectAttributeCaptureSource::Source, true));
	DamageCaptureDefs.Add(FGameplayEffectAttributeCaptureDefinition(UGasBaseAttributeSet::GetYokaiRealmDamageAttribute(), EGameplayEffectAttributeCaptureSource::Source, true));
	
	// Resistencias
	ResistanceCaptureDefs.Add(FGameplayEffectAttributeCaptureDefinition(UGasBaseAttributeSet::GetGuardBreakResistanceAttribute(), EGameplayEffectAttributeCaptureSource::Target, true));
	ResistanceCaptureDefs.Add(FGameplayEffectAttributeCaptureDefinition(UGasBaseAttributeSet::GetFireResistanceAttribute(), EGameplayEffectAttributeCaptureSource::Target, true));
	ResistanceCaptureDefs.Add(FGameplayEffectAttributeCaptureDefinition(UGasBaseAttributeSet::GetWaterResistanceAttribute(), EGameplayEffectAttributeCaptureSource::Target, true));
	ResistanceCaptureDefs.Add(FGameplayEffectAttributeCaptureDefinition(UGasBaseAttributeSet::GetWindResistanceAttribute(), EGameplayEffectAttributeCaptureSource::Target, true));
	ResistanceCaptureDefs.Add(FGameplayEffectAttributeCaptureDefinition(UGasBaseAttributeSet::GetEarthResistanceAttribute(), EGameplayEffectAttributeCaptureSource::Target, true));
	ResistanceCaptureDefs.Add(FGameplayEffectAttributeCaptureDefinition(UGasBaseAttributeSet::GetLightningResistanceAttribute(), EGameplayEffectAttributeCaptureSource::Target, true));
	ResistanceCaptureDefs.Add(FGameplayEffectAttributeCaptureDefinition(UGasBaseAttributeSet::GetPoisonResistanceAttribute(), EGameplayEffectAttributeCaptureSource::Target, true));
	ResistanceCaptureDefs.Add(FGameplayEffectAttributeCaptureDefinition(UGasBaseAttributeSet::GetParalysisResistanceAttribute(), EGameplayEffectAttributeCaptureSource::Target, true));
	ResistanceCaptureDefs.Add(FGameplayEffectAttributeCaptureDefinition(UGasBaseAttributeSet::GetYokaiRealmResistanceAttribute(), EGameplayEffectAttributeCaptureSource::Target, true));

	for (const auto& Def : DamageCaptureDefs)
	{
		RelevantAttributesToCapture.Add(Def);
	}
	for (const auto& Def : ResistanceCaptureDefs)
	{
		RelevantAttributesToCapture.Add(Def);
	}
}

void UDamageResistanceExecution::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	
	UAbilitySystemComponent* TargetAbilitySystemComponent = ExecutionParams.GetTargetAbilitySystemComponent();
	UAbilitySystemComponent* SourceAbilitySystemComponent = ExecutionParams.GetSourceAbilitySystemComponent();

	AActor* SourceActor = SourceAbilitySystemComponent ? SourceAbilitySystemComponent->GetAvatarActor() : nullptr;
	AActor* TargetActor = TargetAbilitySystemComponent ? TargetAbilitySystemComponent->GetAvatarActor() : nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedSourceTags.GetAggregatedTags();
	
	FAggregatorEvaluateParameters EvalParams;
	EvalParams.SourceTags = SourceTags;
	EvalParams.TargetTags = TargetTags;
 
	float TotalDamage = 0.f;
	for (const FGameplayEffectAttributeCaptureDefinition& DamageDef : DamageCaptureDefs)
	{
		float DamageValue = 0.f;
		if (ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageDef, EvalParams, DamageValue))
		{
			TotalDamage += DamageValue;
		}
	}
 
	float TotalResistanceMultiplier = 1.f;
	for (const FGameplayEffectAttributeCaptureDefinition& ResistanceDef : ResistanceCaptureDefs)
	{
		float ResistanceValue = 0.f;
		if (ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(ResistanceDef, EvalParams, ResistanceValue))
		{
			float ResistanceFraction = FMath::Clamp(ResistanceValue / 100.f, 0.f, 0.95f);
			TotalResistanceMultiplier *= (1.f - ResistanceFraction);
		}
	}
 
	float FinalDamage = TotalDamage * TotalResistanceMultiplier;
	FinalDamage = FMath::Max(FinalDamage, 0.f);
 
	if (FinalDamage > 0.f)
	{
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(
			UGasBaseAttributeSet::GetLifeAttribute(), EGameplayModOp::Additive, -FinalDamage));
	}
 
#if !UE_BUILD_SHIPPING
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Cyan, FString::Printf( TEXT("DamageResistanceExecution: TotalDamage=%.2f, ResistanceMultiplier=%.2f, FinalDamage=%.2f"),
		   TotalDamage, TotalResistanceMultiplier, FinalDamage));
	}
#endif
}
