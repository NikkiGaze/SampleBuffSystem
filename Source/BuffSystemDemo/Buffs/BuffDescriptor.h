// // Created by N. Gezhes, ngezhes@temporal-games.com

#pragma once
#include "BuffSystemDemo/Enums/BulletTypes.h"
#include "BuffComponentBase.h"
#include "Engine/DataTable.h"

#include "NiagaraSystem.h"
#include "BuffDescriptor.generated.h"

USTRUCT(BlueprintType)
struct FBuffDescriptor : public FTableRowBase
{
	GENERATED_BODY()

	// UPROPERTY(BlueprintReadWrite, EditAnywhere)
	// EBulletType Type;
	//
	// UPROPERTY(BlueprintReadWrite, EditAnywhere)
	// FString Name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Value;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Duration;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UABuffComponentBase> BuffClass;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UNiagaraSystem *Effect;
};
