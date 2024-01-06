
#include "DetectarComecoAtaque.h"
#include "DevLopBeatEmUp/Personagens/NPC/NPC_Base.h"

void UDetectarComecoAtaque::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	ANPC_Base* NPC = Cast<ANPC_Base>(MeshComp->GetOwner());

	if (IsValid(NPC))
	{
		NPC->PodeMovimentar = false;
		NPC->PermiteDano = true;
	}
}
