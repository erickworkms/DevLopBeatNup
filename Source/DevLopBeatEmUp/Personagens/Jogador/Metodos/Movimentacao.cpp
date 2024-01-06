//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "Components/SkeletalMeshComponent.h"
#include "DevLopBeatEmUp/Personagens/Jogador/Jogador_Base.h"
#include "Kismet/KismetMathLibrary.h"

void AJogador_Base::MoverFrente(float valor)
{
	if (valor != 0)
	{
		if (Acao != Queda && Acao != Morto)
		{
			FVector Lado = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y) *-1;
			AddMovementInput(Lado, valor);
		}
	}
}

void AJogador_Base::MoverLado(float valor)
{
	if (valor != 0)
	{
		if (Acao != Queda && Acao != Morto)
		{
			FVector Lado = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
			AddMovementInput(Lado, valor);
		}
	}
}
