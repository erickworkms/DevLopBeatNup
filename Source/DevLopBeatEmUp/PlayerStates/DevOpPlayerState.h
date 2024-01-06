// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "Interfaces/AlteraPlayerStateInterface.h"
#include "DevOpPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class DEVLOPBEATEMUP_API ADevOpPlayerState : public APlayerState, public IAlteraPlayerStateInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	int GetNumMortesZumbies() const;
	UFUNCTION()
	void SetNumMortesZumbies();
	UFUNCTION(BlueprintCallable)
	int GetNumMortesPlayer() const;
	UFUNCTION()
	void SetNumMortesPlayer();
	virtual void AdicionaMortesZumbiMetodo() override;
	virtual void AdicionaMortesJogadorMetodo() override;

private:
	UPROPERTY()
	int NumMortesZumbies = 0;

	UPROPERTY()
	int NumMortesPlayer = 0;
};
