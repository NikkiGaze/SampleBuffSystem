// Fill out your copyright notice in the Description page of Project Settings.


#include "BurstBuffActor.h"

#include "BuffDescriptor.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "BuffSystemDemo/TP_ThirdPerson/TP_ThirdPersonCharacter.h"


// Sets default values
ABurstBuffActor::ABurstBuffActor()
{
	RootComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root"));
}

void ABurstBuffActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorldTimerManager().ClearTimer(TimerHandle);
	Effect->GetSystemInstanceController()->Deactivate();
}

void ABurstBuffActor::Init(const FBuffDescriptor Descriptor)
{
	Value = Descriptor.Value;
	Duration = Descriptor.Duration;
	CurrentTickCount = 0;
	
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ABurstBuffActor::OnTimer,
		1.f, true);
	
	Effect = UNiagaraFunctionLibrary::SpawnSystemAttached(Descriptor.Effect, GetRootComponent(), FName(""),
		 FVector(0, 0, 0), FRotator(0, 0, 0), EAttachLocation::SnapToTarget, true);
}

void ABurstBuffActor::OnTimer()
{
	if (ATP_ThirdPersonCharacter *OwningCharacter = Cast<ATP_ThirdPersonCharacter>(GetAttachParentActor()))
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



