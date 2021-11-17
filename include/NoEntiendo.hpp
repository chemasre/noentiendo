#ifndef NOENTIENDO_HPP
#define NOENTIENDO_HPP

// Constantes

const int noeTipoTileVacio    = 0;
const int noeColisionVacia    = 0;

// Enums

enum NOE_Sistema
{
	SISTEMA_MUNDO,
	SISTEMA_PANTALLA,
	SISTEMA_TILE
};

enum NOE_Tecla
{
	NOE_TECLA_ESPACIO,
	NOE_TECLA_A,
	NOE_TECLA_B,
	NOE_TECLA_C,
	NOE_TECLA_D,
	NOE_TECLA_E,
	NOE_TECLA_F,
	NOE_TECLA_G,
	NOE_TECLA_H,
	NOE_TECLA_I,
	NOE_TECLA_J,
	NOE_TECLA_K,
	NOE_TECLA_L,
	NOE_TECLA_M,
	NOE_TECLA_N,
	NOE_TECLA_O,
	NOE_TECLA_P,
	NOE_TECLA_Q,
	NOE_TECLA_R,
	NOE_TECLA_S,
	NOE_TECLA_T,
	NOE_TECLA_U,
	NOE_TECLA_V,
	NOE_TECLA_W,
	NOE_TECLA_X,
	NOE_TECLA_Y,
	NOE_TECLA_Z,
	NOE_TECLA_1,
	NOE_TECLA_2,
	NOE_TECLA_3,
	NOE_TECLA_4,
	NOE_TECLA_5,
	NOE_TECLA_6,
	NOE_TECLA_7,
	NOE_TECLA_8,
	NOE_TECLA_9,
	NOE_TECLA_0,
	NOE_TECLA_ESCAPE,
	NOE_TECLA_IZQUIERDA,
	NOE_TECLA_DERECHA,
	NOE_TECLA_ARRIBA,
	NOE_TECLA_ABAJO,
	NOE_TECLA_ENTRAR,
	NOE_TECLA_BORRA_ATRAS
	
};

// Bucle de juego

bool NOE_Inicia();
void NOE_Actualiza();
void NOE_Finaliza();

// Pantalla

void NOE_LimpiaPantalla(int r, int g, int b);
void NOE_MuestraPantalla();

// Entrada

const char *NOE_ObtenEntrada();
void NOE_LimpiaEntrada();


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

// Decorados

void NOE_DibujaDecorado(int decorado);

// Texto

void NOE_DibujaCaracter(char caracter, int x, int y, int ancho, int alto, int font);
void NOE_DibujaTexto(const char texto[], int x, int y, int anchoCaracter, int altoCaracter, int font);

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
bool NOE_ObtenTeclaArriba(NOE_Tecla tecla);
bool NOE_ObtenTeclaAbajo(NOE_Tecla tecla);
int  NOE_ObtenPosicionRatonX();
int  NOE_ObtenPosicionRatonY();
bool NOE_ObtenBotonRaton();


// Audio

void NOE_ReproduceMusica(int musica, int volumen, int pitch);
void NOE_ParaMusica();

int NOE_ReproduceSonido(int sonido, int volumen, int pitch);
void NOE_ParaSonido(int canal);




#endif

