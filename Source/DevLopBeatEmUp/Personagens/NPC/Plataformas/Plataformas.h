// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "Plataformas.generated.h"

UCLASS()
class DEVLOPBEATEMUP_API APlataformasNPC : public AActor
{
	GENERATED_BODY()
	
public:	

	APlataformasNPC();
	
	UPROPERTY()
	UStaticMeshComponent* LocalReferenciaNPC;

	UPROPERTY(EditAnywhere)
	AActor* Plataforma;

	UPROPERTY(EditAnywhere)
	bool TemLoop = false;
	
	UPROPERTY(EditAnywhere)
	bool EstaAtivo = false;

	UPROPERTY(EditAnywhere)
	float Descanso;

	UPROPERTY(EditAnywhere)
	float DistanciaFinalObjetivo;
	
	UPROPERTY(EditAnywhere)
	FVector LocalInicial;

	UPROPERTY(EditAnywhere)
	FVector LocalFinal;

	UFUNCTION()
	void AtivaPlataforma(bool SetTemLoop,bool SetEstaAtivo);


protected:
	
	int ObjetivoContador = 0;
	
	virtual void BeginPlay() override;

	UFUNCTION()
	void MoverPlataforma(float Valor);

	bool ChegouObjetivoA = false;
	
	bool ChegouObjetivoB = false;
	
	float DescansoAtivo = 0;

	FVector DestinoAtual;

	UPROPERTY(VisibleAnywhere)
	UTimelineComponent* TimelineComp;

	virtual void Tick(float DeltaSeconds) override;
};
