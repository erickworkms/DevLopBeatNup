//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "DevLopBeatEmUp/Personagens/Enums/Lista_Enums.h"
#include "DevLopBeatEmUp/Personagens/Jogador/Jogador_Base.h"
#include "Plataformas/ObjetivoNPC.h"
#include "Plataformas/SpawnNPC.h"
#include "NPC_Base.generated.h"

UCLASS()
class DEVLOPBEATEMUP_API ANPC_Base : public ACharacter, public IDanoProjetilInterface
{
	GENERATED_BODY()

public:
	ANPC_Base();

	UPROPERTY()
	float Vida = 100;
	UPROPERTY()
	float Velocidade;
	UPROPERTY()
	float VelocidadeMax = 500;
	UPROPERTY()
	float DistanciaCombate = 150;
	UPROPERTY()
	float IndexObjetivo = 0;


	UPROPERTY()
	bool PodeMovimentar = true;

	UPROPERTY()
	bool PermiteDano = false;

	UPROPERTY()
	FTimerHandle ContadorDescanso;

	UPROPERTY()
	TEnumAsByte<TipoEstado> Estado = NoChaoAndando;
	UPROPERTY()
	TEnumAsByte<TipoAcao> Acao = Nada;
	UPROPERTY()
	TEnumAsByte<TipoIAEstado> IA_Comportamento;
	UPROPERTY()
	UBoxComponent* DanoAtaque;
	UPROPERTY()
	AObjetivoNPC* LocalObjetivoPatrulha;

	UPROPERTY()
	AActor* InimigoEncontrado;

	UPROPERTY()
	ASpawnNPC* PontoSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AObjetivoNPC*> Objetivos;

	//Detecta controles e variaveis da IA
	UPROPERTY()
	UBlackboardComponent* VariaveisIA_BlackBoard;
	UPROPERTY()
	AAIController* ControleNPC;

	UPROPERTY()
	FString MeshPlayer;
	UPROPERTY()
	FString AnimacaoPlayer;

	void GerenciaEscolhaInimigoIA();

protected:
	virtual void BeginPlay() override;

	void DefinePadroesVel(float deltatime);

	void VerificaPadroes();

	void VerificaVida();

	void DefineEstadoAtual();

	void VerificaLocalPatrulha();

	void MoverPersonagemPatrulha(FVector LocalPatrulha);

	void VerificaMetodoComportamento();

	void GerenciaVisaoPersonagemIA();

	void AtualizaObjetivo();

public:
	void ContadorApagaNPC();

	void ApagaNPC();

	void ResetaNPC();
	
	virtual void RecebeDanoTeleportMetodo(ETipoColisao TipoColisao, AActor* Alvo) override;

	void InicializaNPC();

	void InicializaAttachPersonagem();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void DanoMetodo(AActor* Inimigo) override;

	UFUNCTION()
	void InicioDanoColisao(UPrimitiveComponent* OverlappedComp, AActor* InimigoDetectado,
	                       UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                       const FHitResult& SweepResult)
	{
		if (Acao == Atacar && InimigoDetectado != this && PermiteDano == true)
		{
			IDanoProjetilInterface* inimigoEncontrado = Cast<IDanoProjetilInterface>(InimigoDetectado);
			if (inimigoEncontrado)
			{
				inimigoEncontrado->RecebeDanoNPCMetodo();
			}
		}
	}

	UFUNCTION()
	void FimDanoColisao(UPrimitiveComponent* OverlappedComp, AActor* InimigoDetectado,
	                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
	{
		// ResetaSaidaColisao(InimigoDetectado);
	}
};
