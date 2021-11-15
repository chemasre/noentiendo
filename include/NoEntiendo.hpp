#ifndef NOENTIENDO_HPP
#define NOENTIENDO_HPP

// Constantes

const int tipoTileVacio    = 0;
const int colisionVacia    = 0;

// Enums

enum NOE_Sistema
{
	SISTEMA_MUNDO,
	SISTEMA_PANTALLA,
	SISTEMA_TILE
};

enum NOE_Tecla
{
	TECLA_A,
	TECLA_B,
	TECLA_C,
	TECLA_D,
	TECLA_E,
	TECLA_F,
	TECLA_G,
	TECLA_H,
	TECLA_I,
	TECLA_J,
	TECLA_K,
	TECLA_L,
	TECLA_M,
	TECLA_N,
	TECLA_O,
	TECLA_P,
	TECLA_Q,
	TECLA_R,
	TECLA_S,
	TECLA_T,
	TECLA_U,
	TECLA_V,
	TECLA_W,
	TECLA_X,
	TECLA_Y,
	TECLA_Z,
	TECLA_ESPACIO,
	TECLA_ESCAPE,
	TECLA_IZQUIERDA,
	TECLA_DERECHA,
	TECLA_ARRIBA,
	TECLA_ABAJO,
	
	
};

// Bucle de juego

bool NOE_Inicia();
void NOE_Actualiza();
void NOE_Finaliza();

// Pantalla

void NOE_LimpiaPantalla(int r, int g, int b);
void NOE_MuestraPantalla();


// Camara

int NOE_ObtenPosicionCamaraX();
int NOE_ObtenPosicionCamaraY();
void NOE_PonPosicionCamara(int x, int y);


// Tilemaps

int NOE_ObtenTile(int tilemap, int posicionX, int posicionY);
void NOE_PonTile(int tilemap, int posicionX, int posicionY, int tile);
void NOE_LimpiaTilemap(int tilemap, int tile);
void NOE_DibujaTilemap(int numTilemap);

// Sprites

void NOE_DibujaSprite(int sprite, int x, int y, int ancho, int alto, bool invertirX, bool invertirY);

// Tiempo

void NOE_Espera(int tiempo);
int NOE_ObtenTiempoDesdeActualizacion();

// Aleatoriedad

int NOE_ObtenNumeroAleatorio(int minimo, int maximo);

// Cambios de coordenadas

int NOE_ConviertePantallaAMundoX(int x);
int NOE_ConviertePantallaAMundoY(int y);
int NOE_ConvierteMundoAPantallaX(int x);
int NOE_ConvierteMundoAPantallaY(int y);
int NOE_ConvierteMundoATileX(int x);
int NOE_ConvierteMundoATileY(int y);
int NOE_ConvierteTileAMundoX(int x);
int NOE_ConvierteTileAMundoY(int y);


// Entrada

bool NOE_ObtenTeclaPulsada(NOE_Tecla tecla);
int  NOE_ObtenPosicionRatonX();
int  NOE_ObtenPosicionRatonY();
bool NOE_ObtenBotonRaton();

// Audio

void NOE_ReproduceMusica(int musica);
void NOE_ParaMusica();


#endif

