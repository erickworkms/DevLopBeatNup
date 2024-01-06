//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "MenuPrincipalGameMode.h"
#include "GameFramework/HUD.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "DevLopBeatEmUp/Controles/MenuPrincipalController.h"
#include "Kismet/GameplayStatics.h"


AMenuPrincipalGameMode::AMenuPrincipalGameMode()
{
	static ConstructorHelpers::FClassFinder<AHUD> PlayerHUDClass(TEXT("/Game/Mapas/BlueprintHudMenuPrincipal"));
	if (PlayerHUDClass.Succeeded())
	{
		HUDClass = PlayerHUDClass.Class;
	}
	PlayerControllerClass = AMenuPrincipalController::StaticClass();
}

void AMenuPrincipalGameMode::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* Controle = UGameplayStatics::GetPlayerController(this, 0);

	if (Controle)
	{
		Controle->bShowMouseCursor = true;
		Controle->DefaultMouseCursor = EMouseCursor::Crosshairs;
		SeuGameInstance = Cast<UDevLopWarGameInstance>(GetWorld()->GetGameInstance());
	}
}

void AMenuPrincipalGameMode::IniciarJogo()
{
	if (IsValid(hudDetectada))
	{
		hudDetectada->IniciarJogo();
	}
}

