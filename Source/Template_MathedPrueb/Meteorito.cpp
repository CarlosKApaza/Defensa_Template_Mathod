// Fill out your copyright notice in the Description page of Project Settings.


#include "Meteorito.h"
#include "Particles/ParticleSystemComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Template_MathedPruebPawn.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AMeteorito::AMeteorito()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("StaticMesh'/Game/TwinStick/Meshes/Shape_Meteorito.Shape_Meteorito'"));
	MeshObstaculo = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshObstaculo"));
	MeshObstaculo->SetStaticMesh(Mesh.Object);
	RootComponent = MeshObstaculo; // Establecer el componente raíz del obstáculo


	/**/ // podemos comentar esto para evitar errores
	// Inicializa el componente de sistema de partículas
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Fire.P_Fire'"));
	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComponent"));
	ParticleSystemComponent->SetupAttachment(MeshObstaculo);/**/


	escalaObstaculo = FVector(2.0f, 2.0f, 2.0f);
	MeshObstaculo->SetWorldScale3D(escalaObstaculo);

	EnergiaObstaculo = 10.0f;
	Velocidad = 2500.0f;

	// Inicializa la dirección de movimiento hacia abajo en el eje Z
	DireccionMovimiento = FVector(-1.0f, 0.0f, 0.0f);
	VelocidadRotacion = 80.0f; // Grados por segundo


	// Configura la colisión para que llame a OnHit cuando ocurra una colisión
	MeshObstaculo->SetNotifyRigidBodyCollision(true);
	MeshObstaculo->BodyInstance.SetCollisionProfileName("BlockAll");
	MeshObstaculo->OnComponentHit.AddDynamic(this, &AMeteorito::OnHit);
}

void AMeteorito::BeginPlay()
{
	Super::BeginPlay();
	// Temporizador para aparecer el meteorito
	GetWorldTimerManager().SetTimer(aparecerMeteorito, this, &AMeteorito::Aparecer, 6.0f, true);
}

void AMeteorito::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// llamamos a los metodos en el tick para que se ejecuten cada frame
	Mover();
	RotarAleatoriamente();
	CambiarTamanio();
}

void AMeteorito::Aparecer()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, FString::Printf(TEXT("Meteorito Aparecer")));

	ubicacionMeteorito = FVector(2000.0f, -1850.0f, 250.0f);
	rotacionObstaculo = FRotator(0.0f, 180.0f, 0.0f);

	for (int i = 0; i < 2; i++)
	{
		FVector PosicionInicialMeteorito = FVector(ubicacionMeteorito.X, ubicacionMeteorito.Y + i * 3850, ubicacionMeteorito.Z);
		AMeteorito* meteorito = GetWorld()->SpawnActor<AMeteorito>(PosicionInicialMeteorito, rotacionObstaculo);
		// Establecer direcciones de movimiento diferentes para cada meteorito
		if (meteorito)
		{
			if (i == 0)
			{
				meteorito->DireccionMovimiento = FVector(-1.0f, 1.0f, 0.0f); // Izquierda
			}
			else
			{
				meteorito->DireccionMovimiento = FVector(-1.0f, -1.0f, 0.0f); // Derecha
			}
		}
	}
}

void AMeteorito::RotarAleatoriamente()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, FString::Printf(TEXT("Meteorito RotarAleatoriamente")));
	// Rotar el asteroide cada frame 
	FRotator RotacionActual = GetActorRotation();
	RotacionActual.Roll += VelocidadRotacion * GetWorld()->GetDeltaSeconds();
	SetActorRotation(RotacionActual);
}

void AMeteorito::CambiarTamanio()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, FString::Printf(TEXT("Meteorito CambiarTamanio")));
	// Cambiar el tamaño del meteorito aleatoriamente
	float EscalaAleatoria = FMath::RandRange(0.5f, 3.0f);
	FVector NuevaEscala = FVector(EscalaAleatoria, EscalaAleatoria, EscalaAleatoria);
	MeshObstaculo->SetWorldScale3D(NuevaEscala);
}

void AMeteorito::Mover()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, FString::Printf(TEXT("Meteorito Mover")));
	// Mover el asteroide hacia abajo en el eje X
	FVector NuevaPosicion = GetActorLocation() + (DireccionMovimiento * Velocidad * GetWorld()->GetDeltaSeconds());
	SetActorLocation(NuevaPosicion);

	if (NuevaPosicion.X <= -2200.0f || NuevaPosicion.X >= 2000.0f)
	{
		Velocidad = -Velocidad;
	}
	/*if (NuevaPosicion.X < -2200.0f) 	{  Destroy();  }*/
}

void AMeteorito::RecibirDanio()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, FString::Printf(TEXT("Meteorito Destruirse")));

	EnergiaObstaculo -= 10.0f;
	if (EnergiaObstaculo <= 0.0f)
	{
		Destroy();
	}
}

void AMeteorito::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor != this)
	{
		// Verifica si el otro actor es el jugador
		ATemplate_MathedPruebPawn* PlayerPawn = Cast<ATemplate_MathedPruebPawn>(OtherActor);
		if (PlayerPawn)
		{
			// Destruye la nave del jugador y la nave NPC
			PlayerPawn->Destroy();
			Destroy();
		}
	}
}

