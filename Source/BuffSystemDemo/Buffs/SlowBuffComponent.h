// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuffComponentBase.h"
#include "SlowBuffComponent.generated.h"


class UNiagaraComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BUFFSYSTEMDEMO_API USlowBuffComponent : public UABuffComponentBase
{
	GENERATED_BODY()

public:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
	virtual void Init(const FBuffDescriptor Descriptor) override;
	
private:
	void OnTimer();
	
	UPROPERTY()
	float Value;

	UPROPERTY()
	UNiagaraComponent *Effect;

	UPROPERTY()
	FTimerHandle TimerHandle;
};
