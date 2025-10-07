// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/AttributeSets/GasBaseAttributeSet.h"
#include "GameFramework/Character.h"
#include "GasCharacter.generated.h"

UCLASS()
class GASPROJECT_API AGasCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGasCharacter();

	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Ability System")
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Ability System")
	UGasBaseAttributeSet* BaseAttributeSet;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ability System" , meta=(DisplayName="Replication Mode"))
	EGameplayEffectReplicationMode AbilitySystemReplicationMode = EGameplayEffectReplicationMode::Mixed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ability System")
	TArray<TSubclassOf<UGameplayAbility>> StartingAbilities;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ability System")
	TArray<TSubclassOf<UGameplayEffect>> StartingEffects;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ability System")
	TSubclassOf<UGameplayEffect> LevelUpEffect;

	UFUNCTION()
	void HandleLevelUP();

	UFUNCTION(BlueprintCallable, Category = "Ability System")
	float GetCharacterLevel() const;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
