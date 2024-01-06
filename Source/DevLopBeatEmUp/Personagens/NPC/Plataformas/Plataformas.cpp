// Fill out your copyright notice in the Description page of Project Settings.


#include "Plataformas.h"


APlataformasNPC::APlataformasNPC()
{
	LocalReferenciaNPC = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ReferenciaCamera"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> referencia(
		TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	if (referencia.Succeeded())
	{
		LocalReferenciaNPC->SetStaticMesh(referencia.Object);
		LocalReferenciaNPC->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		LocalReferenciaNPC->SetCollisionResponseToAllChannels(ECR_Ignore);
		LocalReferenciaNPC->SetCollisionObjectType(ECC_WorldStatic);
		LocalReferenciaNPC->bHiddenInGame = true;
	}
	PrimaryActorTick.bCanEverTick = true;
}

void APlataformasNPC::BeginPlay()
{
	Super::BeginPlay();
	if (EstaAtivo)
	{
		void IniciaMovimentacaoPlataforma();
	}
	DestinoAtual =LocalInicial;
}

void APlataformasNPC::AtivaPlataforma(bool SetTemLoop, bool SetEstaAtivo)
{
	EstaAtivo = SetEstaAtivo;
	TemLoop = SetTemLoop;
	Descanso = 0;
	void IniciaMovimentacaoPlataforma();
}

void APlataformasNPC::MoverPlataforma(float Valor)
{
	if (DescansoAtivo > 0)
	{
		DescansoAtivo -= Valor;
		if (DescansoAtivo < Valor)
		{
			DescansoAtivo = 0;
		}
	}
	else if (DescansoAtivo == 0)
	{
		FVector NewLocation = FMath::Lerp(Plataforma->GetActorLocation(), DestinoAtual, Valor);
		if (FVector::Dist(Plataforma->GetActorLocation(),LocalInicial) < DistanciaFinalObjetivo && !ChegouObjetivoA)
		{
			ChegouObjetivoA = true;
			ChegouObjetivoB = false;
			DestinoAtual = LocalFinal;
			DescansoAtivo = Descanso;
			ObjetivoContador++;
		}
		else if (FVector::Dist(Plataforma->GetActorLocation(),LocalFinal) < DistanciaFinalObjetivo && !ChegouObjetivoB)
		{
			ChegouObjetivoA = false;
			ChegouObjetivoB= true;
			DestinoAtual = LocalInicial;
			DescansoAtivo = Descanso;
			ObjetivoContador++;
		}
		if (FVector::Dist(Plataforma->GetActorLocation(),DestinoAtual) > DistanciaFinalObjetivo)
		{
			Plataforma->SetActorLocation(NewLocation);
		}
		
		if ((ChegouObjetivoA || ChegouObjetivoB) && !TemLoop && ObjetivoContador > 1)
		{
			EstaAtivo = false;
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow,"DescansoAtivo" + FString::SanitizeFloat(DescansoAtivo));
	}
}

void APlataformasNPC::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (EstaAtivo)
	{
		MoverPlataforma(DeltaSeconds);
	}
}

