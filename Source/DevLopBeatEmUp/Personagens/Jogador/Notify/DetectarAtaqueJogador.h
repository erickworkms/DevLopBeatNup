//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "DetectarAtaqueJogador.generated.h"

/**
 * 
 */
UCLASS()
class DEVLOPBEATEMUP_API UDetectarAtaqueJogador : public UAnimNotifyState
{
	GENERATED_BODY()

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp,
	UAnimSequenceBase* Animacao, float DuracaoTotal) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp,
		UAnimSequenceBase* Animacao, float FrameExecSegundo) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp,
		UAnimSequenceBase* Animacao) override;
};
