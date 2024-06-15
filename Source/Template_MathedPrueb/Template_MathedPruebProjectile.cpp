// Copyright Epic Games, Inc. All Rights Reserve

#include "Template_MathedPruebProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/StaticMesh.h"

#include "NavesNPC.h"
#include "Asteroide.h"
#include "AsteroidePequenio.h"
#include "Meteorito.h"



ATemplate_MathedPruebProjectile::ATemplate_MathedPruebProjectile() 
{
	// Static reference to the mesh to use for the projectile
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("/Game/TwinStick/Meshes/TwinStickProjectile.TwinStickProjectile"));

	// Create mesh component for the projectile sphere
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh0"));
	ProjectileMesh->SetStaticMesh(ProjectileMeshAsset.Object);
	ProjectileMesh->SetupAttachment(RootComponent);
	ProjectileMesh->BodyInstance.SetCollisionProfileName("Projectile");
	ProjectileMesh->OnComponentHit.AddDynamic(this, &ATemplate_MathedPruebProjectile::OnHit);		// set up a notification for when this component hits something
	RootComponent = ProjectileMesh;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement0"));
	ProjectileMovement->UpdatedComponent = ProjectileMesh;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 0.f; // No gravity

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void ATemplate_MathedPruebProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 20.0f, GetActorLocation());
	}

	ANavesNPC* naveNPC = Cast<ANavesNPC>(OtherActor);	
	if (naveNPC != nullptr)
	{
		naveNPC->RecibirDanio();
	}

	AAsteroide* asteroide = Cast<AAsteroide>(OtherActor);
	if (asteroide != nullptr)
	{
		asteroide->RecibirDanio();
	}

	AMeteorito* meteorito = Cast<AMeteorito>(OtherActor);
	if (meteorito != nullptr)
	{
		meteorito->RecibirDanio();
	}

	AAsteroidePequenio* asteroidePequenio = Cast<AAsteroidePequenio>(OtherActor);
	if (asteroidePequenio != nullptr)
	{
		asteroidePequenio->RecibirDanio();
	}

	Destroy();
}