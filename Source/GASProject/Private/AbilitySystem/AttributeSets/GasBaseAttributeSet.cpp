// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AttributeSets/GasBaseAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "Characters/GasCharacter.h"
#include "Net/UnrealNetwork.h"

UGasBaseAttributeSet::UGasBaseAttributeSet()
{

	Level = 1.f;
	AttributePoints = 0.f;
	PointsPerLevel = 3.f;

	// Valores base de atributos
	BaseBody = 10.f;
	BaseHeart = 10.f;
	BaseStrength = 10.f;
	BaseStamina = 10.f;
	BaseSkill = 10.f;
	BaseDexterity = 10.f;
	BaseMagic = 10.f;
	BaseSpirit = 10.f;

	// Atributos base
	Body = 10.f;
	Heart = 10.f;
	Stamina = 10.f;
	Strength = 10.f;
	Skill = 10.f;
	Dexterity = 10.f;
	Magic = 10.f;
	Spirit = 10.f;

	// Atributos derivados
	LifeMax = 100.f;
	Life = 100.f;
	KiMax = 50.f;
	Ki = 50.f;
	Attack = 10.f;
	Defense = 5.f;
	PhysicalBlock = 2.f;
	AttackRating = 10.f;

	// Atributos de dano
	PhysicalDamage = 10.f;
	FireDamage = 5.f;
	WaterDamage = 5.f;
	WindDamage = 3.f;
	EarthDamage = 4.f;
	LightningDamage = 1.f;
	PoisonDamage = 3.f;
	ParalysisDamage = 2.f;
	YokaiRealmDamage = 1.f;	

	// Resistencias
	GuardBreakResistance = 1.f;
	FireResistance = 1.f;
	WaterResistance = 1.f;
	WindResistance = 1.f;
	EarthResistance = 1.f;
	LightningResistance = 1.f;
	PoisonResistance = 1.f;
	ParalysisResistance = 1.f;
	YokaiRealmResistance = 1.f;

	Life.SetCurrentValue(LifeMax.GetCurrentValue());
	Ki.SetCurrentValue(KiMax.GetCurrentValue());
}

void UGasBaseAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	
	if (Attribute == GetLifeMaxAttribute())
    {
        float CurrentLife = GetLife();
        if (CurrentLife > NewValue)
        {
            NewValue = CurrentLife;
        }
    }
    else if (Attribute == GetKiMaxAttribute())
    {
        float CurrentKi = GetKi();
        if (CurrentKi > NewValue)
        {
            NewValue = CurrentKi;
        }
    }
    else if (Attribute == GetXPAttribute())
    {
        if (NewValue < 0.f)
        {
            NewValue = 0.f;
        }
    }
    else if (Attribute == GetMoneyAttribute())
    {
        if (NewValue < 0.f)
        {
            NewValue = 0.f;
        }
    }else if (Attribute == GetPhysicalDamageAttribute())
    {
	    NewValue = FMath::Clamp(NewValue, 0.f, 9999.f);
    }else if (Attribute == GetFireDamageAttribute())
    {
    	NewValue = FMath::Clamp(NewValue, 0.f, 9999.f);
    }else if (Attribute == GetWaterDamageAttribute())
    {
    	NewValue = FMath::Clamp(NewValue, 0.f, 9999.f);
    }else if (Attribute == GetWindDamageAttribute())
    {
    	NewValue = FMath::Clamp(NewValue, 0.f, 9999.f);
    }else if (Attribute == GetEarthDamageAttribute())
    {
    	NewValue = FMath::Clamp(NewValue, 0.f, 9999.f);
    }else if (Attribute == GetLightningDamageAttribute())
    {
    	NewValue = FMath::Clamp(NewValue, 0.f, 9999.f);
    }else if (Attribute == GetPoisonDamageAttribute())
    {
    	NewValue = FMath::Clamp(NewValue, 0.f, 9999.f);
    }else if (Attribute == GetParalysisDamageAttribute())
    {
    	NewValue =  FMath::Clamp(NewValue, 0.f, 9999.f);
    }else if (Attribute == GetYokaiRealmDamageAttribute())
    {
    	NewValue = FMath::Clamp(NewValue, 0.f, 9999.f);
    }
	
    // Limitação das resistências para 0-95% no PreAttributeChange
    if (Attribute == GetGuardBreakResistanceAttribute() ||
        Attribute == GetFireResistanceAttribute() ||
        Attribute == GetWaterResistanceAttribute() ||
        Attribute == GetWindResistanceAttribute() ||
        Attribute == GetEarthResistanceAttribute() ||
        Attribute == GetLightningResistanceAttribute() ||
        Attribute == GetPoisonResistanceAttribute() ||
        Attribute == GetParalysisResistanceAttribute() ||
        Attribute == GetYokaiRealmResistanceAttribute())
    {
        float ClampedValue = FMath::Clamp(NewValue, 0.f, 95.f);
        // Usar setter para atualizar o atributo com o valor clamped
        if (Attribute == GetGuardBreakResistanceAttribute())
           NewValue = ClampedValue;
        else if (Attribute == GetFireResistanceAttribute())
            NewValue = ClampedValue;
        else if (Attribute == GetWaterResistanceAttribute())
        	NewValue = ClampedValue;
        else if (Attribute == GetWindResistanceAttribute())
        	NewValue = ClampedValue;
        else if (Attribute == GetEarthResistanceAttribute())
        	NewValue = ClampedValue;
        else if (Attribute == GetLightningResistanceAttribute())
        	NewValue = ClampedValue;
        else if (Attribute == GetPoisonResistanceAttribute())
        	NewValue = ClampedValue;
        else if (Attribute == GetParalysisResistanceAttribute())
        	NewValue = ClampedValue;
        else if (Attribute == GetYokaiRealmResistanceAttribute())
        	NewValue = ClampedValue;
    }
}

void UGasBaseAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FGameplayAttribute Attribute = Data.EvaluatedData.Attribute;
 
	// Recalcula derivados baseados nas mudanças
	if (Attribute == GetBodyAttribute())
	{
		float NewLifeMax = GetBody() * 10.f;
		float NewPoisonResist = GetBody() * 0.2f;
		float NewParalysisResist = GetBody() * 0.2f;
		
		SetLifeMax(NewLifeMax);
		SetLife(FMath::Min(GetLife(), NewLifeMax));

		SetPoisonResistance(NewPoisonResist);
		SetParalysisResistance(NewParalysisResist);
	}

	if (Attribute == GetHeartAttribute())
	{
		float NewKiMax = GetHeart() * 10.f;
		SetKiMax(NewKiMax);
		SetKi(FMath::Min(GetKi(), NewKiMax));
	}

	if (Attribute == GetStaminaAttribute())
	{
		float NewLifeMax = GetStamina() * 10.f;
		SetLifeMax(NewLifeMax);
		SetLife(FMath::Min(GetLife(), NewLifeMax));
	}

	if (Attribute == GetStrengthAttribute())
	{
		SetAttack(GetStrength() * 2.f);
	}

	if (Attribute == GetSkillAttribute())
	{
		SetAttack(GetStrength() * 1.f);
	}

	if (Attribute == GetDexterityAttribute())
	{
		SetAttack(GetStrength() * 2.f);
	}

	if (Attribute == GetMagicAttribute())
	{
		float NewYokaiResist = GetMagic() * 3.f;
		SetYokaiRealmResistance(NewYokaiResist);
	}
	
	if (Attribute == GetSpiritAttribute())
	{
		float NewYokaiResist = GetMagic() * 2.5f;
		SetYokaiRealmResistance(NewYokaiResist);		
	}
	
	if (Attribute == GetPhysicalDamageAttribute())
	{
		SetAttack(GetAttack() + GetPhysicalDamage() * 2.f);
	}

	if (Attribute == GetFireDamageAttribute())
	{
		SetAttack(GetAttack() + GetFireDamage() * 2.f);
	}

	if (Attribute == GetWaterDamageAttribute())
	{
		SetAttack(GetAttack() + GetWaterDamage() * 2.f);
	}

	if (Attribute == GetWindDamageAttribute())
	{
		SetAttack(GetAttack() + GetWindDamage() * 2.f);
	}

	if (Attribute == GetEarthDamageAttribute())
	{
		SetAttack(GetAttack() + GetEarthDamage() * 2.f);
	}

	if (Attribute == GetLightningDamageAttribute())
	{
		SetAttack(GetAttack() + GetLightningDamage() * 2.f);
	}

	if (Attribute == GetPoisonDamageAttribute())
	{
		SetAttack(GetAttack() + GetPoisonDamage() * 2.f);
	}

	if (Attribute == GetParalysisDamageAttribute())
	{
		SetAttack(GetAttack() + GetParalysisDamage() * 2.f);
	}

	if (Attribute == GetYokaiRealmDamageAttribute())
	{
		SetAttack(GetAttack() + GetYokaiRealmDamage() * 2.f);
	}
	
	if (Attribute == GetPhysicalBlockAttribute() || Attribute == GetDefenseAttribute())
	{
		SetDefense(GetDefense() + GetPhysicalBlock() * 2.f);
	}
 
	// XP e Level com level up automático
	if (Attribute == GetXPAttribute())
	{
		AddXP(GetXP());
	}

	// Verifica se o Player morreu
	if (Attribute == GetLifeAttribute())
	{
		float CurrentLife = GetLife();
		if (CurrentLife <= 0.0f)
		{
			const FGameplayEffectContextHandle& EffectContextHandle = Data.EffectSpec.GetEffectContext();
			AActor* Killer = EffectContextHandle.GetInstigator();
			bIsAlive = false;
			OnEliminated.Broadcast(Killer);
		}
		bIsAlive = true;
	}

	// Verifica se o Player Esta sem Ki
	if (Attribute == GetKiAttribute())
	{
		float CurrentKi = GetKi();
		if (CurrentKi <= 0.0f)
		{
			OnOutOfKi.Broadcast();
		}
	}
 
	// Limita Life e Ki para valores máximos
	SetLife(FMath::Clamp(GetLife(), 0.f, GetLifeMax()));
	SetKi(FMath::Clamp(GetKi(), 0.f, GetKiMax()));
 
	// Limita Money para não-negativo
	SetMoney(FMath::Max(GetMoney(), 0.f));
 
	// Limita resistências para faixa 0-95% após execução
	SetGuardBreakResistance(FMath::Clamp(GetGuardBreakResistance(), 0.f, 95.f));
	SetFireResistance(FMath::Clamp(GetFireResistance(), 0.f, 95.f));
	SetWaterResistance(FMath::Clamp(GetWaterResistance(), 0.f, 95.f));
	SetWindResistance(FMath::Clamp(GetWindResistance(), 0.f, 95.f));
	SetEarthResistance(FMath::Clamp(GetEarthResistance(), 0.f, 95.f));
	SetLightningResistance(FMath::Clamp(GetLightningResistance(), 0.f, 95.f));
	SetPoisonResistance(FMath::Clamp(GetPoisonResistance(), 0.f, 95.f));
	SetParalysisResistance(FMath::Clamp(GetParalysisResistance(), 0.f, 95.f));
	SetYokaiRealmResistance(FMath::Clamp(GetYokaiRealmResistance(), 0.f, 95.f));	
}

