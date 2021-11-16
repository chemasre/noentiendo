#include "NoEntiendo.hpp"

#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <process.h>
#define MAX_RUTA 200
#define MAX_LINEA 200
#define MAX_CADENA 200
#define NOMBRE_LIBRERIA "NoEntiendo"
#define RUTA_RECURSOS "Recursos/"
#define RUTA_TIPOS_TILE "Tiles/"
#define RUTA_MUSICAS "Musicas/"
#define RUTA_SPRITES "Sprites/"
#define RUTA_DECORADOS "Decorados/"

#define VERSION "1.2"

struct Configuracion
{
	int bpp = 32;
	int tamanyoTile = 16;
	int anchoPantalla = 800;
	int altoPantalla = 400;
	int pantallaCompleta = 0;
	int anchoTilemaps = 20;
	int altoTilemaps  = 20;
	int numTiposTile = 32;
	int numTilemaps = 3;
	int numSprites = 32;
	int numDecorados = 8;
	int numMusicas = 8;
	int tiempoMinimoActualizacion = 10;
};

sfRenderWindow* ventana;
sfImage* 		icono;	
sfSprite**		tiposTile;
int***			tilemaps;
int**           colisionMap;
sfMusic**		musicas;
sfClock*		timer;
sfSprite**		sprites;
sfSprite**		decorados;
sfColor         colorLimpiar;

int tiempoDesdeActualizacion;

int camaraX = 0;
int camaraY = 0;

Configuracion configuracion;

