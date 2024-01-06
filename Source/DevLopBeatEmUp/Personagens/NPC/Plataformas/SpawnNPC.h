// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LocalVisaoLuta.h"
#include "ObjetivoNPC.h"
#include "Plataformas.h"
#include "PontoSpawnNPC.h"
#include "Engine/BlockingVolume.h"
#include "GameFramework/Actor.h"
#include "SpawnNPC.generated.h"

UCLASS()
class DEVLOPBEATEMUP_API ASpawnNPC : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpawnNPC();

	UPROPERTY(EditAnywhere)
	int LimiteSpawn = 100;

	UPROPERTY(EditAnywhere)
	int LimiteNPCVivo = 5;

	UPROPERTY(EditAnywhere)
	float ValorSequenciaSpawn = 1;
	
	int ContadorSpawnAtivos = 0;

	UPROPERTY(EditAnywhere)
	APlataformasNPC* Plataforma;
	
	UPROPERTY()
	UStaticMeshComponent* LocalReferenciaNPC;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<AObjetivoNPC*> Objetivos;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<ABlockingVolume*> Bloqueios;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<APontoSpawnNPC*> LocaisSpawn;

	UFUNCTION()
	void AtivaSpawnNPC();


protected:
	FTimerHandle Contador;
		
	int ContadorSpawn = 0;
		
	virtual void BeginPlay() override;

	UFUNCTION()
	void CriaNPC();
	
};
