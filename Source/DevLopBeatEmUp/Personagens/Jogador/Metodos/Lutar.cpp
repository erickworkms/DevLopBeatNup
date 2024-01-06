//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "DevLopBeatEmUp/Personagens/Jogador/Jogador_Base.h"
#include "GameFramework/CharacterMovementComponent.h"

void AJogador_Base::Combo_Pressionado()
{
	if (ComboAtivo == false && StaminaFinalizada == false && PermiteCombo == true)
	{
		if (IndexCombo == 0)
		{
			StaminaCombo = 100;
		}
		else if (StaminaCombo <= 0)
		{
			IndexCombo = 0;
		}
		else
		{
			StaminaCombo += 10;
		}
		ComboAtivo = true;
		PermiteCombo = false;
		Acao = Atacar;
		
		ValorStamina -= VelocidadeCombo * 20;
		if (ValorStamina <= 0.0f)
		{
			StaminaFinalizada = true;
		}
	}
}

void AJogador_Base::Combo_Solto()
{
	PermiteCombo = true;
}
