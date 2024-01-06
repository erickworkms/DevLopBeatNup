// Fill out your copyright notice in the Description page of Project Settings.


#include "PontoSpawn.h"

// Sets default values
APontoSpawn::APontoSpawn()
{
	LocalReferenciaNPC = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ReferenciaCamera"));
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> referencia(
			TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	if (referencia.Succeeded())
	{
		LocalReferenciaNPC->SetStaticMesh(referencia.Object);
		LocalReferenciaNPC->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		LocalReferenciaNPC->SetCollisionObjectType(ECC_WorldStatic);
		LocalReferenciaNPC->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		LocalReferenciaNPC->bHiddenInGame = true;
	}
}
