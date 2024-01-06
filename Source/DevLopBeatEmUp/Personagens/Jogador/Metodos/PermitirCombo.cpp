//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "DevLopBeatEmUp/Personagens/Jogador/Jogador_Base.h"

void AJogador_Base::Permite_Combo()
{
	if (IndexCombo < 4)
	{
		IndexCombo++;
	}
	else
	{
		IndexCombo = 0;
	}
	ComboAtivo = false;
}
