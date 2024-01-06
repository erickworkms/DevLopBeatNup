//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "DevLopBeatEmUp/Personagens/Jogador/Jogador_Base.h"
#include "GameFramework/CharacterMovementComponent.h"

void AJogador_Base::DefinePadroesVel(float valor)
{
	if (Acao == Atacar && IndexCombo < 4)
	{
		VelocidadeMax = 100;

		if (PermiteCombo == true && StaminaFinalizada)
		{
			ValorStamina += 1;
			if (ValorStamina >= 99)
			{
				StaminaFinalizada = false;
			}
		}
	}
	else if (Acao == Atacar && IndexCombo >= 4)
	{
		VelocidadeMax = 1500;

		if (PermiteCombo == true && StaminaFinalizada)
		{
			ValorStamina += 1;
			if (ValorStamina >= 99)
			{
				StaminaFinalizada = false;
			}
		}
	}
	else if (Acao == TomarDano || Acao == Morto)
	{
		VelocidadeMax = 0;

		if (PermiteCombo == true && StaminaFinalizada)
		{
			ValorStamina += 1;
			if (ValorStamina >= 99)
			{
				StaminaFinalizada = false;
			}
		}
	}
	else
	{
		if (StaminaFinalizada)
		{
			ValorStamina += 1;
			if (ValorStamina >= 99)
			{
				StaminaFinalizada = false;
			}
		}
		VelocidadeMax = 600;
	}
	if (StaminaCombo > 0)
	{
		StaminaCombo -= 0.1;
		if (StaminaCombo <= 0)
		{
			IndexCombo = 0;
			ComboAtivo = false;
			PermiteCombo = true;
			Acao = Nada;
		}
	}
	GetCharacterMovement()->MaxWalkSpeed = VelocidadeMax;
	PersonagemSeMovimenta = (GetCapsuleComponent()->GetComponentVelocity().GetAbs().X
		+ GetCapsuleComponent()->GetComponentVelocity().GetAbs().Y) > 0;
	Velocidade = GetCapsuleComponent()->GetComponentVelocity().GetAbs().X
		+ GetCapsuleComponent()->GetComponentVelocity().GetAbs().Y;
	Velocidade = FMath::FInterpTo(GetCapsuleComponent()->GetComponentVelocity().Size(),
	                              Velocidade, valor, 10.f);

	ApontamentoZControle = FMath::FInterpTo(ApontamentoZControle,
	                                        GetCharacterMovement()->GetLastUpdateVelocity().Z, valor, 10.f);
	if (Vida <= 0.0f)
	{
		Acao = Morto;
	}
}