// Copyright Epic Games, Inc. All Rights Reserved.

#include "BuffSystemDemoCharacter.h"
#include "BuffSystemDemoProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"


//////////////////////////////////////////////////////////////////////////
// ABuffSystemDemoCharacter

ABuffSystemDemoCharacter::ABuffSystemDemoCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	TurnRateGamepad = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

}

void ABuffSystemDemoCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

}

//////////////////////////////////////////////////////////////////////////// Input

void ABuffSystemDemoCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event
	PlayerInputComponent->BindAction("Shoot1", IE_Pressed, this, &ABuffSystemDemoCharacter::OnShoot1);
	PlayerInputComponent->BindAction("Shoot2", IE_Pressed, this, &ABuffSystemDemoCharacter::OnShoot2);
	PlayerInputComponent->BindAction("Shoot3", IE_Pressed, this, &ABuffSystemDemoCharacter::OnShoot3);

	// Enable touchscreen input
	EnableTouchscreenMovement(PlayerInputComponent);

	// Bind movement events
	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &ABuffSystemDemoCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &ABuffSystemDemoCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "Mouse" versions handle devices that provide an absolute delta, such as a mouse.
	// "Gamepad" versions are for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn Right / Left Gamepad", this, &ABuffSystemDemoCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("Look Up / Down Gamepad", this, &ABuffSystemDemoCharacter::LookUpAtRate);
}

void ABuffSystemDemoCharacter::OnShoot1()
{
	OnUseItem.Broadcast(BulletType_Burst);
}

void ABuffSystemDemoCharacter::OnShoot3()
{
	OnUseItem.Broadcast(BulletType_Damage);
}

void ABuffSystemDemoCharacter::OnShoot2()
{
	OnUseItem.Broadcast(BulletType_Slow);
}

void ABuffSystemDemoCharacter::BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// if (TouchItem.bIsPressed == true)
	// {
	// 	return;
	// }
	// if ((FingerIndex == TouchItem.FingerIndex) && (TouchItem.bMoved == false))
	// {
	// 	OnPrimaryAction();
	// }
	// TouchItem.bIsPressed = true;
	// TouchItem.FingerIndex = FingerIndex;
	// TouchItem.Location = Location;
	// TouchItem.bMoved = false;
}

void ABuffSystemDemoCharacter::EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == false)
	{
		return;
	}
	TouchItem.bIsPressed = false;
}

void ABuffSystemDemoCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ABuffSystemDemoCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void ABuffSystemDemoCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void ABuffSystemDemoCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

bool ABuffSystemDemoCharacter::EnableTouchscreenMovement(class UInputComponent* PlayerInputComponent)
{
	if (FPlatformMisc::SupportsTouchInput() || GetDefault<UInputSettings>()->bUseMouseForTouch)
	{
		PlayerInputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ABuffSystemDemoCharacter::BeginTouch);
		PlayerInputComponent->BindTouch(EInputEvent::IE_Released, this, &ABuffSystemDemoCharacter::EndTouch);

		return true;
	}
	
	return false;
}
