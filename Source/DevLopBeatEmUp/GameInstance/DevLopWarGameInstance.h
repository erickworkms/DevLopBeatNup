//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "DevLopWarGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class DEVLOPBEATEMUP_API UDevLopWarGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY()
	APlayerController* ControleJogador;
};
