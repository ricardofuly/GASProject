// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/GasCharacter.h"

#include "AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AGasCharacter::AGasCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Character Default Settings
	GetCapsuleComponent()->InitCapsuleSize(35.f, 90.f);

	// Camera Defaults
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	// Character Movement Defaults
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);

	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.f;
	

	// Ability System
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(AbilitySystemReplicationMode);

	// Attribute Set
	BaseAttributeSet = CreateDefaultSubobject<UGasBaseAttributeSet>(TEXT("BaseAttributeSet"));
}

class UAbilitySystemComponent* AGasCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// Called when the game starts or when spawned
void AGasCharacter::BeginPlay()
{
	Super::BeginPlay();

	BaseAttributeSet->OnLevelUp.AddUniqueDynamic(this, &ThisClass::AGasCharacter::HandleLevelUP);
	
	if (AbilitySystemComponent)
	{

		// Give initial abilities for the player
		if (HasAuthority())
		{
			for (TSubclassOf Ability : StartingAbilities)
			{
				GetAbilitySystemComponent()->GiveAbility(Ability);
			}
			for (TSubclassOf Effect : StartingEffects)
			{
				if (IsValid(Effect))
				{
					GetAbilitySystemComponent()->ApplyGameplayEffectToSelf(Effect.GetDefaultObject(), GetCharacterLevel(), FGameplayEffectContextHandle());
				}
			}
		}
	}
}

void AGasCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}

void AGasCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}

void AGasCharacter::HandleLevelUP()
{
	if (AbilitySystemComponent)
	{
		if (IsValid(LevelUpEffect))
		{
			AbilitySystemComponent->ApplyGameplayEffectToSelf(LevelUpEffect.GetDefaultObject(), GetCharacterLevel(), FGameplayEffectContextHandle());
		}
	}
}

float AGasCharacter::GetCharacterLevel() const
{
	if (AbilitySystemComponent)
	{
		if (BaseAttributeSet)
		{
			return BaseAttributeSet->GetLevel();
		}
	}
	return 0.f;
}

// Called every frame
void AGasCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGasCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

