//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.


#include "LocalVisaoLuta.h"

ALocalVisaoLuta::ALocalVisaoLuta()
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
