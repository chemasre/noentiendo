#include "Modulos/NOEComun.hpp"

namespace NOEConfiguracion
{
	const int noeConfigurationMaxLinea = 200;

	Configuracion configuracion;

	Configuracion& ObtenConfiguracion()
	{
		return configuracion;
	}

	void IniciaConfiguracion()
	{
		// Iniciar configuracion

		configuracion = Configuracion();

		char linea1[noeConfigurationMaxLinea];
		char linea2[noeConfigurationMaxLinea];
		FILE* f = fopen("configuracion.ini","r");
		char* r = 0;

		do
		{
			r = fgets(linea1, noeConfigurationMaxLinea, f);

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

					char parte1[noeConfigurationMaxLinea];
					char parte2[noeConfigurationMaxLinea];

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
					else if(strcmp(parte1, "LONGITUDLINEAENTRADA") == 0)
					{
						configuracion.longitudLineaEntrada = atoi(parte2);
					}
					
				}

				

			}



		} while(r > 0);

		fclose(f);

		printf("Configuracion:\n");
		printf("\n");
		printf("  anchoPantalla......... %d pixels\n", configuracion.anchoPantalla);
		printf("  altoPantalla.......... %d pixels\n", configuracion.altoPantalla);
		printf("  pantallaCompleta...... %d\n", configuracion.pantallaCompleta);
		printf("  longitudLineaEntrada.. %d\n", configuracion.longitudLineaEntrada);
		printf("  tamanyoTile........... %d pixels\n", configuracion.tamanyoTile);
		printf("  anchoTilemaps......... %d tiles\n", configuracion.anchoTilemaps);
		printf("  altoTilemaps.......... %d tiles\n", configuracion.altoTilemaps);
		printf("  numTilemaps........... %d\n", configuracion.numTilemaps);
		printf("  numSprites............ %d\n", configuracion.numSprites);
		printf("  numDecorados.......... %d\n", configuracion.numDecorados);
		printf("  numFuentes............ %d\n", configuracion.numFuentes);
		printf("  numCursores........... %d\n", configuracion.numCursores);
		printf("  cursor................ %d\n", configuracion.cursor);
		printf("  anchoCursor........... %d\n", configuracion.anchoCursor);
		printf("  altoCursor............ %d\n", configuracion.altoCursor);
		printf("  desplazamientoCursorX. %d\n", configuracion.desplazamientoCursorX);
		printf("  desplazamientoCursorY. %d\n", configuracion.desplazamientoCursorY);
		printf("  numMusicas............ %d\n", configuracion.numMusicas);
		printf("  numSonidos............ %d\n", configuracion.numSonidos);
		printf("  numCanales............ %d\n", configuracion.numCanales);
		printf("\n");
		
	}
}