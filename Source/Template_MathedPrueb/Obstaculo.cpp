// Fill out your copyright notice in the Description page of Project Settings.

#include "Obstaculo.h"

AObstaculo::AObstaculo() {PrimaryActorTick.bCanEverTick = true; }

void AObstaculo::BeginPlay() { Super::BeginPlay(); }

void AObstaculo::Tick(float DeltaTime) { Super::Tick(DeltaTime); }

void AObstaculo::procesarObstaculo()
{
	Aparecer();
	GenerarObstaculoAleatorio();
	RotarAleatoriamente();
	Dividirse();
	CambiarTamanio();
	Disparar();
	ShotTimerExpired();
	Mover();
	RecibirDanio();
}
