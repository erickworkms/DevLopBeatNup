//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "DetectarDano.h"
#include "DevLopBeatEmUp/Personagens/Jogador/Jogador_Base.h"
#include "DevLopBeatEmUp/Personagens/NPC/NPC_Base.h"

void UDetectarDano::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animacao,
                                float DuracaoTotal)
{
	AJogador_Base* Jogador = Cast<AJogador_Base>(MeshComp->GetOwner());
	ANPC_Base* NPC = Cast<ANPC_Base>(MeshComp->GetOwner());
	if (IsValid(Jogador))
	{
		Jogador->Acao = TomarDano;
	}
	else if (NPC)
	{
		NPC->Acao = TomarDano;
	}
}


void UDetectarDano::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animacao)
{
	AJogador_Base* Jogador = Cast<AJogador_Base>(MeshComp->GetOwner());
	ANPC_Base* NPC = Cast<ANPC_Base>(MeshComp->GetOwner());
	if (IsValid(Jogador))
	{
		Jogador->ComboAtivo = false;
		Jogador->PermiteCombo = true;
		Jogador->IndexCombo = 0;
		Jogador->Acao = Nada;
	}
	else if (NPC)
	{
		NPC->Acao = Nada;
	}
}