void UGasBaseAttributeSet::AddAttributePoint(const FGameplayAttribute& Attribute)
{
	if (GetAttributePoints() <= 0)
		return;

	float* SpentPoints = nullptr;
	float* BaseValue = nullptr;
	float* CurrentValue = nullptr;

	if (Attribute == GetBodyAttribute())
	{
		*SpentPoints = SpentPointsBody.GetBaseValue();
		*BaseValue = BaseBody.GetCurrentValue();
		*CurrentValue = Body.GetCurrentValue();
	}

	if (Attribute == GetHeartAttribute())
	{
		*SpentPoints = SpentPointsHeart.GetBaseValue();
		*BaseValue = BaseHeart.GetCurrentValue();
		*CurrentValue = Heart.GetCurrentValue();
	}

	if (Attribute == GetStaminaAttribute())
	{
		*SpentPoints = SpentPointsStamina.GetBaseValue();
		*BaseValue = BaseStamina.GetCurrentValue();
		*CurrentValue = Stamina.GetCurrentValue();
	}

	if (Attribute == GetStrengthAttribute())
	{
		*SpentPoints = SpentPointsStrength.GetBaseValue();
		*BaseValue = BaseStrength.GetCurrentValue();
		*CurrentValue = Strength.GetCurrentValue();
	}

	if (Attribute == GetSkillAttribute())
	{
		*SpentPoints = SpentPointsSkill.GetBaseValue();
		*BaseValue = BaseSkill.GetCurrentValue();
		*CurrentValue = Skill.GetCurrentValue();
	}

	if (Attribute == GetDexterityAttribute())
	{
		*SpentPoints = SpentPointsDexterity.GetBaseValue();
		*BaseValue = BaseDexterity.GetCurrentValue();
		*CurrentValue = Dexterity.GetCurrentValue();
	}

	if (Attribute == GetMagicAttribute())
	{
		*SpentPoints = SpentPointsMagic.GetBaseValue();
		*BaseValue = BaseMagic.GetCurrentValue();
		*CurrentValue = Magic.GetCurrentValue();
	}

	if (Attribute == GetSpiritAttribute())
	{
		*SpentPoints = SpentPointsSpirit.GetBaseValue();
		*BaseValue = BaseSpirit.GetCurrentValue();
		*CurrentValue = Spirit.GetCurrentValue();
	}
	
	if (SpentPoints && BaseValue && CurrentValue)
	{
		SetAttributePoints(GetAttributePoints() - 1);
		(*SpentPoints)++;
		*CurrentValue = *BaseValue + *SpentPoints;
	}	
}

