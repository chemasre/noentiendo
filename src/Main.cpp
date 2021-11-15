#include "NoEntiendo.hpp"
#include <stdio.h>

#define FPS 30
#define ESPERA ((int)(((float)1/FPS) * 1000))
#define VELOCIDAD 3

int main()
{
	NOE_Inicia();
	
	
	int ciclo = 0;
	int direccionX = 0;
	int direccionY = 0;
	int posicionX = 0;
	int posicionY = 0;

	int direccionCamaraX = 0;
	int direccionCamaraY = 0;
	
	int temporizador = 0;
	
	int musica = 0;
	
	printf("---------------- \n");	
	printf(" Instrucciones   \n");
	printf("---------------- \n");	
	printf("RATON o WASD .. Mover el tile \n");
	printf("ESPACIO........ Cambiar de musica \n");
	printf("ESCAPE ........ Salir \n");
	
	
	NOE_ReproduceMusica(musica);


	while(!NOE_ObtenTeclaPulsada(TECLA_ESCAPE))
	{
		NOE_Actualiza();		

		if(NOE_ObtenTeclaPulsada(TECLA_D))
		{
			direccionX = 1;			
		}
		else if(NOE_ObtenTeclaPulsada(TECLA_A))
		{
			direccionX = -1;
		}
		if(NOE_ObtenTeclaPulsada(TECLA_S))
		{
			direccionY = 1;
		}
		else if(NOE_ObtenTeclaPulsada(TECLA_W))
		{
			direccionY = -1;
		}

		if(NOE_ObtenTeclaPulsada(TECLA_DERECHA))
		{
			direccionCamaraX = 2;			
		}
		else if(NOE_ObtenTeclaPulsada(TECLA_IZQUIERDA))
		{
			direccionCamaraX = -2;
		}
		if(NOE_ObtenTeclaPulsada(TECLA_ABAJO))
		{
			direccionCamaraY = 2;
		}
		else if(NOE_ObtenTeclaPulsada(TECLA_ARRIBA))
		{
			direccionCamaraY = -2;
		}		
		
		if(NOE_ObtenTeclaPulsada(TECLA_ESPACIO))
		{
			if(musica == 0) { NOE_ReproduceMusica(1); musica = 1; }
			else { NOE_ReproduceMusica(0); musica = 0; }
		}		
		
		NOE_PonTile(0, 5, 5, 7);
		
		temporizador = temporizador + NOE_ObtenTiempoDesdeActualizacion();

		if(temporizador > 100)
		{
			posicionX += direccionX;
			posicionY += direccionY;
			
			direccionX = 0;
			direccionY = 0;

			int x = NOE_ObtenPosicionCamaraX();
			int y = NOE_ObtenPosicionCamaraY();

			x += direccionCamaraX;
			y += direccionCamaraY;

			NOE_PonPosicionCamara(x, y);			

			direccionCamaraX = 0;
			direccionCamaraY = 0;

			temporizador = 0;

		}
		
		if(NOE_ObtenBotonRaton())
		{
			int x = NOE_ObtenPosicionRatonX();
			int y = NOE_ObtenPosicionRatonY();
			x = NOE_ConviertePantallaAMundoX(x);
			y = NOE_ConviertePantallaAMundoY(y);
			posicionX = NOE_ConvierteMundoATileX(x);
			posicionY = NOE_ConvierteMundoATileY(y);
			
		}
		
		NOE_PonTile(1, posicionX, posicionY, 1);

		NOE_LimpiaPantalla(20,20,20);
		NOE_DibujaDecorado(0);
		NOE_DibujaTilemap(0);
		NOE_DibujaTilemap(1);
		NOE_DibujaSprite(1, 0, 0, 100, 100, 1, 1);
		NOE_MuestraPantalla();
		
		NOE_PonTile(1, posicionX, posicionY, noeTipoTileVacio);

		ciclo ++;
		
	}
	
	NOE_ParaMusica();
	
	NOE_Finaliza();

    return 0;
}