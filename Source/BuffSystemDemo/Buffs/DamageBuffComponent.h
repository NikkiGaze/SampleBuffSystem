// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuffComponentBase.h"
#include "DamageBuffComponent.generated.h"


class UNiagaraComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BUFFSYSTEMDEMO_API UDamageBuffComponent : public UABuffComponentBase
{
	GENERATED_BODY()

protected:
	virtual void Init(const FBuffDescriptor Descriptor) override;
};