void UGasBaseAttributeSet::ResetAttributePoints()
{
	float TotalPoints = 0;

	// Soma todo os pontos gastos
	TotalPoints += SpentPointsBody.GetCurrentValue();
	TotalPoints += SpentPointsHeart.GetCurrentValue();
	TotalPoints += SpentPointsStamina.GetCurrentValue();
	TotalPoints += SpentPointsStrength.GetCurrentValue();
	TotalPoints += SpentPointsSkill.GetCurrentValue();
	TotalPoints += SpentPointsDexterity.GetCurrentValue();
	TotalPoints += SpentPointsMagic.GetCurrentValue();
	TotalPoints += SpentPointsSpirit.GetCurrentValue();
	
	// Reseta os atributos para seus valores base
	SetBody(GetBaseBody());
	SetHeart(GetBaseHeart());
	SetStamina(GetBaseStamina());
	SetStrength(GetBaseStrength());
	SetSkill(GetBaseSkill());
	SetDexterity(GetBaseDexterity());
	SetMagic(GetBaseMagic());
	SetSpirit(GetBaseSpirit());
	
	// Zera os pontos gastos
	SpentPointsBody.SetCurrentValue(0.f);
	SpentPointsHeart.SetCurrentValue(0.f);
	SpentPointsStamina.SetCurrentValue(0.f);
	SpentPointsStrength.SetCurrentValue(0.f);
	SpentPointsSkill.SetCurrentValue(0.f);
	SpentPointsDexterity.SetCurrentValue(0.f);
	SpentPointsMagic.SetCurrentValue(0.f);
	SpentPointsSpirit.SetCurrentValue(0.f);
	
	// Devolve os pontos para serem gastos novamente
	SetAttributePoints(GetAttributePoints() + TotalPoints);
}

float UGasBaseAttributeSet::GetAvailablePoints() const
{
	return GetAttributePoints();
}

void UGasBaseAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Atributos base
	DOREPLIFETIME_CONDITION_NOTIFY(UGasBaseAttributeSet, Body, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGasBaseAttributeSet, Heart, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGasBaseAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGasBaseAttributeSet, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGasBaseAttributeSet, Skill, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGasBaseAttributeSet, Dexterity, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGasBaseAttributeSet, Magic, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGasBaseAttributeSet, Spirit, COND_None, REPNOTIFY_Always);

	// Atributos derivados
	DOREPLIFETIME_CONDITION_NOTIFY(UGasBaseAttributeSet, LifeMax, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGasBaseAttributeSet, Life, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGasBaseAttributeSet, KiMax, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGasBaseAttributeSet, Ki, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGasBaseAttributeSet, Attack, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGasBaseAttributeSet, Defense, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGasBaseAttributeSet, PhysicalBlock, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGasBaseAttributeSet, AttackRating, COND_None, REPNOTIFY_Always);

	// Dano
	DOREPLIFETIME_CONDITION_NOTIFY(UGasBaseAttributeSet, PhysicalDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGasBaseAttributeSet, FireDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGasBaseAttributeSet, WaterDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGasBaseAttributeSet, WindDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGasBaseAttributeSet, EarthDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGasBaseAttributeSet, LightningDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGasBaseAttributeSet, PoisonDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGasBaseAttributeSet, ParalysisDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGasBaseAttributeSet, YokaiRealmDamage, COND_None, REPNOTIFY_Always);

	// Resistencias
	DOREPLIFETIME_CONDITION_NOTIFY(UGasBaseAttributeSet, GuardBreakResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGasBaseAttributeSet, FireResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGasBaseAttributeSet, WaterResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGasBaseAttributeSet, EarthResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGasBaseAttributeSet, WindResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGasBaseAttributeSet, LightningResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGasBaseAttributeSet, PoisonResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGasBaseAttributeSet, ParalysisResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGasBaseAttributeSet, YokaiRealmResistance, COND_None, REPNOTIFY_Always);
	
	// XP, Level and Money
	DOREPLIFETIME_CONDITION_NOTIFY(UGasBaseAttributeSet, XP, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGasBaseAttributeSet, Level, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGasBaseAttributeSet, Money, COND_None, REPNOTIFY_Always);
}

