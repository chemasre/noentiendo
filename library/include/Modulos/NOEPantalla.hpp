#ifndef __NOE_PANTALLA__
#define __NOE_PANTALLA__

namespace NOEPantalla
{
	extern char noeVentanaNombre[];

	bool IniciaPantalla();
	void FinalizaPantalla();

	sfRenderWindow* ObtenVentana();

	// Library funcions
	
	void LimpiaPantalla(int r, int g, int b);
	void MuestraPantalla();
	void PonCursor(int c);
	void PonMostrarCursor(bool mostrar);
	void PonTamanyoCursor(int ancho, int alto);
	void PonDesplazamientoCursor(int x, int y);
}

#endif