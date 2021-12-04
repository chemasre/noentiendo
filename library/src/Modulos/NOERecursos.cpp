#include "Modulos/NOEComun.hpp"

namespace NOERecursos
{
	NOETextura** texturas[NOE_GRUPOTEXTURAS_TOTAL];

	NOEFuente* fuentes;

	NOEBufferSonido**		buffersSonido;
	NOEMusica**		musicas;
	



	void IniciaRecursos()
	{
		char ruta[noeRecursosMaxRuta];
		Configuracion & c = ObtenConfiguracion();
		
		texturas[NOE_GRUPOTEXTURAS_SPRITES] = new NOETextura*[c.numSprites];
		
		for(int i = 0; i < c.numSprites; i ++)
		{
			
			sprintf(ruta, "%s%s%03d.png", noeRecursosRutaBase, noeRecursosRutaSprites, i);
			texturas[NOE_GRUPOTEXTURAS_SPRITES][i] = sfTexture_createFromFile(ruta, NULL);	
		}
		
		texturas[NOE_GRUPOTEXTURAS_TIPOSTILE] = new NOETextura*[c.numTiposTile];
		
		for(int i = 0; i < c.numTiposTile; i ++)
		{
			sprintf(ruta, "%s%s%03d.png", noeRecursosRutaBase, noeRecursosRutaTiposTile, i);
			texturas[NOE_GRUPOTEXTURAS_TIPOSTILE][i] = sfTexture_createFromFile(ruta, NULL);
			
		}
		
		texturas[NOE_GRUPOTEXTURAS_DECORADOS] = new NOETextura*[c.numDecorados];
		
		for(int i = 0; i < c.numDecorados; i ++)
		{
			
			sprintf(ruta, "%s%s%02d.png", noeRecursosRutaBase, noeRecursosRutaDecorados, i);
			texturas[NOE_GRUPOTEXTURAS_DECORADOS][i] = sfTexture_createFromFile(ruta, NULL);
			
		}
		
		fuentes	= new NOEFuente[c.numFuentes];
		
		for(int i = 0; i < c.numFuentes; i ++)
		{
			fuentes[i] = new sfTexture*[noeRecursosNumGlifosFuente];
			
			for(int j = 0; j < noeRecursosNumGlifosFuente; j ++)
			{
				sprintf(ruta, "%s%s%02d/%02d.png", noeRecursosRutaBase, noeRecursosRutaFuentes, i, j);
				fuentes[i][j] = sfTexture_createFromFile(ruta, NULL);

			}
		}	
		
	
		buffersSonido = new NOEBufferSonido*[c.numSonidos];
		
		for(int i = 0; i < c.numSonidos; i ++)
		{
			sprintf(ruta, "%s%s%03d.wav", noeRecursosRutaBase, noeRecursosRutaSonidos, i);
			buffersSonido[i] = sfSoundBuffer_createFromFile(ruta);
			
		}

		musicas = new sfMusic*[c.numMusicas];
		
		for(int i = 0; i < c.numMusicas; i ++)
		{
			sprintf(ruta, "%s%s%02d.wav", noeRecursosRutaBase, noeRecursosRutaMusicas, i);
			musicas[i] = sfMusic_createFromFile(ruta);
			
		}		
			

		
	}


	void FinalizaRecursos()
	{
		Configuracion &c = ObtenConfiguracion();
		for(int i = 0; i < c.numSonidos; i ++) { sfSoundBuffer_destroy(buffersSonido[i]); }
		delete buffersSonido;
		
		for(int i = 0; i < c.numMusicas; i ++) { sfMusic_destroy(musicas[i]); }
		delete musicas;		
	}

	NOETextura* ObtenTextura(NOEGrupoTexturas grupo, int indice)
	{
		return texturas[grupo][indice];
	}

	NOEBufferSonido* ObtenBufferSonido(int indice)
	{
		return buffersSonido[indice];	
	}

	NOEMusica* ObtenMusica(int indice)
	{
		return musicas[indice];
	}
	
	NOEFuente ObtenFuente(int indice)
	{
		return fuentes[indice];
	}
	
	

}