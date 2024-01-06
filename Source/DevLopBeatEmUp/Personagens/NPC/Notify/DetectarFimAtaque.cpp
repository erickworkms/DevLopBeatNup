//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "DetectarFimAtaque.h"
#include "DevLopBeatEmUp/Personagens/Enums/Lista_Enums.h"
#include "DevLopBeatEmUp/Personagens/NPC/NPC_Base.h"

void UDetectarFimAtaque::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	ANPC_Base* NPC = Cast<ANPC_Base>(MeshComp->GetOwner());
	if (IsValid(NPC))
	{
		NPC->PodeMovimentar = true;
		NPC->PermiteDano = false;
		NPC->Acao = Nada;
	}
}
