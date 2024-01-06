#pragma once

#include "Struct.generated.h"

UENUM(BlueprintType)
enum class ETime : uint8
{
	Clientes,
	Agil,
	Cascade,
	Nenhum
};

UENUM(BlueprintType)
enum class ETipoColisao : uint8
{
	EvitaQueda,
	Teleport,
	AtivaSpawn,
	FinalizaFase,
	Nenhum
};