bool NOE_EstaEnTilemap(int x, int y);
void NOE_RellenaAreaTilemap(int capa, int posicionX, int posicionY, int ancho, int alto, int tipoBloque);
void NOE_RellenaTilemap(int tilemap, int tipoBloque);
bool NOE_Inicia()
{
	printf("----------------------------------------------\n");
	printf("  %s Version %s\n", NOMBRE_LIBRERIA, VERSION);
	printf("----------------------------------------------\n");
	printf("\n");

	// Iniciar configuracion

	configuracion = Configuracion();

	char linea1[MAX_LINEA];
	char linea2[MAX_LINEA];
	FILE* f = fopen("configuracion.txt","r");
	char* r = 0;

	do
	{
		r = fgets(linea1, MAX_LINEA, f);

		if(r != 0)
		{
			// Trim line

			int j = 0;
			for(int i = 0; i < strlen(linea1); i ++)
			{
				if(linea1[i] != ' ' && linea1[i] != '\t' && linea1[i] != '\n')
				{
					linea2[j] = toupper(linea1[i]);
					j ++;
				}
			}

			linea2[j] = 0;

			//printf("Trimeada \"%s\"\n", linea2);

			if(strlen(linea2) == 0)
			{
				// Skip line
				//printf("Linea vacia\n");
			}
			else if(linea2[0] == '#')
			{
				// Skip line
				//printf("Comentario\n");
			}
			else
			{
				// Parse line

				char parte1[MAX_LINEA];
				char parte2[MAX_LINEA];

				int j = 0;
				int foundSeparator = 0;
				for(int i = 0; i < strlen(linea2); i++)
				{
					if(!foundSeparator)
					{
						if(linea2[i] == ':')
						{
							//printf("Separador\n");
							foundSeparator = 1;
							parte1[j] = 0;
							j = 0;
						}
						else
						{
							//printf("Copiando1\n");
							parte1[j] = linea2[i];
							j ++;
						}
					}
					else
					{
						//printf("Copiando2\n");
						parte2[j] = linea2[i];
						j ++;
					}
					
				}

				parte2[j] = 0;

				//printf("Parseada => \"%s\" : \"%s\"\n", parte1, parte2);

				if(strcmp(parte1, "TAMANYOTILE") == 0)
				{
					configuracion.tamanyoTile = atoi(parte2);
				}
				else if(strcmp(parte1, "ANCHOTILEMAPS") == 0)
				{
					configuracion.anchoTilemaps = atoi(parte2);
				}
				else if(strcmp(parte1, "ALTOTILEMAPS") == 0)
				{
					configuracion.altoTilemaps = atoi(parte2);
				}
				else if(strcmp(parte1, "ANCHOPANTALLA") == 0)
				{
					configuracion.anchoPantalla = atoi(parte2);
				}
				else if(strcmp(parte1, "ALTOPANTALLA") == 0)
				{
					configuracion.altoPantalla = atoi(parte2);
				}
				else if(strcmp(parte1, "PANTALLACOMPLETA") == 0)
				{
					configuracion.pantallaCompleta = atoi(parte2);
				}
				
			}

			

		}



	} while(r > 0);

	fclose(f);

	printf("Configuracion:\n");
	printf("\n");
	printf("  anchoPantalla..... %d pixels\n", configuracion.anchoPantalla);
	printf("  altoPantalla...... %d pixels\n", configuracion.altoPantalla);
	printf("  pantallaCompleta.. %d\n", configuracion.pantallaCompleta);
	printf("  tamanyoTile....... %d pixels\n", configuracion.tamanyoTile);
	printf("  anchoTilemaps..... %d tiles\n", configuracion.anchoTilemaps);
	printf("  altoTilemaps...... %d tiles\n", configuracion.altoTilemaps);
	printf("  numTilemaps....... %d\n", configuracion.numTilemaps);
	printf("  numSprites........ %d\n", configuracion.numSprites);
	printf("  numDecorados...... %d\n", configuracion.numDecorados);
	printf("  numMusicas........ %d\n", configuracion.numMusicas);
	printf("\n");

	// Iniciar pantalla

	Configuracion &c = configuracion;
	
    sfVideoMode mode = { (unsigned int)(c.anchoPantalla),
	                     (unsigned int)(c.altoPantalla),
						 (unsigned int)(c.bpp) };


	char titulo[MAX_CADENA];

	sprintf(titulo, "%s Version %s", NOMBRE_LIBRERIA, VERSION);

	int style = sfTitlebar;
	if(configuracion.pantallaCompleta) { style |= sfFullscreen; }
	
    ventana = sfRenderWindow_create(mode, titulo, style, NULL);
    if(!ventana) { return false; }
	
	colorLimpiar = sfColor_fromRGB(0, 0, 0);

	
	char ruta[MAX_RUTA];
	sprintf(ruta, "%s%s", RUTA_RECURSOS, "icono.png");
	
	icono = sfImage_createFromFile(ruta);
	
	sfRenderWindow_setIcon(ventana, sfImage_getSize(icono).y, sfImage_getSize(icono).y, sfImage_getPixelsPtr(icono));
	
	// Cargar recursos
	
	tiposTile = new sfSprite*[c.numTiposTile];
	
	for(int i = 0; i < c.numTiposTile; i ++)
	{
		sfTexture* texture;
		
		sprintf(ruta, "%s%s%03d.png", RUTA_RECURSOS, RUTA_TIPOS_TILE, i);
		texture = sfTexture_createFromFile(ruta, NULL);

		tiposTile[i] = sfSprite_create();
		sfSprite_setTexture(tiposTile[i], texture, sfTrue);
		
	}
	
	sprites = new sfSprite*[c.numSprites];
	
	for(int i = 0; i < c.numSprites; i ++)
	{
		sfTexture* texture;
		
		sprintf(ruta, "%s%s%03d.png", RUTA_RECURSOS, RUTA_SPRITES, i);
		texture = sfTexture_createFromFile(ruta, NULL);

		sprites[i] = sfSprite_create();
		sfSprite_setTexture(sprites[i], texture, sfTrue);
		
	}
	
	decorados = new sfSprite*[c.numDecorados];
	
	for(int i = 0; i < c.numDecorados; i ++)
	{
		sfTexture* texture;
		
		sprintf(ruta, "%s%s%02d.png", RUTA_RECURSOS, RUTA_DECORADOS, i);
		texture = sfTexture_createFromFile(ruta, NULL);

		decorados[i] = sfSprite_create();
		sfSprite_setTexture(decorados[i], texture, sfTrue);
		
	}
	
	musicas = new sfMusic*[c.numMusicas];
	
	for(int i = 0; i < c.numMusicas; i ++)
	{
		sprintf(ruta, "%s%s%02d.wav", RUTA_RECURSOS, RUTA_MUSICAS, i);
		musicas[i] = sfMusic_createFromFile(ruta);
		
	}	
		
	// Iniciar tilemaps
	
	tilemaps = new int**[c.numTilemaps];
	
	for(int t = 0; t < c.numTilemaps; t++)
	{
		tilemaps[t] = new int *[c.altoTilemaps];
		
		for(int y = 0; y < c.altoTilemaps; y ++)
		{
			tilemaps[t][y] = new int[c.anchoTilemaps];
			
			for(int x = 0; x < c.anchoTilemaps; x ++)
			{
				tilemaps[t][y][x] = noeTipoTileVacio;
			}
		}
		
	}

	// Iniciar colision

	colisionMap = new int*[c.altoTilemaps];
	
	for(int y = 0; y < c.altoTilemaps; y ++)
	{
		colisionMap[y] = new int[c.anchoTilemaps];
		
		for(int x = 0; x < c.anchoTilemaps; x ++)
		{
			colisionMap[y][x] = noeColisionVacia;
		}
	}

	// Iniciar generador numeros aleatorios
	
	srand(getpid());

	// Iniciar timer

	timer = sfClock_create();
	tiempoDesdeActualizacion = 0;

		
	return true;
	
}

