// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "GasBaseAttributeSet.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEliminatedDelegate, AActor*, Killer);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOutOfKi);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelUp);
 

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class GASPROJECT_API UGasBaseAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:

	UGasBaseAttributeSet();

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	UPROPERTY(BlueprintAssignable)
	FOnEliminatedDelegate OnEliminated;

	UPROPERTY(BlueprintAssignable)
	FOnOutOfKi OnOutOfKi;

	UPROPERTY(BlueprintAssignable)
	FOnLevelUp OnLevelUp;

	// Pontos de Atributo
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Points", ReplicatedUsing = OnRep_AttributePoints)
	FGameplayAttributeData AttributePoints;
	ATTRIBUTE_ACCESSORS(UGasBaseAttributeSet, AttributePoints)
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Points")
	FGameplayAttributeData PointsPerLevel;
	ATTRIBUTE_ACCESSORS(UGasBaseAttributeSet, PointsPerLevel)

	// Pontos Gastos por Attributo
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Points")
	FGameplayAttributeData SpentPointsBody;
	ATTRIBUTE_ACCESSORS(UGasBaseAttributeSet, SpentPointsBody)
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Points")
	FGameplayAttributeData SpentPointsHeart;
	ATTRIBUTE_ACCESSORS(UGasBaseAttributeSet, SpentPointsHeart)

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Points")
	FGameplayAttributeData SpentPointsStamina;
	ATTRIBUTE_ACCESSORS(UGasBaseAttributeSet, SpentPointsStamina)

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Points")
	FGameplayAttributeData SpentPointsStrength;
	ATTRIBUTE_ACCESSORS(UGasBaseAttributeSet, SpentPointsStrength)

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Points")
	FGameplayAttributeData SpentPointsSkill;
	ATTRIBUTE_ACCESSORS(UGasBaseAttributeSet, SpentPointsSkill)

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Points")
	FGameplayAttributeData SpentPointsDexterity;
	ATTRIBUTE_ACCESSORS(UGasBaseAttributeSet, SpentPointsDexterity)

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Points")
	FGameplayAttributeData SpentPointsMagic;
	ATTRIBUTE_ACCESSORS(UGasBaseAttributeSet, SpentPointsMagic)

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Points")
	FGameplayAttributeData SpentPointsSpirit;
	ATTRIBUTE_ACCESSORS(UGasBaseAttributeSet, SpentPointsSpirit)

	// Valor Base dos Atributos Base
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Base")
	FGameplayAttributeData BaseBody;
	ATTRIBUTE_ACCESSORS(UGasBaseAttributeSet, BaseBody)
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Base")
	FGameplayAttributeData BaseHeart;
	ATTRIBUTE_ACCESSORS(UGasBaseAttributeSet, BaseHeart)

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Base")
	FGameplayAttributeData BaseStamina;
	ATTRIBUTE_ACCESSORS(UGasBaseAttributeSet, BaseStamina)

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Base")
	FGameplayAttributeData BaseStrength;
	ATTRIBUTE_ACCESSORS(UGasBaseAttributeSet, BaseStrength)

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Base")
	FGameplayAttributeData BaseSkill;
	ATTRIBUTE_ACCESSORS(UGasBaseAttributeSet, BaseSkill)

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Base")
	FGameplayAttributeData BaseDexterity;
	ATTRIBUTE_ACCESSORS(UGasBaseAttributeSet, BaseDexterity)

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Base")
	FGameplayAttributeData BaseMagic;
	ATTRIBUTE_ACCESSORS(UGasBaseAttributeSet, BaseMagic)

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Base")
	FGameplayAttributeData BaseSpirit;
	ATTRIBUTE_ACCESSORS(UGasBaseAttributeSet, BaseSpirit)
	

	// Attributos Base
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Body, Category = "Attribute|Base")
    FGameplayAttributeData Body;
    ATTRIBUTE_ACCESSORS(UGasBaseAttributeSet, Body)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Heart, Category = "Attribute|Base")
	FGameplayAttributeData Heart;
	ATTRIBUTE_ACCESSORS(UGasBaseAttributeSet, Heart)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Stamina, Category = "Attribute|Base")
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UGasBaseAttributeSet, Stamina)
 
    UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Strength, Category = "Attribute|Base")
    FGameplayAttributeData Strength;
    ATTRIBUTE_ACCESSORS(UGasBaseAttributeSet, Strength)
 
    UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Skill, Category = "Attribute|Base")
    FGameplayAttributeData Skill;
    ATTRIBUTE_ACCESSORS(UGasBaseAttributeSet, Skill)
 
    UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Dexterity, Category = "Attribute|Base")
    FGameplayAttributeData Dexterity;
    ATTRIBUTE_ACCESSORS(UGasBaseAttributeSet, Dexterity)
 
    UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Magic, Category = "Attribute|Base")
    FGameplayAttributeData Magic;
    ATTRIBUTE_ACCESSORS(UGasBaseAttributeSet, Magic)
 
    UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Spirit, Category = "Attribute|Base")
    FGameplayAttributeData Spirit;
    ATTRIBUTE_ACCESSORS(UGasBaseAttributeSet, Spirit)
 
    // --- Atributos Derivados ---
    UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_LifeMax, Category = "Attribute|Derived")
    FGameplayAttributeData LifeMax;
    ATTRIBUTE_ACCESSORS(UGasBaseAttributeSet, LifeMax)
 
    UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Life, Category = "Attribute|Derived")
    FGameplayAttributeData Life;
    ATTRIBUTE_ACCESSORS(UGasBaseAttributeSet, Life)
 
    UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_KiMax, Category = "Attribute|Derived")
    FGameplayAttributeData KiMax;
    ATTRIBUTE_ACCESSORS(UGasBaseAttributeSet, KiMax)
 
    UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Ki, Category = "Attribute|Derived")
    FGameplayAttributeData Ki;
    ATTRIBUTE_ACCESSORS(UGasBaseAttributeSet, Ki)
 
    UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Attack, Category = "Attribute|Derived")
    FGameplayAttributeData Attack;
    ATTRIBUTE_ACCESSORS(UGasBaseAttributeSet, Attack)
 
    UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Defense, Category = "Attribute|Derived")
    FGameplayAttributeData Defense;
    ATTRIBUTE_ACCESSORS(UGasBaseAttributeSet, Defense)
 
    UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_PhysicalBlock, Category = "Attribute|Derived")
    FGameplayAttributeData PhysicalBlock;
    ATTRIBUTE_ACCESSORS(UGasBaseAttributeSet, PhysicalBlock)
 
    UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_AttackRating, Category = "Attribute|Derived")
    FGameplayAttributeData AttackRating;
    ATTRIBUTE_ACCESSORS(UGasBaseAttributeSet, AttackRating)

	// Atributos de Dano
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_PhysicalDamage, Category = "Attribute|Damage")
	FGameplayAttributeData PhysicalDamage;
	ATTRIBUTE_ACCESSORS(UGasBaseAttributeSet, PhysicalDamage)
 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_FireDamage, Category = "Attribute|Damage")
	FGameplayAttributeData FireDamage;
	ATTRIBUTE_ACCESSORS(UGasBaseAttributeSet, FireDamage)
 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_WaterDamage, Category = "Attribute|Damage")
	FGameplayAttributeData WaterDamage;
	ATTRIBUTE_ACCESSORS(UGasBaseAttributeSet, WaterDamage)
 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_WindDamage, Category = "Attribute|Damage")
	FGameplayAttributeData WindDamage;
	ATTRIBUTE_ACCESSORS(UGasBaseAttributeSet, WindDamage)
 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_EarthDamage, Category = "Attribute|Damage")
	FGameplayAttributeData EarthDamage;
	ATTRIBUTE_ACCESSORS(UGasBaseAttributeSet, EarthDamage)
 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_LightningDamage, Category = "Attribute|Damage")
	FGameplayAttributeData LightningDamage;
	ATTRIBUTE_ACCESSORS(UGasBaseAttributeSet, LightningDamage)
 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_PoisonDamage, Category = "Attribute|Damage")
	FGameplayAttributeData PoisonDamage;
	ATTRIBUTE_ACCESSORS(UGasBaseAttributeSet, PoisonDamage)
 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_ParalysisDamage, Category = "Attribute|Damage")
	FGameplayAttributeData ParalysisDamage;
	ATTRIBUTE_ACCESSORS(UGasBaseAttributeSet, ParalysisDamage)
 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_YokaiRealmDamage, Category = "Attribute|Damage")
	FGameplayAttributeData YokaiRealmDamage;
	ATTRIBUTE_ACCESSORS(UGasBaseAttributeSet, YokaiRealmDamage)

	// --- Resistências ---
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_GuardBreakResistance, Category = "Attribute|Resistance")
	FGameplayAttributeData GuardBreakResistance;
	ATTRIBUTE_ACCESSORS(UGasBaseAttributeSet, GuardBreakResistance)
	 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_FireResistance, Category = "Attribute|Resistance")
	FGameplayAttributeData FireResistance;
	ATTRIBUTE_ACCESSORS(UGasBaseAttributeSet, FireResistance)
	 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_WaterResistance, Category = "Attribute|Resistance")
	FGameplayAttributeData WaterResistance;
	ATTRIBUTE_ACCESSORS(UGasBaseAttributeSet, WaterResistance)
	 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_WindResistance, Category = "Attribute|Resistance")
	FGameplayAttributeData WindResistance;
	ATTRIBUTE_ACCESSORS(UGasBaseAttributeSet, WindResistance)
	 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_EarthResistance, Category = "Attribute|Resistance")
	FGameplayAttributeData EarthResistance;
	ATTRIBUTE_ACCESSORS(UGasBaseAttributeSet, EarthResistance)
	 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_LightningResistance, Category = "Attribute|Resistance")
	FGameplayAttributeData LightningResistance;
	ATTRIBUTE_ACCESSORS(UGasBaseAttributeSet, LightningResistance)
	 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_PoisonResistance, Category = "Attribute|Resistance")
	FGameplayAttributeData PoisonResistance;
	ATTRIBUTE_ACCESSORS(UGasBaseAttributeSet, PoisonResistance)
	 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_ParalysisResistance, Category = "Attribute|Resistance")
	FGameplayAttributeData ParalysisResistance;
	ATTRIBUTE_ACCESSORS(UGasBaseAttributeSet, ParalysisResistance)
	 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_YokaiRealmResistance, Category = "Attribute|Resistance")
	FGameplayAttributeData YokaiRealmResistance;
	ATTRIBUTE_ACCESSORS(UGasBaseAttributeSet, YokaiRealmResistance)

	// --- XP, Level, Dinheiro ---
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_XP, Category = "Attribute|Progression")
	FGameplayAttributeData XP;
	ATTRIBUTE_ACCESSORS(UGasBaseAttributeSet, XP)
 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Level, Category = "Attribute|Progression")
	FGameplayAttributeData Level;
	ATTRIBUTE_ACCESSORS(UGasBaseAttributeSet, Level)
 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Money, Category = "Attribute|Progression")
	FGameplayAttributeData Money;
	ATTRIBUTE_ACCESSORS(UGasBaseAttributeSet, Money)

	UFUNCTION(BlueprintCallable, Category = "Attributes|Points")
	void AddAttributePoint(const FGameplayAttribute& Attribute);

	UFUNCTION(BlueprintCallable, Category = "Attributes|Points")
	void ResetAttributePoints();

	UFUNCTION(BlueprintCallable, Category = "Attributes|Points")
	float GetAvailablePoints() const;

