//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "DetectarAtaqueJogador.h"
#include "DevLopBeatEmUp/Personagens/Jogador/Jogador_Base.h"

void UDetectarAtaqueJogador::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animacao,
                                         float DuracaoTotal)
{
	AJogador_Base* Jogador = Cast<AJogador_Base>(MeshComp->GetOwner());
	if (IsValid(Jogador))
	{
		Jogador->ComboAtivo = true;
		Jogador->PermiteCombo = false;
		Jogador->AlteraLocalAttachPersonagem();
	}
}

void UDetectarAtaqueJogador::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animacao,
	float FrameExecSegundo)
{

}

void UDetectarAtaqueJogador::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animacao)
{
	AJogador_Base* Jogador = Cast<AJogador_Base>(MeshComp->GetOwner());
	if (IsValid(Jogador))
	{
		if (Jogador->IndexCombo < 5 && Jogador->Estado == NoChaoAndando)
		{
			Jogador->IndexCombo++;
		}
		if (Jogador->IndexCombo > 4 && Jogador->Estado == NoChaoAndando)
		{
			Jogador->IndexCombo = 0;
		}
		Jogador->ComboAtivo = false;
		Jogador->Acao = Nada;
		Jogador->DesabilitaColisaoDanoPersonagem();
	}
}