void UGasBaseAttributeSet::AddXP(float Amount)
{
	float CurrentXP = GetXP();
	float CurrentLevel = GetLevel();
 
	CurrentXP += Amount;
 
	while (CurrentXP >= GetXPRequiredForNextLevel())
	{
		CurrentXP -= GetXPRequiredForNextLevel();
		CurrentLevel += 1.f;
		SetAttributePoints(GetAttributePoints() + GetPointsPerLevel());
		
		OnLevelUp.Broadcast();
	}
 
	SetXP(CurrentXP);
	SetLevel(CurrentLevel);
}

float UGasBaseAttributeSet::GetXPRequiredForNextLevel() const
{
	return FMath::Pow(1.15f, GetLevel()) * 100.f;
}

#define IMPLEMENT_ONREP_ATTR(AttrName) \
void UGasBaseAttributeSet::OnRep_##AttrName(const FGameplayAttributeData& OldValue) \
{ \
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGasBaseAttributeSet, AttrName, OldValue); \
}

// Attribute Points
IMPLEMENT_ONREP_ATTR(AttributePoints)

// Base
IMPLEMENT_ONREP_ATTR(Body)
IMPLEMENT_ONREP_ATTR(Heart)
IMPLEMENT_ONREP_ATTR(Stamina)
IMPLEMENT_ONREP_ATTR(Strength)
IMPLEMENT_ONREP_ATTR(Skill)
IMPLEMENT_ONREP_ATTR(Dexterity)
IMPLEMENT_ONREP_ATTR(Magic)
IMPLEMENT_ONREP_ATTR(Spirit)

// Atributos Derivados
IMPLEMENT_ONREP_ATTR(LifeMax)
IMPLEMENT_ONREP_ATTR(Life)
IMPLEMENT_ONREP_ATTR(KiMax)
IMPLEMENT_ONREP_ATTR(Ki)
IMPLEMENT_ONREP_ATTR(Attack)
IMPLEMENT_ONREP_ATTR(Defense)
IMPLEMENT_ONREP_ATTR(PhysicalBlock)
IMPLEMENT_ONREP_ATTR(AttackRating)

// Dano
IMPLEMENT_ONREP_ATTR(PhysicalDamage)
IMPLEMENT_ONREP_ATTR(FireDamage)
IMPLEMENT_ONREP_ATTR(WaterDamage)
IMPLEMENT_ONREP_ATTR(WindDamage)
IMPLEMENT_ONREP_ATTR(EarthDamage)
IMPLEMENT_ONREP_ATTR(LightningDamage)
IMPLEMENT_ONREP_ATTR(PoisonDamage)
IMPLEMENT_ONREP_ATTR(ParalysisDamage)
IMPLEMENT_ONREP_ATTR(YokaiRealmDamage)

// Resistências
IMPLEMENT_ONREP_ATTR(GuardBreakResistance)
IMPLEMENT_ONREP_ATTR(FireResistance)
IMPLEMENT_ONREP_ATTR(WaterResistance)
IMPLEMENT_ONREP_ATTR(EarthResistance)
IMPLEMENT_ONREP_ATTR(WindResistance)
IMPLEMENT_ONREP_ATTR(LightningResistance)
IMPLEMENT_ONREP_ATTR(PoisonResistance)
IMPLEMENT_ONREP_ATTR(ParalysisResistance)
IMPLEMENT_ONREP_ATTR(YokaiRealmResistance)

// XP, Level and Money
IMPLEMENT_ONREP_ATTR(XP)
IMPLEMENT_ONREP_ATTR(Level)
IMPLEMENT_ONREP_ATTR(Money)