protected:

	virtual  void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	void AddXP(float Amount);

	UFUNCTION(BlueprintCallable, Category= "Attribute | XP")
	float GetXPRequiredForNextLevel() const;

	bool bIsAlive = true;
	
	UFUNCTION(BLueprintCallable, Category = "Attribute | Life")
	virtual bool IsAlive()const {return bIsAlive;}
	
	// Replication Notify functions
	UFUNCTION()
	void OnRep_AttributePoints(const FGameplayAttributeData& OldValue);	
	
	// Atributos Base
	UFUNCTION()
	void OnRep_Body(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_Heart(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_Stamina(const FGameplayAttributeData& OldValue);
 
	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldValue);
 
	UFUNCTION()
	void OnRep_Skill(const FGameplayAttributeData& OldValue);
 
	UFUNCTION()
	void OnRep_Dexterity(const FGameplayAttributeData& OldValue);
 
	UFUNCTION()
	void OnRep_Magic(const FGameplayAttributeData& OldValue);
 
	UFUNCTION()
	void OnRep_Spirit(const FGameplayAttributeData& OldValue);

	// Atributos Derivados
	UFUNCTION()
	void OnRep_LifeMax(const FGameplayAttributeData& OldValue);
 
	UFUNCTION()
	void OnRep_Life(const FGameplayAttributeData& OldValue);
 
	UFUNCTION()
	void OnRep_KiMax(const FGameplayAttributeData& OldValue);
 
	UFUNCTION()
	void OnRep_Ki(const FGameplayAttributeData& OldValue);
 
	UFUNCTION()
	void OnRep_Attack(const FGameplayAttributeData& OldValue);
 
	UFUNCTION()
	void OnRep_Defense(const FGameplayAttributeData& OldValue);
 
	UFUNCTION()
	void OnRep_PhysicalBlock(const FGameplayAttributeData& OldValue);
 
	UFUNCTION()
	void OnRep_AttackRating(const FGameplayAttributeData& OldValue);

	// Dano
	UFUNCTION()
	void OnRep_PhysicalDamage(const FGameplayAttributeData& OldValue);
	
	UFUNCTION()
	void OnRep_FireDamage(const FGameplayAttributeData& OldValue);
	
	UFUNCTION()
	void OnRep_WaterDamage(const FGameplayAttributeData& OldValue);
	
	UFUNCTION()
	void OnRep_WindDamage(const FGameplayAttributeData& OldValue);
	
	UFUNCTION()
	void OnRep_EarthDamage(const FGameplayAttributeData& OldValue);
	
	UFUNCTION()
	void OnRep_LightningDamage(const FGameplayAttributeData& OldValue);
	
	UFUNCTION()
	void OnRep_PoisonDamage(const FGameplayAttributeData& OldValue);
	
	UFUNCTION()
	void OnRep_ParalysisDamage(const FGameplayAttributeData& OldValue);
	
	UFUNCTION()
	void OnRep_YokaiRealmDamage(const FGameplayAttributeData& OldValue);

	// Resistências
	UFUNCTION()
	void OnRep_GuardBreakResistance(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_FireResistance(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_WaterResistance(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_WindResistance(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_EarthResistance(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_LightningResistance(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_PoisonResistance(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_ParalysisResistance(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_YokaiRealmResistance(const FGameplayAttributeData& OldValue);

	// XP, Level, Dinheiro
	UFUNCTION()
	void OnRep_XP(const FGameplayAttributeData& OldValue);
	
	UFUNCTION()
	void OnRep_Level(const FGameplayAttributeData& OldValue);
	
	UFUNCTION()
	void OnRep_Money(const FGameplayAttributeData& OldValue);
	
};
