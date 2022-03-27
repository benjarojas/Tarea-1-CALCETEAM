#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "list.h"

int main()
{
    int option = 0;

    while(option != 11)
    {
        printf("1.-  Importar canciones desde un archivo CSV\n");
        printf("2.-  Exportar canciones CSV\n");
        printf("3.-  Agregar cancion\n");
        printf("4.-  Buscar cancion por nombre\n");
        printf("5.-  Buscar cancion por artista\n");
        printf("6.-  Buscar cancion por genero\n");
        printf("7.-  Eliminar cancion\n");
        printf("8.-  Mostrar nombres de las listas de reproduccion\n");
        printf("9.-  Mostrar una lista de reproduccion\n");
        printf("10.- Mostrar todas las canciones\n");
        printf("11.- Salir\n\n");

        printf("Ingrese una opcion: ");
        scanf("%d", &option);

        switch(option)
        {
            case 1: break;  // Importar canciones
            case 2: break;  // Exportar canciones
            case 3: break;  // Agregar cancion
            case 4: break;  // Buscar por nombre
            case 5: break;  // Buscar por artista
            case 6: break;  // Buscar por genero
            case 7: break;  // Eliminar cancion
            case 8: break;  // Mostrar nombres listas
            case 9: break;  // Mostrar canciones lista
            case 10: break; // Mostrar todas las canciones
            
            case 11: exit(EXIT_SUCCESS); // Salir de la aplicacion
        }
    }
    
    return 0;
}