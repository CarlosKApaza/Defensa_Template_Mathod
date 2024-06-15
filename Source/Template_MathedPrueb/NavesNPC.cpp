
#include "NavesNPC.h"
#include "Template_MathedPruebPawn.h"
#include "Components/StaticMeshComponent.h"

ANavesNPC::ANavesNPC()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("StaticMesh'/Game/TwinStick/Meshes/Cube_NaveNPC.Cube_NaveNPC'"));
	MeshObstaculo = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshObstaculo"));
	MeshObstaculo->SetStaticMesh(Mesh.Object);
	escalaObstaculo = FVector(1.0f, 1.0f, 1.0f);
	MeshObstaculo->SetWorldScale3D(escalaObstaculo);

	EnergiaObstaculo = 10.0f;
	Velocidad = 100.0f;

	DireccionMovimiento = FVector(0.0f, 1.0f, 0.0f);

	// Configura la colisión para que llame a OnHit cuando ocurra una colisión
	MeshObstaculo->SetNotifyRigidBodyCollision(true);
	MeshObstaculo->BodyInstance.SetCollisionProfileName("BlockAll");
	MeshObstaculo->OnComponentHit.AddDynamic(this, &ANavesNPC::OnHit);

	
	// Inicializa las propiedades de disparo
	GunOffset = FVector(0.f, 90.f, 0.f);
	GunOffset2 = FVector(0.f, -90.f, 0.f);
	FireRate = 3.0f;
	bCanFire = true;
	bShouldFireRight = true;
}

void ANavesNPC::BeginPlay() 
{
	Super::BeginPlay(); 
	// Configura un temporizador para llamar a GenerarObstaculoAleatoria() cada 10 segundos (ajusta el intervalo según tus necesidades)
	//GetWorldTimerManager().SetTimer(FTNavesNPCAleatorios, this, &ANavesNPC::GenerarObstaculoAleatorio, 3.0f, true, 3.0f);
	
}

void ANavesNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Mover();
	Disparar();
}

void ANavesNPC::Aparecer()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan, FString::Printf(TEXT("NaveNPC Aparecer")));

	ubicacionNaveNPC = FVector(2000.0f, -1850.0f, 250.0f); 
	ubicacionNaveNPC2 = FVector(2000.0f, 1850.0f, 250.0f);
	rotacionObstaculo = FRotator(0.0f, 180.0f, 0.0f);

	for (int i = 0; i < 1; i++)
	{
		FVector posicionInicialNPC = FVector(ubicacionNaveNPC.X + i * -500, ubicacionNaveNPC.Y, ubicacionNaveNPC.Z);
		ANavesNPC* NPC = GetWorld()->SpawnActor<ANavesNPC>(posicionInicialNPC, rotacionObstaculo);
	}

	for (int i = 0; i < 1; i++)
	{
		FVector posicionInicialNPC2 = FVector(ubicacionNaveNPC2.X + i * -500, ubicacionNaveNPC2.Y, ubicacionNaveNPC2.Z);
		ANavesNPC* NPC2 = GetWorld()->SpawnActor<ANavesNPC>(posicionInicialNPC2, rotacionObstaculo);
	}
}

void ANavesNPC::GenerarObstaculoAleatorio()
{
	Destroy();

	ubicacionNaveNPCAleatorio = FVector(2000.0f, -1850.0f, 250.0f);
	ubicacionNaveNPC2Aleatorio = FVector(2000.0f, 1850.0f, 250.0f);

	int32 NumNavesIzquierda = FMath::RandRange(3, 15);  // Maximo a la izquierda
	int32 NumNavesDerecha = FMath::RandRange(3, 15); // Maximo a la derecha

	// Generar naves a la izquierda
	for (int i = 0; i < NumNavesIzquierda; ++i)
	{
		// Generar ubicación aleatoria a la izquierda
		FVector PosicionInicialNPC = FVector(ubicacionNaveNPCAleatorio.X + i * -500, ubicacionNaveNPCAleatorio.Y, ubicacionNaveNPCAleatorio.Z);
		// Generar velocidad aleatoria (dirección aleatoria)
		Velocidad = FMath::RandRange(200.0f, 800.0f);  // Velocidad entre 50 y 200 unidades por segundo
		ANavesNPC* NPC = GetWorld()->SpawnActor<ANavesNPC>(PosicionInicialNPC, rotacionObstaculo);
		NPC->Velocidad = Velocidad;
	}

	// Generar naves a la derecha
	for (int i = 0; i < NumNavesDerecha; ++i)
	{
		// Generar ubicación aleatoria a la derecha
		FVector PosicionInicialNPC2 = FVector(ubicacionNaveNPC2Aleatorio.X + i * -500, ubicacionNaveNPC2Aleatorio.Y, ubicacionNaveNPC2Aleatorio.Z);
		// Generar velocidad aleatoria (dirección aleatoria)
		Velocidad = FMath::RandRange(-200.0f, -1000.0f);  // Velocidad entre 50 y 200 unidades por segundo
		ANavesNPC* NPC = GetWorld()->SpawnActor<ANavesNPC>(PosicionInicialNPC2, rotacionObstaculo);
		NPC->Velocidad = Velocidad;
	}
}

void ANavesNPC::Disparar()
{
	if (bCanFire)
	{
		UWorld* World = GetWorld();
		if (World != nullptr)
		{
			// Disparo hacia la derecha o izquierda según el valor de bShouldFireRight
			FRotator FireRotation;
			FVector SpawnLocation;

			if (bShouldFireRight)
			{
				FireRotation = FRotator(0.f, 90.f, 0.f);  // Rotación para disparar hacia la derecha
				SpawnLocation = GetActorLocation() + FireRotation.RotateVector(GunOffset);
			}
			else
			{
				FireRotation = FRotator(0.f, -90.f, 0.f);  // Rotación para disparar hacia la izquierda
				SpawnLocation = GetActorLocation() + FireRotation.RotateVector(GunOffset2);
			}

			World->SpawnActor<ATemplate_MathedPruebProjectile>(SpawnLocation, FireRotation);

			bShouldFireRight = !bShouldFireRight;  // Alternar entre true y false para el próximo disparo
			bCanFire = false;
			World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &ANavesNPC::ShotTimerExpired, FireRate);
		}

	}
}

void ANavesNPC::ShotTimerExpired()
{
	bCanFire = true;
}

void ANavesNPC::Mover()
{
	// Mover el asteroide hacia abajo en el eje X
	FVector NuevaPosicion = GetActorLocation() + (DireccionMovimiento * Velocidad * GetWorld()->GetDeltaSeconds());
	SetActorLocation(NuevaPosicion);

	if (NuevaPosicion.Y <= -2200.0f || NuevaPosicion.Y >= 2000.0f)
	{
		Velocidad = -Velocidad;
	}
}

void ANavesNPC::RecibirDanio()
{
	EnergiaObstaculo -= 10.0f;
	if (EnergiaObstaculo <= 0.0f)
	{
		Destroy();
	}
}

void ANavesNPC::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
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
