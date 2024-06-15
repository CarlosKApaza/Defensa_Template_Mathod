// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Obstaculo.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AsteroidePequenio.generated.h"

UCLASS()
class TEMPLATE_MATHEDPRUEB_API AAsteroidePequenio : public AObstaculo
{
	GENERATED_BODY()

public:
	AAsteroidePequenio();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	void Mover() override;
	void RecibirDanio() override;

protected:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};
