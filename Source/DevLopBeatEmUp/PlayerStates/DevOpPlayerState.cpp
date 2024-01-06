// Fill out your copyright notice in the Description page of Project Settings.


#include "DevOpPlayerState.h"

int ADevOpPlayerState::GetNumMortesZumbies() const
{
	return NumMortesZumbies;
}

void ADevOpPlayerState::SetNumMortesZumbies()
{
	NumMortesZumbies++;
}

int ADevOpPlayerState::GetNumMortesPlayer() const
{
	return NumMortesPlayer;
}

void ADevOpPlayerState::SetNumMortesPlayer()
{
	NumMortesPlayer++;
}

void ADevOpPlayerState::AdicionaMortesZumbiMetodo()
{
	SetNumMortesZumbies();
}

void ADevOpPlayerState::AdicionaMortesJogadorMetodo()
{
	SetNumMortesPlayer();
}
