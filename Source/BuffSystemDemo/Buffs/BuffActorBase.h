// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuffActorBase.generated.h"

class UNiagaraSystem;
struct FBuffDescriptor;

UCLASS()
class BUFFSYSTEMDEMO_API ABuffActorBase : public AActor
{
	GENERATED_BODY()

public:
	virtual void Init(const FBuffDescriptor Descriptor);
};
