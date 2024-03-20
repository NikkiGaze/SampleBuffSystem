// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuffComponentBase.generated.h"

struct FBuffDescriptor;

UCLASS()
class BUFFSYSTEMDEMO_API UABuffComponentBase : public USceneComponent
{
	GENERATED_BODY()

public:
	virtual void Init(const FBuffDescriptor Descriptor);
};
