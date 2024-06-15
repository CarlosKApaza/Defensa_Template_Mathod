// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Template_MathedPruebProjectile.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Obstaculo.generated.h"

UCLASS()
class TEMPLATE_MATHEDPRUEB_API AObstaculo : public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MeshObstaculo; // Malla del Obstaculo

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* ParticleSystemComponent; // Particulas del Obstaculo

	FVector escalaObstaculo;
	FVector posicionInicial;

public:	
	AObstaculo();
protected: virtual void BeginPlay() override;

public:	virtual void Tick(float DeltaTime) override;

public:
	float EnergiaObstaculo;
	float Velocidad;
	FVector ubicacionAsteroide;
	FVector ubicacionMeteorito;
	FVector ubicacionNaveNPC;
	FVector ubicacionNaveNPC2;
	FRotator rotacionObstaculo;
	FVector DireccionMovimiento;
	float VelocidadRotacion;

	FVector ubicacionNaveNPCAleatorio;
	FVector ubicacionNaveNPC2Aleatorio;

	FVector GunOffset;	
	FVector GunOffset2;
	float FireRate;
	FTimerHandle TimerHandle_ShotTimerExpired;
	bool bCanFire;
	bool bShouldFireRight;

	FTimerHandle aparecerMeteorito;
	FTimerHandle FTNavesNPCAleatorios;
	float MoverdeltaTime;
	bool bCanMove = false;

public:
	void procesarObstaculo(); // PATRON TEMPLATE METHOD - METODO PLANTILLA

protected:
	// Metodos de la plantilla (esqueleto) 
	virtual void Aparecer() {}; // Asteroides, Meteoritos y NavesNPC 
	virtual void GenerarObstaculoAleatorio() {}; // Asteroides, Meteoritos y NavesNPC
	virtual void RotarAleatoriamente() {}; // Meteoritos y Asteroides
	virtual void Dividirse() {}; // Asteroides
	virtual void CambiarTamanio() {}; // Meteoritos
	virtual void Disparar() {}; // NavesNPC
	virtual void ShotTimerExpired() {};
	virtual void Mover() PURE_VIRTUAL(AObstaculo::Mover, ); // Asteroides, Meteoritos y NavesNPC
	virtual void RecibirDanio() PURE_VIRTUAL(AObstaculo::Morir, ); // Asteroides, Meteoritos y NavesNPC

	// patron terminado
};


