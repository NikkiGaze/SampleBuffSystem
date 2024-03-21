// Copyright Epic Games, Inc. All Rights Reserved.

#include "TP_ThirdPersonCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "NiagaraFunctionLibrary.h"


//////////////////////////////////////////////////////////////////////////
// ATP_ThirdPersonCharacter

ATP_ThirdPersonCharacter::ATP_ThirdPersonCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
}

void ATP_ThirdPersonCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ATP_ThirdPersonCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UPawnMovementComponent* MovementComponent = GetMovementComponent();
	if (!IsValid(MovementComponent))
	{
		return;
	}
	const FVector Direction = GetActorForwardVector();

	FHitResult HitResult;
	FVector Start = GetActorLocation();
	FVector End = Start + Direction * DeltaSeconds * Speed * 1000;;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	if (!GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_WorldStatic, CollisionParams))
	{
		MovementComponent->AddInputVector(Direction * DeltaSeconds * Speed);
	}
	else
	{
		FRotator CurrentRotation = GetActorRotation();
		FRotator TargetRotation = CurrentRotation + FRotator(0.0f, 180.0f, 0.0f);
		SetActorRotation(TargetRotation);
	}
}

void ATP_ThirdPersonCharacter::ApplyBuff(const FBuffDescriptor &BuffDescriptor)
{
	if (IsValid(BuffDescriptor.BuffClass))
	{
		UABuffComponentBase* BuffComponent = NewObject<UABuffComponentBase>(this, BuffDescriptor.BuffClass);
		if (BuffComponent)
		{
			BuffComponent->RegisterComponent();
			BuffComponent->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
		}

		BuffComponent->Init(BuffDescriptor);
	}	
}

void ATP_ThirdPersonCharacter::TakeDamage(int Damage)
{
	Health -= Damage;

	if (Health <= 0)
	{
		Destroy();
	}
}
