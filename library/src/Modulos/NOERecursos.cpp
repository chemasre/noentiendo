#include "Modulos/NOEComun.hpp"

namespace NOERecursos
{
	NOETextura** texturas[NOE_GRUPOTEXTURAS_TOTAL];

	NOEFuente* fuentes;

	NOEBufferSonido**		buffersSonido;
	NOEMusica**		musicas;
	
	NOEDatosForma** datosFormas;


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
		
		datosFormas = new NOEDatosForma*[c.numFormas];
		
		for(int i = 0; i < c.numFormas; i ++)
		{
			//printf("Leyendo forma %d\n", i);
			sprintf(ruta, "%s%s%02d.shape", noeRecursosRutaBase, noeRecursosRutaFormas, i);
			NOEDatosForma* datosForma = new NOEDatosForma;
			
			char nombre[noeRecursosMaxLinea];
			char valor[noeRecursosMaxLinea];
			NOERecurso *recurso = AbreRecurso(ruta);
			
			LeePropiedad(recurso, nombre, valor);

			//printf("Leida propiedad %s:%s\n", nombre, valor);
			
			int numPuntos = ObtenLongitudVector(valor) / 2;
			
			//printf("Num puntos es:%d\n", numPuntos);
			
			int* puntos = new int[numPuntos * 2];
			ObtenVector(valor, puntos);
			
			//printf("Los puntos son:\n");
			//for(int j = 0; j < numPuntos; j ++)
			//{
			//	printf("Punto %d,%d\n", puntos[j * 2], puntos[j * 2 + 1]);
			//}
			
			
			
			datosFormas[i] = new NOEDatosForma();
			datosFormas[i]->puntos = puntos;
			datosFormas[i]->numPuntos = numPuntos;
			
			//printf("Leida forma %d\n", i);
			//printf("Num puntos %d\n", datosFormas[i]->numPuntos);
			//for(int j = 0; j < datosFormas[i]->numPuntos; j ++)
			//{
			//	printf("Punto %d,%d\n", datosFormas[i]->puntos[j * 2], datosFormas[i]->puntos[j * 2 + 1]);
			//}
			
			CierraRecurso(recurso);
			
		}		
		

		
	}
	
	NOERecurso* AbreRecurso(const char nombre[])
	{
		NOERecurso* f = fopen(nombre,"r");
		return f;
	}
	
	int ObtenLongitudVector(const char valor[])
	{
		int cuenta;
		cuenta = 0;

		if(strlen(valor) - 2 > 0)
		{ 
			cuenta = 1;
			for(int i = 0; i < strlen(valor); i++)
			{
				if(valor[i] == ',') { cuenta ++; }
			}
		}
		
		return cuenta;

	}
	
	void ObtenVector(const char valor[], int vector[])
	{
		int indice1;
		int indice2;
		char elemento[noeRecursosMaxLinea];
		
		if(strlen(valor) - 2 > 0)
		{ 
			indice1 = 0;
			indice2 = 0;
			
			for(int i = 1; i < strlen(valor); i++)
			{
				
				if(valor[i] == ',' || valor[i] == ']')
				{
					elemento[indice2] = 0;
					
					vector[indice1] = atoi(elemento);
					
					indice1 ++;
					indice2 = 0;
				}
				else
				{
					elemento[indice2] = valor[i];
					indice2 ++;
				}
			}
		}

	}
	
	int ObtenEntero(const char valor[])
	{
		return atoi(valor);
	}
	
	bool LeePropiedad(NOERecurso* recurso, char nombre[], char valor[])
	{
		
		char linea[noeRecursosMaxLinea];
		char trimeada[noeRecursosMaxLinea];		

		char* r = 0;
		bool leida = false;
		
		do
		{
			r = fgets(linea, noeRecursosMaxLinea, recurso);
			
			if(r > 0)
			{
				
				// Trimear

				int j = 0;
				for(int i = 0; i < strlen(linea); i ++)
				{
					if(linea[i] != ' ' && linea[i] != '\t' && linea[i] != '\n')
					{
						trimeada[j] = toupper(linea[i]);
						j ++;
					}
				}

				trimeada[j] = 0;

				//printf("Trimeada \"%s\"\n", trimeada);

				if(strlen(trimeada) == 0)
				{
					// Linea vacia
				}
				else if(trimeada[0] == '#')
				{
					// Comentario
				}
				else
				{
					// Parse line

					int j = 0;
					int foundSeparator = 0;
					for(int i = 0; i < strlen(trimeada); i++)
					{
						if(!foundSeparator)
						{
							if(trimeada[i] == ':')
							{
								//printf("Separador\n");
								foundSeparator = 1;
								nombre[j] = 0;
								j = 0;
							}
							else
							{
								//printf("Copiando1\n");
								nombre[j] = trimeada[i];
								j ++;
							}
						}
						else
						{
							//printf("Copiando2\n");
							valor[j] = trimeada[i];
							j ++;
						}
						
					}

					valor[j] = 0;
					
					leida = true;
				}
			}
		
		} while(r > 0 && !leida);
		
		return leida;
		
	}
	
	void CierraRecurso(NOERecurso* f)
	{		
		fclose(f);	
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
	
	NOEDatosForma* ObtenDatosForma(int indice)
	{
		return datosFormas[indice];
	}	
	
	NOEFuente ObtenFuente(int indice)
	{
		return fuentes[indice];
	}
	
	

}