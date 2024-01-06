//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BaseHudMenuPrincipal.generated.h"

/**
 * 
 */
UCLASS()
class DEVLOPBEATEMUP_API ABaseHudMenuPrincipal : public AHUD
{
	GENERATED_BODY()

	ABaseHudMenuPrincipal();
public:
	UFUNCTION(BlueprintCallable)
	void IniciarJogo();
};
