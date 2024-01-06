//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#pragma once

#include "CoreMinimal.h"
#include "SpawnNPC.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "DevLopBeatEmUp/Estruturas/Struct.h"
#include "ColisaoTeleport.generated.h"

UCLASS()
class DEVLOPBEATEMUP_API AColisaoTeleport : public AActor
{
	GENERATED_BODY()
	
public:	
	AColisaoTeleport();

	UPROPERTY()
	UBoxComponent* ColisaoReferenciaNPC;

	UPROPERTY(EditAnywhere)
	AActor* LocalTeleport;

	UPROPERTY(EditAnywhere)
	ASpawnNPC* ObjetoSpawn;
	
	UPROPERTY(EditAnywhere)
	FVector Tamanho = FVector(1,1,1);

	UPROPERTY(EditAnywhere)
	ETipoColisao TipoColisao = ETipoColisao::AtivaSpawn;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	ALocalVisaoLuta* LocalVisaoLuta;

	virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
				   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
				   bool bFromSweep, const FHitResult& SweepResult);
};
