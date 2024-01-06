//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "DevLopBeatEmUp/Personagens/Jogador/Jogador_Base.h"
#include "GameFramework/Actor.h"
#include "GameFramework/CharacterMovementComponent.h"


void AJogador_Base::DefinePadroes()
{
	MeshesPlayer.Init("4", 4);
	AnimacaoPlayer.Init("4", 4);
	
	MeshesPlayer[0] = TEXT("SkeletalMesh'/Game/Personagens/Estagiario/Estagiario.Estagiario'");
	MeshesPlayer[1] = TEXT("SkeletalMesh'/Game/Personagens/Pleno/Sporty_Granny.Sporty_Granny'");
	MeshesPlayer[2] = TEXT("SkeletalMesh'/Game/Personagens/Senior/Swat.Swat'");
	MeshesPlayer[3] = TEXT("SkeletalMesh'/Game/Personagens/Chefe/The_Boss.The_Boss'");
	
	CaminhoArma = TEXT("SkeletalMesh'/Game/Personagens/Arma/Arma.Arma'");

	AnimacaoPlayer[0] = TEXT("AnimBlueprint'/Game/Personagens/Estagiario/Estagiario_AnimBlueprint.Estagiario_AnimBlueprint_C'");
	AnimacaoPlayer[1] = TEXT("AnimBlueprint'/Game/Personagens/Pleno/Pleno_AnimBlueprint.Pleno_AnimBlueprint_C'");
	AnimacaoPlayer[2] = TEXT("AnimBlueprint'/Game/Personagens/Senior/Senior_AnimBlueprint.Senior_AnimBlueprint_C'");
	AnimacaoPlayer[3] = TEXT("AnimBlueprint'/Game/Personagens/Chefe/Chefe_AnimBlueprint.Chefe_AnimBlueprint_C'");


	Estagiario_Anim = Cast<UClass>(StaticLoadObject(UClass::StaticClass(),NULL, *AnimacaoPlayer[0]));
	Pleno_Anim = Cast<UClass>(StaticLoadObject(UClass::StaticClass(),NULL, *AnimacaoPlayer[1]));
	Senior_Anim = Cast<UClass>(StaticLoadObject(UClass::StaticClass(),NULL, *AnimacaoPlayer[2]));
	Chefe_Anim = Cast<UClass>(StaticLoadObject(UClass::StaticClass(),NULL, *AnimacaoPlayer[3]));

	GetCharacterMovement()->AirControl = 1;
	GetCharacterMovement()->AirControlBoostMultiplier = 10;
	GetCharacterMovement()->AirControlBoostVelocityThreshold = 100;
	DesabilitaColisaoDanoPersonagem();
	ColisaoDanoCombo->OnComponentBeginOverlap.AddDynamic(this, &AJogador_Base::InicioDanoColisao);
	ColisaoDanoCombo->OnComponentEndOverlap.AddDynamic(this, &AJogador_Base::FimDanoColisao);
}

void AJogador_Base::VerificaMeshPersonagem(float Index)
{
	if (IsValid(Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(),NULL, *MeshesPlayer[Index]))) &&
		IsValid(Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(),NULL, *CaminhoArma))))
	{
		GetMesh()->SetSkeletalMesh(
		Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(),NULL, *MeshesPlayer[Index])));
		InicializaAttachPersonagem();
	}	
}
void AJogador_Base::CriaPersonagemConfig()
{	
	GetCapsuleComponent()->InitCapsuleSize(29.0f, 76.0f);
	
	//BaseMesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		MeshContainer(TEXT("SkeletalMesh'/Game/Personagens/Estagiario/Estagiario.Estagiario'"));
	if (MeshContainer.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshContainer.Object);
		GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -75));
		GetMesh()->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
		GetMesh()->SetWorldScale3D(FVector(0.70f, 0.70f, 0.70f));
	}

	//AnimBlueprint
	 static ConstructorHelpers::FObjectFinder<UClass> AnimacaoEncontrada(TEXT("AnimBlueprint'/Game/Personagens/Estagiario/Estagiario_AnimBlueprint.Estagiario_AnimBlueprint_C'"));
	 GetMesh()->SetAnimInstanceClass(AnimacaoEncontrada.Object);

	ColisaoDanoCombo = CreateDefaultSubobject<UBoxComponent>(TEXT("ColisaoCombo"));
}

