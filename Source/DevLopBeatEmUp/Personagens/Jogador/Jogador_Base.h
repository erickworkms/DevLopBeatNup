//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DevLopBeatEmUp/Personagens/Enums/Lista_Enums.h"
#include "DevLopBeatEmUp/Personagens/NPC/Plataformas/LocalVisaoLuta.h"
#include "Interfaces/DanoProjetilInterface.h"
#include "Jogador_Base.generated.h"

UCLASS()
class DEVLOPBEATEMUP_API AJogador_Base : public ACharacter, public IDanoProjetilInterface
{
	GENERATED_BODY()

	UPROPERTY()
	USpringArmComponent* SpringArm;
	UPROPERTY()
	UCameraComponent* CameraPrincipal;
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* ColisaoDanoCombo;
	UPROPERTY()
	UStaticMeshComponent* LocalReferenciaCamera;

public:

	AJogador_Base();
	
	UPROPERTY()
	FTimerHandle ProjetilTemporizador;

	UPROPERTY()
	TArray<FString> MeshesPlayer;
	UPROPERTY()
	TArray<FString> AnimacaoPlayer;
	UPROPERTY()
	FString CaminhoArma;

	UPROPERTY(BlueprintReadOnly,Category="Variaveis")
	float Vida = 100;
	UPROPERTY()
	float Velocidade;
	UPROPERTY()
	float AnguloCorpo;
	UPROPERTY()
	float AnguloCameraX;
	UPROPERTY()
	float AnguloCameraY;
	UPROPERTY()
	float Direcao;
	UPROPERTY()
	float VelTempAnimacao;
	UPROPERTY()
	float ApontamentoZControle = 0.f;
	
	UPROPERTY(meta=(BlueprintProtected = "true"))
	float VelocidadeCombo = 0.2f;
	UPROPERTY(BlueprintReadOnly,Category="Variaveis")
	float ValorStamina = 100.0f;
	UPROPERTY(BlueprintReadOnly,Category="Variaveis")
	float StaminaCombo = 0.0f;
	UPROPERTY(BlueprintReadOnly,Category="Variaveis")
	float TempoCombo = 0;
	UPROPERTY()
	float QuantidadeDano = 0.0f;
	UPROPERTY()
	float VelocidadeMax = 1000;
	UPROPERTY()
	float RotacaoMira;

	UPROPERTY()
	TEnumAsByte<TipoEstado> Estado = NoChaoAndando;
	UPROPERTY()
	TEnumAsByte<TipoAcao> Acao = Nada;
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category="Personagem")
	TEnumAsByte<TipoPersonagem> PersonagemNPC = Estagiario;

	UPROPERTY()
	UClass* Estagiario_Anim;
	UPROPERTY()
	UClass* Pleno_Anim;
	UPROPERTY()
	UClass* Senior_Anim;
	UPROPERTY()
	UClass* Chefe_Anim;

	UPROPERTY()
	bool BloqueiaContador = true;
	UPROPERTY()
	bool PersonagemSeMovimenta;
	UPROPERTY()
	bool Mirar = false;
	UPROPERTY()
	bool PermiteCombo = true;
	UPROPERTY()
	bool StaminaFinalizada = false;
	UPROPERTY()
	bool ComboAtivo = false;
	UPROPERTY()
	int IndexCombo = 0;

	UPROPERTY()
	FVector LocalSocketArma;

	UPROPERTY()
	FRotator RotacaoSocketArma;
	
	void CarregarAssetsPersonagem();

	void VerificaEscolhaPersonagem();
	
	void VerificaMeshPersonagem(float Index);
	
	void AlteraLocalAttachPersonagem();
	
	void DesabilitaColisaoDanoPersonagem();

protected:
	virtual void BeginPlay() override;
	
	void MoverFrente(float valor);
	
	void MoverLado(float valor);
	
	void VirarCameraLado(float valor);

	void DefinePadroesVel(float valor);

	//Botões apertados
	void VerificaPulo_Pressionado();
	void VerificaPulo_Solto();
	void Combo_Pressionado();
	void Combo_Solto();
	
	void Interagir_Pressionado();
	void Interagir_Solto();
	void Permite_Combo();

	//Metodos
	void DefinePadroes();

	void DefineEstadoAtual();
	void CriaCameraConfig();
	void CriaPersonagemConfig();
	void InicializaAttachPersonagem();
	
	void CriaProjetil();

public:

	virtual void Tick(float DeltaTime) override;
	
	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
		
	virtual void ReativarCameraFollow();
	
	virtual void RecebeDanoNPCMetodo() override;

	virtual void RecebeDanoTeleportMetodo(ETipoColisao TipoColisao,AActor* Alvo) override;

	UFUNCTION()
	void InicioDanoColisao(UPrimitiveComponent* OverlappedComp, AActor* InimigoDetectado,
						   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
						   const FHitResult& SweepResult)
	{
		if (Acao == Atacar && InimigoDetectado != this)
		{
			IDanoProjetilInterface* inimigoEncontrado = Cast<IDanoProjetilInterface>(InimigoDetectado);
			if (inimigoEncontrado)
			{
				inimigoEncontrado->DanoMetodo(this);
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
