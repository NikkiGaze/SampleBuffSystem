// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BuffSystemDemo/Buffs/BuffDescriptor.h"
#include "GameFramework/Character.h"
#include "TP_ThirdPersonCharacter.generated.h"

UCLASS(config=Game)
class ATP_ThirdPersonCharacter : public ACharacter
{
	GENERATED_BODY()

	// /** Camera boom positioning the camera behind the character */
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	// class USpringArmComponent* CameraBoom;
	//
	// /** Follow camera */
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	// class UCameraComponent* FollowCamera;
public:
	ATP_ThirdPersonCharacter();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	void ApplyBuff(const FBuffDescriptor &BuffDescriptor);
	void TakeDamage(int Damage);

private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	int Health;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	float Speed;
	
	UPROPERTY()
	int MoveDirection;
};