void NOE_Actualiza()
{
	// Procesar eventos de ventana
	
	sfEvent event;
	
	while (sfRenderWindow_pollEvent(ventana, &event))
	{
		/* Close ventana : exit */
		//if (event.type == sfEvtClosed)
		//	sfRenderWindow_close(ventana);
	}
	
	// Actualizar reloj
	
	sfTime t = sfClock_getElapsedTime(timer);
	tiempoDesdeActualizacion = sfTime_asMilliseconds(t);
	
	if(tiempoDesdeActualizacion > configuracion.tiempoMinimoActualizacion)
	{
		tiempoDesdeActualizacion = sfTime_asMilliseconds(t);
		sfClock_restart(timer);
	}
	else
	{
		tiempoDesdeActualizacion = 0;
	}
	
	
}


void NOE_Finaliza()
{
	Configuracion &c = configuracion;

	// Liberar recursos

	for(int i = 0; i < c.numMusicas; i ++) { sfMusic_destroy(musicas[i]); }
	delete musicas;

	// Liberar timer

	sfClock_destroy(timer);
	
	sfRenderWindow_destroy(ventana);
	sfImage_destroy(icono);
		
	
}

void NOE_Espera(int tiempo)
{
	sfTime t = sfMilliseconds(tiempo);
	sfSleep(t);
	
}

int NOE_ObtenTiempoDesdeActualizacion()
{
	return tiempoDesdeActualizacion;
}

int NOE_ObtenNumeroAleatorio(int minimo, int maximo)
{
	return minimo + rand() % (maximo - minimo + 1);
}

sfKeyCode codigosTecla[] = 
{
	sfKeyA,
	sfKeyB,
	sfKeyC,
	sfKeyD,
	sfKeyE,
	sfKeyF,
	sfKeyG,
	sfKeyH,
	sfKeyI,
	sfKeyJ,
	sfKeyK,
	sfKeyL,
	sfKeyM,
	sfKeyN,
	sfKeyO,
	sfKeyP,
	sfKeyQ,
	sfKeyR,
	sfKeyS,
	sfKeyT,
	sfKeyU,
	sfKeyV,
	sfKeyW,
	sfKeyX,
	sfKeyY,
	sfKeyZ,
	sfKeySpace,
	sfKeyEscape,
    sfKeyLeft, 
    sfKeyRight,
    sfKeyUp,   
    sfKeyDown, 
};

bool NOE_ObtenTeclaPulsada(NOE_Tecla tecla)
{
	return sfKeyboard_isKeyPressed(codigosTecla[tecla]);
}

int NOE_ConviertePantallaAMundoX(int x)
{
	return x + camaraX;
}

int NOE_ConviertePantallaAMundoY(int y)
{
	return y + camaraY;
}

int NOE_ConvierteMundoAPantallaX(int x)
{
	return x - camaraX;
}

int NOE_ConvierteMundoAPantallaY(int y)
{
	return y - camaraY;
}

int NOE_ConvierteMundoATileX(int x)
{
	Configuracion &c = configuracion;
	return x / c.tamanyoTile;
}

int NOE_ConvierteMundoATileY(int y)
{
	Configuracion &c = configuracion;
	return y / c.tamanyoTile;
}

int NOE_ConvierteTileAMundoX(int x)
{
	Configuracion &c = configuracion;
	return x * c.tamanyoTile;
}

int NOE_ConvierteTileAMundoY(int y)
{
	Configuracion &c = configuracion;
	return y * c.tamanyoTile;
}

int NOE_ObtenPosicionRatonX()
{
	Configuracion &c = configuracion;
	return sfMouse_getPosition((const sfWindow*)ventana).x;
}

int NOE_ObtenPosicionRatonY()
{
	Configuracion &c = configuracion;	
	return sfMouse_getPosition((const sfWindow*)ventana).y;
}

bool NOE_ObtenBotonRaton()
{
	return sfMouse_isButtonPressed(sfMouseLeft);
}

int NOE_ObtenPosicionCamaraX()
{
	return camaraX;
}

int NOE_ObtenPosicionCamaraY()
{
	return camaraY;
}

void NOE_PonPosicionCamara(int x, int y)
{
	camaraX = x;
	camaraY = y;
}

void NOE_DibujaSprite(int sprite, int x, int y, int ancho, int alto, bool invertirX, bool invertirY)
{
	sfSprite* sprite2 = sprites[sprite];
	
	
	const sfTexture* textura = sfSprite_getTexture(sprite2);
	sfVector2u tamanyo = sfTexture_getSize(textura);

	sfVector2f escala = { (invertirX ? -1: 1) * (float)ancho / tamanyo.x, (invertirY ? -1: 1) * (float)alto / tamanyo.y  };
	sfSprite_setScale(sprite2, escala);

	sfVector2f position = { (invertirX ? 1 : 0) * ancho + (float)x - camaraX, (invertirY ? 1 : 0) * alto+ (float)y - camaraY };
	sfSprite_setPosition(sprite2, position);

	sfRenderWindow_drawSprite(ventana, sprite2, NULL);
	
}

