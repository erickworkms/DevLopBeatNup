//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "NPC_Base.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AIController.h"
#include "IAControle.h"
#include "UObject/ConstructorHelpers.h"
#include "DevLopBeatEmUp/Personagens/NPC/Plataformas/PontoSpawn.h"
#include "EngineUtils.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "BehaviorTree/BlackboardComponent.h"
#include "DevLopBeatEmUp/PlayerStates/Interfaces/AlteraPlayerStateInterface.h"


ANPC_Base::ANPC_Base()
{
	VerificaPadroes();
}


void ANPC_Base::BeginPlay()
{
	Super::BeginPlay();
	InicializaNPC();
}

void ANPC_Base::ContadorApagaNPC()
{
	FTimerHandle ContadorMorte;
	PontoSpawn->ContadorSpawnAtivos--;
	GetWorldTimerManager().SetTimer(ContadorMorte, this, &ANPC_Base::ApagaNPC, 5, false);
}

void ANPC_Base::ApagaNPC()
{
	Destroy();
}

void ANPC_Base::ResetaNPC()
{
	PodeMovimentar = true;
	Acao = Nada;
}

void ANPC_Base::RecebeDanoTeleportMetodo(ETipoColisao TipoColisao, AActor* Alvo)
{
	UWorld* World = GetWorld();
	check(World);
	
	APontoSpawn* ObjetoEscolhido = nullptr;
		
	FVector Local;
	
	for (TActorIterator<APontoSpawn> It(World); It; ++It)
	{
		if (IsValid(ObjetoEscolhido) && (It->GetDistanceTo(this) < ObjetoEscolhido->GetDistanceTo(this)))
		{
			ObjetoEscolhido = *It;
		}
		else if (!IsValid(ObjetoEscolhido))
		{
			ObjetoEscolhido = *It;
		}
	}
	Local = ObjetoEscolhido->GetActorLocation();
	SetActorLocationAndRotation(FVector(Local.X, Local.Y, Local.Z + 50),
								ObjetoEscolhido->GetActorRotation(), false, nullptr,
								ETeleportType::TeleportPhysics);
}

void ANPC_Base::InicializaNPC()
{
	VariaveisIA_BlackBoard = UAIBlueprintHelperLibrary::GetBlackboard(GetController());
	ControleNPC = Cast<AIAControle>(GetController());
	VerificaLocalPatrulha();
	InicializaAttachPersonagem();
}

void ANPC_Base::InicializaAttachPersonagem()
{
	DanoAtaque->AttachToComponent(GetMesh(),
	                              FAttachmentTransformRules::SnapToTargetIncludingScale, "MaoEsqSoquete");
	GetCharacterMovement()->bUseRVOAvoidance = true;
	GetCharacterMovement()->AvoidanceConsiderationRadius = 500;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	GetCharacterMovement()->MaxSwimSpeed = 600.0f;
	GetCharacterMovement()->AirControl = 0.2f;
	GetCharacterMovement()->SetAvoidanceEnabled(true);
}

void ANPC_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetController())
	{
		DefineEstadoAtual();
		DefinePadroesVel(DeltaTime);
		VerificaVida();
		GerenciaVisaoPersonagemIA();
		if (Vida > 0 && Acao != Queda && Estado == NoChaoAndando)
		{
			VerificaMetodoComportamento();
		}
		if (Acao == Morto && Estado != Caindo)
		{
			GetCharacterMovement()->SetCanEverAffectNavigation(false);
			GetCharacterMovement()->SetAvoidanceEnabled(false);
			GetController()->bBlockInput = true;
			GetController()->UnPossess();

			if (IsValid(InimigoEncontrado))
			{
				InimigoEncontrado = NULL;
			}
			SetActorTickEnabled(false);
		}
	}


}

void ANPC_Base::VerificaVida()
{
	if (Vida <= 0)
	{
		IA_Comportamento = Morto_NPC;
		Acao = Morto;
	}
}

void ANPC_Base::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ANPC_Base::DanoMetodo(AActor* Inimigo)
{
	AJogador_Base* Jogador_Base = Cast<AJogador_Base>(Inimigo);
	if (Vida > 0 && IsValid(Jogador_Base))
	{
		if (InimigoEncontrado == NULL)
		{
			InimigoEncontrado = Inimigo;
			IA_Comportamento = Perseguir_NPC;
		}
		Acao = TomarDano;
		Vida -= 15;
		if (Vida <= 0)
		{
			ContadorApagaNPC();
			Acao = Morto;
			IAlteraPlayerStateInterface* VerPlayerState = Cast<IAlteraPlayerStateInterface>(Jogador_Base->GetPlayerState());
			if (VerPlayerState)
			{
				VerPlayerState->AdicionaMortesZumbiMetodo();
			}
		}
	}
}

