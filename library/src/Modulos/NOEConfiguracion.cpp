#include "Modulos/NOEComun.hpp"

namespace NOEConfiguracion
{
	Configuracion configuracion;

	Configuracion& ObtenConfiguracion()
	{
		return configuracion;
	}

	void IniciaConfiguracion()
	{
		// Iniciar configuracion

		configuracion = Configuracion();


		FILE* fichero;	
		char nombre[noeRecursosMaxLinea];
		char valor[noeRecursosMaxLinea];
		
		fichero = AbreRecurso("configuracion.ini");
		
		while(LeePropiedad(fichero, nombre, valor))
		{
			if(strcmp(nombre, "TAMANYOTILE") == 0)
			{
				configuracion.tamanyoTile = ObtenEntero(valor);
			}
			else if(strcmp(nombre, "ANCHOTILEMAPS") == 0)
			{
				configuracion.anchoTilemaps = ObtenEntero(valor);
			}
			else if(strcmp(nombre, "ALTOTILEMAPS") == 0)
			{
				configuracion.altoTilemaps = ObtenEntero(valor);
			}
			else if(strcmp(nombre, "ANCHOPANTALLA") == 0)
			{
				configuracion.anchoPantalla = ObtenEntero(valor);
			}
			else if(strcmp(nombre, "ALTOPANTALLA") == 0)
			{
				configuracion.altoPantalla = ObtenEntero(valor);
			}
			else if(strcmp(nombre, "PANTALLACOMPLETA") == 0)
			{
				configuracion.pantallaCompleta = ObtenEntero(valor);
			}
			else if(strcmp(nombre, "LONGITUDLINEAENTRADA") == 0)
			{
				configuracion.longitudLineaEntrada = ObtenEntero(valor);
			}
			
		}
		
		CierraRecurso(fichero);		

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
		printf("  numFormas............. %d\n", configuracion.numFormas);
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