// Fill out your copyright notice in the Description page of Project Settings.


#include "AsteroidePequenio.h"
#include "Template_MathedPruebPawn.h"
#include "Components/StaticMeshComponent.h"

AAsteroidePequenio::AAsteroidePequenio()
{
	PrimaryActorTick.bCanEverTick = true;

    // Cargar el mesh del asteroide peque�o
    static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("StaticMesh'/Game/TwinStick/Meshes/Shape_Asteroide_2.Shape_Asteroide_2'"));
    MeshObstaculo = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshObstaculo"));
    MeshObstaculo->SetStaticMesh(Mesh.Object);

    // Configurar la escala y otros par�metros del asteroide peque�o
    escalaObstaculo = FVector(0.5f, 0.5f, 0.5f);  // Ejemplo de escala m�s peque�a
    MeshObstaculo->SetWorldScale3D(escalaObstaculo);

    EnergiaObstaculo = 5.0f;  // Menos energ�a que el asteroide grande
    Velocidad = 100.0f;  // Mayor velocidad que el asteroide grande

    DireccionMovimiento = FVector(-1.0f, 0.0f, 0.0f);  // Direcci�n de movimiento

    // Configurar colisi�n y eventos de colisi�n
    MeshObstaculo->SetNotifyRigidBodyCollision(true);
    MeshObstaculo->BodyInstance.SetCollisionProfileName("BlockAll");

    MeshObstaculo->OnComponentHit.AddDynamic(this, &AAsteroidePequenio::OnHit);
}

void AAsteroidePequenio::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAsteroidePequenio::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    Mover();
}

void AAsteroidePequenio::Mover()
{
	FVector NuevaUbicacion = GetActorLocation() + (DireccionMovimiento * Velocidad * GetWorld()->DeltaTimeSeconds);
	SetActorLocation(NuevaUbicacion);
}

void AAsteroidePequenio::RecibirDanio()
{
    EnergiaObstaculo -= 2.0f;  // Menos da�o que el asteroide grande
    if (EnergiaObstaculo <= 0.0f)
    {
        Destroy();
    }
}

void AAsteroidePequenio::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
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

