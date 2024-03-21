// Fill out your copyright notice in the Description page of Project Settings.


#include "SlowBuffComponent.h"

#include "BuffDescriptor.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "BuffSystemDemo/TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


void USlowBuffComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	Effect->GetSystemInstanceController()->Deactivate();
}

void USlowBuffComponent::Init(const FBuffDescriptor Descriptor)
{
	Value = Descriptor.Value;

	if (ATP_ThirdPersonCharacter *OwningCharacter = Cast<ATP_ThirdPersonCharacter>(GetOwner()))
	{
		OwningCharacter->GetCharacterMovement()->MaxWalkSpeed = OwningCharacter->GetCharacterMovement()->MaxWalkSpeed / Value;
	}
	
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &USlowBuffComponent::OnTimer,
		Descriptor.Duration, false);
	
	Effect = UNiagaraFunctionLibrary::SpawnSystemAttached(Descriptor.Effect, this, FName(""),
		 FVector(0, 0, 0), FRotator(0, 0, 0), EAttachLocation::SnapToTarget, true);
}

void USlowBuffComponent::OnTimer()
{
	if (ATP_ThirdPersonCharacter *OwningCharacter = Cast<ATP_ThirdPersonCharacter>(GetOwner()))
	{
		OwningCharacter->GetCharacterMovement()->MaxWalkSpeed = OwningCharacter->GetCharacterMovement()->MaxWalkSpeed * Value;
		DestroyComponent();
	}
}