void NOE_DibujaDecorado(int decorado)
{
	Configuracion &c = configuracion;	

	sfSprite* decorado2 = decorados[decorado];
		
	const sfTexture* textura = sfSprite_getTexture(decorado2);
	sfVector2u tamanyo = sfTexture_getSize(textura);

		
	sfVector2f escala = { (float) c.anchoPantalla / tamanyo.x, (float) c.altoPantalla  / tamanyo.y  };
	sfSprite_setScale(decorado2, escala);

	sfVector2f position = { 0, 0 };
	sfSprite_setPosition(decorado2, position);

	sfRenderWindow_drawSprite(ventana, decorado2, NULL);
	
}


void NOE_ReproduceMusica(int musica)
{
	Configuracion &c = configuracion;		
	for(int i = 0; i < c.numMusicas; i ++) { sfMusic_stop(musicas[i]); }
	sfMusic_setLoop(musicas[musica], true);
	sfMusic_play(musicas[musica]);
}

void NOE_ParaMusica()
{
	Configuracion &c = configuracion;	
	for(int i = 0; i < c.numMusicas; i ++) { sfMusic_stop(musicas[i]); }		
}


// Métodos privados
bool NOE_EstaEnTilemap(int posicionX, int posicionY)
{
	Configuracion &c = configuracion;	
	return posicionX >= 0 && posicionX < c.anchoTilemaps && posicionY >= 0 && posicionY < c.altoTilemaps;
}

void NOE_RellenaAreaTilemap(int tilemap, int posicionX, int posicionY, int ancho, int alto, int tipoBloque)
{
	for(int y = 0; y < alto; y++)
	{
		for(int x = 0; x < ancho; x++)
		{
			if(NOE_EstaEnTilemap(posicionX + x, posicionY + y))
			{
				tilemaps[tilemap][posicionY + y][posicionX + x] = tipoBloque;
			}
		}
	}

}

void NOE_RellenaTilemap(int tilemap, int tipoBloque)
{
	Configuracion &c = configuracion;	
	NOE_RellenaAreaTilemap(tilemap, 0, 0, c.anchoTilemaps, c.altoTilemaps, tipoBloque);
}

void NOE_LimpiaTilemap(int tilemap, int tile)
{
	NOE_RellenaTilemap(tilemap, tile);
}


void NOE_PonTile(int tilemap, int posicionX, int posicionY, int tipo)
{
	if(NOE_EstaEnTilemap(posicionX, posicionY))
	{
		tilemaps[tilemap][posicionY][posicionX] = tipo;
	}
}

int NOE_ObtenTile(int tilemap, int posicionX, int posicionY)
{
	if(NOE_EstaEnTilemap(posicionX, posicionY))
	{
		return tilemaps[tilemap][posicionY][posicionX];
	}
	else
	{
		return noeTipoTileVacio;
	}
}

int NOE_ObtenAnchoTilemap()
{
	return configuracion.anchoTilemaps;
}

int NOE_ObtenAltoTilemap()
{
	return configuracion.altoTilemaps;
}

void NOE_LimpiaPantalla(int r, int g, int b)
{
	sfColor color = sfColor_fromRGB(r,g,b);									
   sfRenderWindow_clear(ventana, color);
}

void NOE_DibujaFondo(int fondo)
{
}

void NOE_DibujaTilemap(int indice)
{
	Configuracion &c = configuracion;

	for(int y = 0; y < c.altoTilemaps; y++)
	{
		for(int x = 0; x < c.anchoTilemaps; x++)
		{
			int tipoTile = tilemaps[indice][y][x];
			if(tipoTile != noeTipoTileVacio)
			{
				sfSprite* sprite = tiposTile[tipoTile];
				
				sfVector2f position = { (float)x * c.tamanyoTile - camaraX, (float)y * c.tamanyoTile  - camaraY };
				sfSprite_setPosition(sprite, position);
				
				const sfTexture* textura = sfSprite_getTexture(sprite);
				sfVector2u tamanyo = sfTexture_getSize(textura);

				sfVector2f escala = { (float)c.tamanyoTile / tamanyo.x, (float)c.tamanyoTile / tamanyo.y  };
				sfSprite_setScale(sprite, escala);

				sfRenderWindow_drawSprite(ventana, sprite, NULL);
			}
		}
	}

}

void NOE_MuestraPantalla()
{
	sfRenderWindow_display(ventana);	
}