void ANPC_Base::DefinePadroesVel(float valor)
{
	if (IA_Comportamento == Perseguir_NPC && Acao != Atacar && PodeMovimentar == true)
	{
		VelocidadeMax = 400;
	}
	else if (PodeMovimentar == false || (Acao == TomarDano || Acao == Morto))
	{
		VelocidadeMax = 0;
	}
	else
	{
		VelocidadeMax = 100;
	}
	GetCharacterMovement()->MaxWalkSpeed = VelocidadeMax;
	Velocidade = GetCapsuleComponent()->GetComponentVelocity().GetAbs().X
		+ GetCapsuleComponent()->GetComponentVelocity().GetAbs().Y;
	Velocidade = FMath::FInterpTo(GetCapsuleComponent()->GetComponentVelocity().Size(),
	                              Velocidade, valor, 10.f);
	if (Vida <= 0.0f)
	{
		Acao = Morto;
		VelocidadeMax = 0;
		GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
		GetCapsuleComponent()->SetCollisionObjectType(ECC_WorldDynamic);
		GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldStatic,ECR_Block);
		ControleNPC->ClearFocus(EAIFocusPriority::Gameplay);
	}
}

void ANPC_Base::VerificaPadroes()
{
	GetCapsuleComponent()->InitCapsuleSize(29.0f, 76.0f);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);

	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -75));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	GetMesh()->SetWorldScale3D(FVector(0.70f, 0.70f, 0.70f));
	GetMesh()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);


	//BaseMesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		MeshContainer(TEXT("SkeletalMesh'/Game/Personagens/Clientes/Mremireh_O_Desbiens.Mremireh_O_Desbiens'"));
	if (MeshContainer.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshContainer.Object);
	}
	AnimacaoPlayer = "AnimBlueprint'/Game/Personagens/Clientes/Clientes_AnimBlueprint.Clientes_AnimBlueprint_C'";
	//AnimBlueprint
	static ConstructorHelpers::FObjectFinder<UClass> AnimacaoEncontrada(*AnimacaoPlayer);
	GetMesh()->SetAnimInstanceClass(AnimacaoEncontrada.Object);

	//floats
	Vida = 100;
	DistanciaCombate = 100;

	//Structs
	Acao = Nada;
	Estado = NoChaoAndando;
	IA_Comportamento = Patrulha_NPC;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	AutoPossessPlayer = EAutoReceiveInput::Disabled;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AIAControle::StaticClass();

	DanoAtaque = CreateDefaultSubobject<UBoxComponent>(TEXT("ColisaoAtaque"));
	DanoAtaque->bFillCollisionUnderneathForNavmesh = false;
	DanoAtaque->bHiddenInGame = false;
	DanoAtaque->SetVisibility(true);
	DanoAtaque->SetCanEverAffectNavigation(false);
	DanoAtaque->SetRelativeLocation(FVector(0.0f, 0.0f, 30.0f));
	DanoAtaque->SetRelativeRotation(FRotator(0, 0, 0));
	DanoAtaque->SetWorldScale3D(FVector(1, 0.5, 2));
	DanoAtaque->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	DanoAtaque->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	DanoAtaque->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	DanoAtaque->OnComponentBeginOverlap.AddDynamic(this, &ANPC_Base::InicioDanoColisao);
	DanoAtaque->OnComponentEndOverlap.AddDynamic(this, &ANPC_Base::FimDanoColisao);
}

void ANPC_Base::DefineEstadoAtual()
{
	if (GetCharacterMovement()->MovementMode == MOVE_Falling)
	{
		Estado = Caindo;
	}
	else if (GetCharacterMovement()->MovementMode == MOVE_Flying)
	{
		Estado = Voando;
	}
	else if (GetCharacterMovement()->MovementMode == MOVE_Walking)
	{
		Estado = NoChaoAndando;
	}
	else
	{
		Estado = NoChaoAndando;
	}
}

void ANPC_Base::VerificaLocalPatrulha()
{
	if (IsValid(VariaveisIA_BlackBoard))
	{
		VariaveisIA_BlackBoard->SetValueAsVector("LocalObjetivo", Objetivos[IndexObjetivo]->GetActorLocation());
	}
}

