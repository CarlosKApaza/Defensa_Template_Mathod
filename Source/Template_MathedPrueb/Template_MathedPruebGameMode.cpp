// Copyright Epic Games, Inc. All Rights Reserved.

#include "Template_MathedPruebGameMode.h"
#include "Template_MathedPruebPawn.h"
#include "Kismet/GameplayStatics.h"
/*-----------------------Abstract Obstaculo-----------------------*/
#include "Obstaculo.h"
/*-----------------Clases Concretas del TemplateMehtod-----------------------*/
#include "Asteroide.h"
#include "NavesNPC.h"
#include "Meteorito.h"

ATemplate_MathedPruebGameMode::ATemplate_MathedPruebGameMode()
{
	DefaultPawnClass = ATemplate_MathedPruebPawn::StaticClass();
	PrimaryActorTick.bCanEverTick = true;
}

void ATemplate_MathedPruebGameMode::BeginPlay()
{
	Super::BeginPlay();
// Spawnwamos los obstaculos al mundo

	asteroide = GetWorld()->SpawnActor<AAsteroide>(ubicacionAsteroide, rotacionObstaculo);
	asteroide->procesarObstaculo(); // Llamamos al metodo plantilla para ejecutar metodos para el objeto

	meteorito = GetWorld()->SpawnActor<AMeteorito>(ubicacionMeteorito, rotacionObstaculo);
	meteorito->procesarObstaculo();

	naveNPC = GetWorld()->SpawnActor<ANavesNPC>(ubicacionNaveNPC, rotacionObstaculo);
	naveNPC->procesarObstaculo();
}

void ATemplate_MathedPruebGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
