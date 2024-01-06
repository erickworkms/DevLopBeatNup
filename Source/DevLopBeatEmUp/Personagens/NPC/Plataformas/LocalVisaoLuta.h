//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LocalVisaoLuta.generated.h"

UCLASS()
class DEVLOPBEATEMUP_API ALocalVisaoLuta : public AActor
{
	GENERATED_BODY()
	
public:	
	ALocalVisaoLuta();

	UPROPERTY()
	UStaticMeshComponent* LocalReferenciaNPC;
};
