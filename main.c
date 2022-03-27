#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "list.c"

typedef struct
{
    char* NombreLista;
    List* CancionesLista;
    size_t Cantidad;
} ListaReproduccion;

typedef struct 
{
    char Nombre [100];
    char Artista [100];
    List* Generos;
    int Anio;
    ListaReproduccion* ListaReproduccion;
} Cancion;

void eliminarCancion(char *nombre, char *artista, int anio);
void mostrarListasReproduccion();
void mostrarCancionesPorLista(char *nombre);
void mostrarInfoCancion(Cancion *cancion);

void nuevaCancion();

List *ListaGlobalCanciones;
List *ListaGlobalListasReproduccion;

int main()
{
    ListaGlobalCanciones = createList();
    ListaGlobalListasReproduccion = createList();

    char nombre[100];
    char artista[100];
    int anio;
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
        getchar();

        switch(option)
        {
            case 1: break;  // Importar canciones
            case 2: break;  // Exportar canciones
            case 3:
                nuevaCancion();
                break;  // Agregar cancion
            case 4: break;  // Buscar por nombre
            case 5: break;  // Buscar por artista
            case 6: break;  // Buscar por genero
            case 7: // Eliminar cancion
                printf("Ingrese el nombre de la canción: ");
                scanf("%[^\n]", nombre);
                getchar();
                printf("Ingrese el artista de la canción: ");
                scanf("%[^\n]", artista);
                getchar();
                printf("Ingrese el año de la canción: ");
                scanf("%d", &anio);
                getchar();
                eliminarCancion(nombre, artista, anio);
                break;
            case 8: // Mostrar nombres listas
                mostrarListasReproduccion();
                break;  
            case 9: // Mostrar canciones lista
                printf("Ingrese el nombre de la lista: ");
                scanf("%[^\n]", nombre);
                getchar();
                mostrarCancionesPorLista(nombre);
                break; 
            case 10: break; // Mostrar todas las canciones      
            case 11: exit(EXIT_SUCCESS); // Salir de la aplicacion
        }
    }
    
    return 0;
}

void nuevaCancion()
{
    char* generos = (char *) malloc(30*sizeof(char));

    Cancion* nuevaCancion = NULL;

    nuevaCancion = (Cancion *) malloc(sizeof(Cancion));

    char nombreCancion[30];
    char artistaCancion[30];
    int anioCancion;
    int x;

    fflush(stdin);
    printf("Ingrese el nombre de la cancion: ");
    scanf("%[^\n]s", nombreCancion);

    strcpy(nuevaCancion->Nombre, nombreCancion);

    fflush(stdin);
    printf("Ingrese el artista de la cancion: ");
    scanf("%[^\n]s", artistaCancion);

    strcpy(nuevaCancion->Artista, artistaCancion);

    fflush(stdin);
    nuevaCancion->Generos = createList();
    printf("Ingrese el/los genero(s) de la cancion: ");
    scanf("%[^\n]s", generos);

    pushBack(nuevaCancion->Generos, generos);

    fflush(stdin);
    printf("Ingrese el anio de la cancion: ");
    scanf("%d", &anioCancion);

    nuevaCancion->Anio = anioCancion;

    pushBack(ListaGlobalCanciones, nuevaCancion);

}

void eliminarCancion(char *nombre, char *artista, int anio)
{
    int contador = 0;
    Cancion *cancion = firstList(ListaGlobalCanciones);
    while(cancion)
    {
        if(strcmp(cancion->Nombre, nombre) && strcmp(cancion->Artista, artista) && cancion->Anio == anio)
        {
            ListaReproduccion *listaReproduccion = cancion->ListaReproduccion;
            List *listaCanciones = listaReproduccion->CancionesLista;
            Cancion *aux = firstList(listaCanciones);
            while(aux)
            {
                if(aux == cancion)
                {
                    popCurrent(ListaGlobalCanciones);
                    popCurrent(listaCanciones);
                    listaReproduccion->Cantidad--;
                    contador++;
                    break;
                }
                aux = nextList(listaCanciones);
            }
        }
        cancion = nextList(ListaGlobalCanciones);
    }

    if(contador == 0) // La canción ingresada no existe
    {
        printf("No se encontraron canciones\n\n");
    }
}

void mostrarListasReproduccion()
{
    ListaReproduccion *listaReproduccion = firstList(ListaGlobalListasReproduccion);
    while(listaReproduccion)
    {
        printf("%s, %zd\n", listaReproduccion->NombreLista, listaReproduccion->Cantidad);
        listaReproduccion = nextList(ListaGlobalListasReproduccion);
    }
    printf("\n");
}

void mostrarCancionesPorLista(char *nombre)
{
    int contador = 0;
    ListaReproduccion *listaReproduccion = firstList(ListaGlobalListasReproduccion);
    while(listaReproduccion)
    {
        if(strcmp(listaReproduccion->NombreLista, nombre) == 0)
        {
            List *listaCanciones = listaReproduccion->CancionesLista;
            Cancion *cancion = firstList(listaCanciones);
            while(cancion)
            {
                mostrarInfoCancion(cancion);
                cancion = nextList(listaCanciones);
            }
            break;
        }
        listaReproduccion = nextList(ListaGlobalListasReproduccion);
    }

    if(contador == 0) // La lista no existe
    {
        printf("No se encontró la lista de reproducción\n\n");
    }
}

void mostrarInfoCancion(Cancion *cancion)
{
    printf("%s, %s,", cancion->Nombre, cancion->Artista);

    List *listaGeneros = cancion->Generos;
    char *genero = firstList(listaGeneros);
    while(genero)
    {
        printf(" %s", genero);
        genero = nextList(listaGeneros);
    }

    printf(", %d, %s\n", cancion->Anio, cancion->ListaReproduccion->NombreLista);
}