void AJogador_Base::InicializaAttachPersonagem()
{
	ColisaoDanoCombo->AttachToComponent(GetMesh(),
						FAttachmentTransformRules::SnapToTargetIncludingScale, "MaoDirSoquete");
	ColisaoDanoCombo->SetRelativeLocationAndRotation(FVector(0, 0, 70),
										 FRotator(0, 0, 0), false, false);
	ColisaoDanoCombo->SetVisibility(true);
	ColisaoDanoCombo->bHiddenInGame = true;
	ColisaoDanoCombo->SetWorldScale3D(FVector(0.5, 0.5, 2));
}

void AJogador_Base::AlteraLocalAttachPersonagem()
{
	if (Estado == NoChaoAndando)
	{
		switch (IndexCombo)
		{
		case 0:
			ColisaoDanoCombo->AttachToComponent(GetMesh(),
							FAttachmentTransformRules::SnapToTargetIncludingScale, "MaoEsquerdaSoquete");
			ColisaoDanoCombo->SetRelativeLocationAndRotation(FVector(0, 0, 70),
												 FRotator(0, 0, 0), false, false);
			ColisaoDanoCombo->SetWorldScale3D(FVector(1, 1, 2));
			break;
		case 1:
			ColisaoDanoCombo->AttachToComponent(GetMesh(),
						FAttachmentTransformRules::SnapToTargetIncludingScale, "MaoDirSoquete");
			ColisaoDanoCombo->SetRelativeLocationAndRotation(FVector(0, 0, 70),
												 FRotator(0, 0, 0), false, false);
			ColisaoDanoCombo->SetWorldScale3D(FVector(1, 1, 2));
			break;
		case 2:
			ColisaoDanoCombo->AttachToComponent(GetMesh(),
						FAttachmentTransformRules::SnapToTargetIncludingScale, "MaoDirSoquete");
			ColisaoDanoCombo->SetRelativeLocationAndRotation(FVector(0, 0, 70),
												 FRotator(0, 0, 0), false, false);
			ColisaoDanoCombo->SetWorldScale3D(FVector(1, 1, 2));
			break;
		case 3:
			ColisaoDanoCombo->AttachToComponent(GetMesh(),
						FAttachmentTransformRules::SnapToTargetIncludingScale, "PeEsquerdoSoquete");
			ColisaoDanoCombo->SetRelativeLocationAndRotation(FVector(0, 0, 0),
												 FRotator(0, 0, 0), false, false);
			ColisaoDanoCombo->SetWorldScale3D(FVector(1, 1, 2));
			break;
		case 4:
			ColisaoDanoCombo->AttachToComponent(GetMesh(),
						FAttachmentTransformRules::SnapToTargetIncludingScale, "PeEsquerdoSoquete");
			ColisaoDanoCombo->SetRelativeLocationAndRotation(FVector(0, 0, 0),
												 FRotator(30, 0, 0), false, false);
			ColisaoDanoCombo->SetWorldScale3D(FVector(1, 1, 2));
			break;
		default:
			break;
		}
	}else if (Estado == Caindo)
	{
		ColisaoDanoCombo->AttachToComponent(GetMesh(),
						FAttachmentTransformRules::SnapToTargetIncludingScale, "PeEsquerdoSoquete");
		ColisaoDanoCombo->SetRelativeLocationAndRotation(FVector(0, 0, 0),
											 FRotator(30, 0, 0), false, false);
		ColisaoDanoCombo->SetWorldScale3D(FVector(1, 1, 2));
	}
}

void AJogador_Base::DesabilitaColisaoDanoPersonagem()
{
	ColisaoDanoCombo->SetWorldScale3D(FVector(0, 0, 0));
}
