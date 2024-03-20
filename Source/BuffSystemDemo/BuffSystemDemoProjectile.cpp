// Copyright Epic Games, Inc. All Rights Reserved.

#include "BuffSystemDemoProjectile.h"

#include "BuffSystemDemoCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TP_ThirdPerson/TP_ThirdPersonCharacter.h"

ABuffSystemDemoProjectile::ABuffSystemDemoProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &ABuffSystemDemoProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void ABuffSystemDemoProjectile::SetBuffDescriptor(const FBuffDescriptor &InBuffDescriptor)
{
	BuffDescriptor = InBuffDescriptor;
}

void ABuffSystemDemoProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));

	TArray<AActor *> OutActors;
	UKismetSystemLibrary::SphereOverlapActors(GetWorld(), Hit.Location, ExplosionRadius, ObjectTypes, ACharacter::StaticClass(), TArray<AActor*>(), OutActors); 

	DrawDebugSphere(GetWorld(), Hit.Location, ExplosionRadius, 12, FColor::Red, false, 10.0f);

	for (AActor *DamagedCharacter : OutActors)
	{
		DrawDebugSphere(GetWorld(), DamagedCharacter->GetActorLocation(), 100, 12, FColor::Blue, false, 10.0f);
		if (auto EnemyCharacter = Cast<ATP_ThirdPersonCharacter>(DamagedCharacter))
		{
			EnemyCharacter->ApplyBuff(BuffDescriptor);
		}
	}

	Destroy();
}
