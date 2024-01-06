//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#pragma once

#include "CoreMinimal.h"
#include "DevLopBeatEmUp/Huds/BaseHudMenuPrincipal.h"
#include "GameFramework/PlayerController.h"
#include "MenuPrincipalController.generated.h"

/**
 * 
 */
UCLASS()
class DEVLOPBEATEMUP_API AMenuPrincipalController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	ABaseHudMenuPrincipal* Hud;
protected:
	virtual void BeginPlay() override;

};
