//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.


#include "ColisaoTeleport.h"
#include "DevLopBeatEmUp/Personagens/Jogador/Interfaces/DanoProjetilInterface.h"

AColisaoTeleport::AColisaoTeleport()
{
	ColisaoReferenciaNPC = CreateDefaultSubobject<UBoxComponent>(TEXT("ReferenciaCamera"));
	ColisaoReferenciaNPC->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ColisaoReferenciaNPC->SetCollisionObjectType(ECC_WorldStatic);
	ColisaoReferenciaNPC->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	ColisaoReferenciaNPC->bHiddenInGame = true;
	ColisaoReferenciaNPC->OnComponentBeginOverlap.AddDynamic(this, &AColisaoTeleport::OnOverlap);

}

void AColisaoTeleport::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	ColisaoReferenciaNPC->SetWorldScale3D(Tamanho);
}
void AColisaoTeleport::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
								 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
								 bool bFromSweep, const FHitResult& SweepResult)
{
	// Verificar se o OtherActor é o jogador
	IDanoProjetilInterface* ActorEncontrado = Cast<IDanoProjetilInterface>(OtherActor);
	if (ActorEncontrado)
	{
		if (TipoColisao == ETipoColisao::Teleport)
		{
			ActorEncontrado->RecebeDanoTeleportMetodo(TipoColisao,LocalTeleport);
			Destroy();
		}
		else
		{
			ActorEncontrado->RecebeDanoTeleportMetodo(TipoColisao,this);
		}
		
	}
}