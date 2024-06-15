// Fill out your copyright notice in the Description page of Project SettiDestruirs

#pragma once
#include "Obstaculo.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NavesNPC.generated.h"

UCLASS()
class TEMPLATE_MATHEDPRUEB_API ANavesNPC : public AObstaculo
{
	GENERATED_BODY()
	
public:	
	ANavesNPC();

protected: virtual void BeginPlay() override;
public:	virtual void Tick(float DeltaTime) override;

public:
	void Aparecer() override;
	void GenerarObstaculoAleatorio() override;
	void Disparar() override;
	void ShotTimerExpired() override;
	void Mover() override;
	void RecibirDanio() override;

protected:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};
