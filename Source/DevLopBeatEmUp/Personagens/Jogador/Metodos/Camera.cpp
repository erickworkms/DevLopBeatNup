//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "DevLopBeatEmUp/Personagens/Jogador/Jogador_Base.h"
#include "Kismet/GameplayStatics.h"


void AJogador_Base::VirarCameraLado(float valor)
{
	if (Acao != Morto)
	{
		FVector2D MouseScreenPosition;
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

		PlayerController->GetMousePosition(MouseScreenPosition.X, MouseScreenPosition.Y);
		int32 ViewportSizeX, ViewportSizeY;
		PlayerController->GetViewportSize(ViewportSizeX, ViewportSizeY);
		AnguloCameraY = ((MouseScreenPosition.Y / ViewportSizeY) * 2.0f - 1.0f) * -1;
	}
}

void AJogador_Base::CriaCameraConfig()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;

	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	GetCharacterMovement()->MaxSwimSpeed = 1000.0f;
	GetCharacterMovement()->AirControl = 0.2f;

	//Cria e attacha a camera ao objeto root
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	SpringArm->SetupAttachment(RootComponent);

	SpringArm->bUsePawnControlRotation = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;

	CameraPrincipal = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	CameraPrincipal->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	CameraPrincipal->bUsePawnControlRotation = false;

	SpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 150.0f), FRotator(-35.0f, -90.0f, 0.0f));
	SpringArm->TargetArmLength = 1000.f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 20.0f;

	SpringArm->bDoCollisionTest = false;
	SpringArm->ProbeSize = 15;
	SpringArm->ProbeChannel = ECC_Camera;
	
	AutoPossessPlayer = EAutoReceiveInput::Disabled;
}
