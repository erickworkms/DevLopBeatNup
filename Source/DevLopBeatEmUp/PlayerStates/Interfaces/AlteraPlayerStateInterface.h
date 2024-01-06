#pragma once
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AlteraPlayerStateInterface.generated.h"

UINTERFACE(MinimalAPI)
class UAlteraPlayerStateInterface : public UInterface
{
	GENERATED_BODY()
};

class DEVLOPBEATEMUP_API IAlteraPlayerStateInterface
{
	GENERATED_BODY()
public:
	UFUNCTION()
	virtual void AdicionaMortesZumbiMetodo();
	UFUNCTION()
	virtual void AdicionaMortesJogadorMetodo();
};