void ANPC_Base::MoverPersonagemPatrulha(FVector LocalPatrulha)
{
	if (IA_Comportamento == Patrulha_NPC)
	{
		VerificaLocalPatrulha();
		if (FVector::Dist(LocalPatrulha, GetActorLocation()) >= DistanciaCombate)
		{
			ControleNPC->MoveToLocation(LocalPatrulha, 25, true, false,
			                            false, false, 0, false);
			if (FVector::Dist(LocalPatrulha, GetActorLocation()) <= 130 && PodeMovimentar == true)
			{
				PodeMovimentar = false;
				if (IndexObjetivo == 0)
				{
					IndexObjetivo = 1;
				}
				else
				{
					IndexObjetivo = 0;
				}
				FTimerHandle ContadorLocal;
				GetWorldTimerManager().SetTimer(ContadorLocal, this, &ANPC_Base::AtualizaObjetivo, 2, false);
			}
		}
	}
	else if (IA_Comportamento == Perseguir_NPC)
	{
		if (FVector::Dist(InimigoEncontrado->GetActorLocation(), GetActorLocation()) >= DistanciaCombate)
		{
			Acao = Nada;
			VariaveisIA_BlackBoard->SetValueAsEnum("Acao", Acao);
			ControleNPC->MoveToLocation(InimigoEncontrado->GetActorLocation(), 25, false, false,
			                            false, false, 0, false);
			ControleNPC->ClearFocus(EAIFocusPriority::Default);
		}
		else if (FVector::Dist(InimigoEncontrado->GetActorLocation(), GetActorLocation()) <= DistanciaCombate && Acao !=
			Atacar && PodeMovimentar == true)
		{
			PodeMovimentar = false;
			Acao = Atacar;
			VariaveisIA_BlackBoard->SetValueAsEnum("Acao", Acao);
			ControleNPC->SetFocus(InimigoEncontrado);
			FTimerHandle ContadorLocal;
			GetWorldTimerManager().SetTimer(ContadorLocal, this, &ANPC_Base::ResetaNPC, 2, false);
		}
	}
}

void ANPC_Base::VerificaMetodoComportamento()
{
	if (IsValid(ControleNPC))
	{
		if (Estado == NoChaoAndando)
		{
			if (IA_Comportamento == Patrulha_NPC)
			{
				MoverPersonagemPatrulha(VariaveisIA_BlackBoard->GetValueAsVector("LocalObjetivo"));
			}
			if (IA_Comportamento == Perseguir_NPC)
			{
				if (IsValid(InimigoEncontrado))
				{
					MoverPersonagemPatrulha(InimigoEncontrado->GetActorLocation());
				}
			}
		}
		else
		{
			ControleNPC->ClearFocus(EAIFocusPriority::Gameplay);
			GetCharacterMovement()->StopActiveMovement();
			ControleNPC->StopMovement();
			Acao = Nada;
		}
	}
}

void ANPC_Base::GerenciaEscolhaInimigoIA()
{
	AJogador_Base* JogadorPadrao = Cast<AJogador_Base>(InimigoEncontrado);

	if (IsValid(JogadorPadrao))
	{
		VariaveisIA_BlackBoard->SetValueAsObject("Inimigo", JogadorPadrao);
	}
}

void ANPC_Base::GerenciaVisaoPersonagemIA()
{
	if (Vida > 0 && Acao != Queda && Estado == NoChaoAndando)
	{
		if (InimigoEncontrado)
		{
			float AuxDistancia = GetDistanceTo(InimigoEncontrado);
			if (AuxDistancia < 3000)
			{
				VariaveisIA_BlackBoard->SetValueAsFloat("DistanciaObjetivo", AuxDistancia);
				IA_Comportamento = Perseguir_NPC;
				VariaveisIA_BlackBoard->SetValueAsEnum("IA_Comportamento", IA_Comportamento);
			}
			else
			{
				InimigoEncontrado = NULL;
				VariaveisIA_BlackBoard->ClearValue("Inimigo");
				IA_Comportamento = Patrulha_NPC;
				VariaveisIA_BlackBoard->SetValueAsEnum("IA_Comportamento", IA_Comportamento);
			}
		}
	}
	if (IsValid(InimigoEncontrado))
	{
		AJogador_Base* JogadorPadrao = Cast<AJogador_Base>(InimigoEncontrado);
		if (IsValid(JogadorPadrao))
		{
			if (JogadorPadrao->Vida <= 0)
			{
				InimigoEncontrado = NULL;
				ControleNPC->ClearFocus(EAIFocusPriority::Gameplay);
				VariaveisIA_BlackBoard->ClearValue("Inimigo");
				Acao = Nada;
				VariaveisIA_BlackBoard->SetValueAsEnum("Acao", Acao);
				IA_Comportamento = Patrulha_NPC;
				VariaveisIA_BlackBoard->SetValueAsEnum("IA_Comportamento", IA_Comportamento);
			}
		}
	}
}

void ANPC_Base::AtualizaObjetivo()
{
	PodeMovimentar = true;
}
