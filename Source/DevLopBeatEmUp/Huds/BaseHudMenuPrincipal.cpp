//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.


#include "BaseHudMenuPrincipal.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

ABaseHudMenuPrincipal::ABaseHudMenuPrincipal()
{
}

void ABaseHudMenuPrincipal::IniciarJogo()
{
	UWorld* World = GetWorld();
	check(World);

	UGameplayStatics::OpenLevel(World, "/Game/Mapas/MapaJogavel", true);
}
