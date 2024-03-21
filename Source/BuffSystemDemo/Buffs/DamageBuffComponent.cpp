// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageBuffComponent.h"


#include "BuffSystemDemo/TP_ThirdPerson/TP_ThirdPersonCharacter.h"

void UDamageBuffComponent::Init(const FBuffDescriptor Descriptor)
{
	Super::Init(Descriptor);

	if (ATP_ThirdPersonCharacter *OwningCharacter = Cast<ATP_ThirdPersonCharacter>(GetOwner()))
	{
		OwningCharacter->TakeDamage(static_cast<int>(Descriptor.Value));
	}

	DestroyComponent();	
}
