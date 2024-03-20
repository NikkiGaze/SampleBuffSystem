// Fill out your copyright notice in the Description page of Project Settings.


#include "BurstBuffComponent.h"

#include "BuffDescriptor.h"
#include "NiagaraFunctionLibrary.h"
#include "BuffSystemDemo/TP_ThirdPerson/TP_ThirdPersonCharacter.h"


// // Sets default values
// UABurstBuffComponent::UABurstBuffComponent()
// {
// 	RootComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root"));
// }

void UABurstBuffComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	// Effect->GetSystemInstanceController()->Deactivate();
}

void UABurstBuffComponent::Init(const FBuffDescriptor Descriptor)
{
	Value = Descriptor.Value;
	Duration = Descriptor.Duration;
	CurrentTickCount = 0;
	
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UABurstBuffComponent::OnTimer,
		1.f, true);
	
	Effect = UNiagaraFunctionLibrary::SpawnSystemAttached(Descriptor.Effect, this, FName(""),
		 FVector(0, 0, 0), FRotator(0, 0, 0), EAttachLocation::SnapToTarget, true);
}

void UABurstBuffComponent::OnTimer()
{
	if (ATP_ThirdPersonCharacter *OwningCharacter = Cast<ATP_ThirdPersonCharacter>(GetOwner()))
	{
		OwningCharacter->TakeDamage(static_cast<int>(Value));
	}
	
	// CurrentTickCount++;
	// if (CurrentTickCount == Duration)
	// {
	// 	GetWorldTimerManager().ClearTimer(TimerHandle);
	// 	Destroy();
	// }
	
}



