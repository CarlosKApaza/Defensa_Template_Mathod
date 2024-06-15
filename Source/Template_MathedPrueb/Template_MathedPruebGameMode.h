// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Template_MathedPruebGameMode.generated.h"

UCLASS(MinimalAPI)
class ATemplate_MathedPruebGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATemplate_MathedPruebGameMode();

protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;

public:
	// Referencias a las clases concretas del Template Method
	class AAsteroide* asteroide;
	class ANavesNPC* naveNPC;
	class AMeteorito* meteorito;


	FVector ubicacionAsteroide;
	FVector ubicacionNaveNPC;
	FVector ubicacionMeteorito;

	FRotator rotacionObstaculo = FRotator(0.0f, 180.0f, 0.0f);
};



