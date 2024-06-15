// Fill out your copyright notice in the Description page of Project Settings.


#include "Asteroide.h"
#include "AsteroidePequenio.h" // Incluir la clase de asteroide pequeño para dividir el asteroide
#include "Template_MathedPruebPawn.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AAsteroide::AAsteroide()
{
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("StaticMesh'/Game/TwinStick/Meshes/Shape_Asteroide.Shape_Asteroide'"));
	MeshObstaculo = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshObstaculo"));
	MeshObstaculo->SetStaticMesh(Mesh.Object);

	escalaObstaculo = FVector(1.0f, 1.0f, 1.0f);
	MeshObstaculo->SetWorldScale3D(escalaObstaculo);


	EnergiaObstaculo = 10.0f;
	Velocidad = 450.0f;

	// Inicializa la dirección de movimiento hacia abajo en el eje X
	DireccionMovimiento = FVector(-1.0f, 0.0f, 0.0f);
	VelocidadRotacion = 180.0f; // Grados por segundo


	// Configura la colisión para que llame a OnHit cuando ocurra una colisión
	MeshObstaculo->SetNotifyRigidBodyCollision(true);
	MeshObstaculo->BodyInstance.SetCollisionProfileName("BlockAll");

	MeshObstaculo->OnComponentHit.AddDynamic(this, &AAsteroide::OnHit);
}

void AAsteroide::BeginPlay()
{
	Super::BeginPlay();
}

void AAsteroide::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Mover();
	RotarAleatoriamente();
}

void AAsteroide::Aparecer()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Asteroide Aparecer")));
	
	ubicacionAsteroide = FVector(2000.0f, -700.0f, 200.0f);
	rotacionObstaculo = FRotator(0.0f, 180.0f, 0.0f);

	for (int i = 0; i < 8; i++)
	{
		FVector PosicionInicialAsteroide = FVector(ubicacionAsteroide.X, ubicacionAsteroide.Y + i * 200, ubicacionAsteroide.Z);
		AAsteroide* asteroide = GetWorld()->SpawnActor<AAsteroide>(PosicionInicialAsteroide, rotacionObstaculo);
	}
}

void AAsteroide::RotarAleatoriamente()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Asteroide RotarAleatoriamente")));
	// Rotar el asteroide cada frame
	FRotator RotacionActual = GetActorRotation();
	RotacionActual.Roll += VelocidadRotacion * GetWorld()->GetDeltaSeconds();
	SetActorRotation(RotacionActual);
}
void AAsteroide::Dividirse()
{
	// Crear varios asteroides pequeños
	const int NumAsteroidesPequenios = 3;  // Por ejemplo, dividir en 3 asteroides pequeños

	for (int i = 0; i < NumAsteroidesPequenios; ++i)
	{
		// Calcular posición y rotación para los asteroides pequeños
		FVector PosicionInicial = GetActorLocation() + FVector(FMath::RandRange(-50.0f, 50.0f), FMath::RandRange(-50.0f, 50.0f), FMath::RandRange(-50.0f, 50.0f));
		FRotator Rotacion = FRotator(FMath::RandRange(-180.0f, 180.0f), FMath::RandRange(-180.0f, 180.0f), FMath::RandRange(-180.0f, 180.0f));

		// Spawn del asteroide pequeño
		AAsteroidePequenio* AsteroidePequenio = GetWorld()->SpawnActor<AAsteroidePequenio>(PosicionInicial, Rotacion);
	}
}

void AAsteroide::Mover()
{
	// Mover el asteroide hacia abajo en el eje X
	FVector NuevaPosicion = GetActorLocation() + (DireccionMovimiento * Velocidad * GetWorld()->GetDeltaSeconds());
	SetActorLocation(NuevaPosicion);

	if (NuevaPosicion.X < -2200.0f)
	{
		Destroy();
	}
}

void AAsteroide::RecibirDanio()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Asteroide Destruirse")));
	EnergiaObstaculo -= 10.0f;
	if (EnergiaObstaculo <= 0.0f)
	{
		Dividirse(); // Al destruirse, dividir en asteroides pequeños
		Destroy();
	}
}

void AAsteroide::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor != this)
	{
		// Verifica si el otro actor es el jugador
		ATemplate_MathedPruebPawn* PlayerPawn = Cast<ATemplate_MathedPruebPawn>(OtherActor);
		if (PlayerPawn)
		{
			// Destruye la nave del jugador y la nave NPC
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, FString::Printf(TEXT("NaveDestruida")));
			PlayerPawn->Destroy();
			Destroy();
		}
	}
}

