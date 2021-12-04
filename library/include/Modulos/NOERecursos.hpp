#ifndef __NOE_RECURSOS__
#define __NOE_RECURSOS__

namespace NOERecursos
{
	typedef sfTexture NOETextura;
	typedef sfSoundBuffer NOEBufferSonido;
	typedef sfMusic NOEMusica;

	typedef NOETextura** NOEFuente;

	enum NOEGrupoTexturas
	{
		NOE_GRUPOTEXTURAS_SPRITES = 0,
		NOE_GRUPOTEXTURAS_TIPOSTILE = 1,
		NOE_GRUPOTEXTURAS_DECORADOS = 2,
		NOE_GRUPOTEXTURAS_TOTAL = 3
		
	};

	const int noeRecursosNumGlifosFuente = 37;

	const char noeRecursosRutaBase[] = "Recursos/";
	const char noeRecursosRutaTiposTile[] = "Tiles/";
	const char noeRecursosRutaMusicas[] = "Musicas/";
	const char noeRecursosRutaSonidos[] = "Sonidos/";
	const char noeRecursosRutaSprites[] = "Sprites/";
	const char noeRecursosRutaDecorados[] = "Decorados/";
	const char noeRecursosRutaFuentes[] = "Fuentes/";
	const char noeRecursosRutaCursores[] = "Cursores/";
	const int noeRecursosMaxRuta = 200;

	void IniciaRecursos();

	NOETextura* ObtenTextura(NOEGrupoTexturas grupo, int indice);
	NOEBufferSonido* ObtenBufferSonido(int indice);
	NOEMusica* ObtenMusica(int indice);

	NOEFuente ObtenFuente(int indice);
}

#endif