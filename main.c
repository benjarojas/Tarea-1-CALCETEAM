#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "list.h"

typedef struct
{
    char NombreLista[100];
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

char *get_csv_field (char * tmp, int k);
void importarCanciones(char *nombreArchivo);
void exportarCanciones(char *nombreArchivo);
void crearCancion(char* nombre, char* artista, List* generos, int anio, char* nombreLista);
void agregarCancion();
void eliminarCancion(char *nombre, char *artista, int anio);
void mostrarListasReproduccion();
void mostrarCancionesPorLista(char *nombre);
void mostrarInfoCancion(Cancion *cancion);
void mostrarCanciones();
void buscarArtista();
void buscarGenero();

ListaReproduccion *buscarListaReproduccion(char *nombre);
ListaReproduccion *crearListaReproduccion(char *nombre);

Cancion* buscarCancionNombre(char *nombre);

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

    Cancion* resultadoBusqueda;

    while(option != 11)
    {
        printf("1.-  Importar canciones desde un archivo CSV\n"); //Funcionando
        printf("2.-  Exportar canciones CSV\n"); //Funcionando
        printf("3.-  Agregar cancion\n"); // Funcionando
        printf("4.-  Buscar cancion por nombre\n"); // Funcionando
        printf("5.-  Buscar cancion por artista\n");
        printf("6.-  Buscar cancion por genero\n");
        printf("7.-  Eliminar cancion\n"); // Funcionando
        printf("8.-  Mostrar nombres de las listas de reproduccion\n"); // Funcionando
        printf("9.-  Mostrar una lista de reproduccion\n"); // Funcionando
        printf("10.- Mostrar todas las canciones\n"); // Funcionando
        printf("11.- Salir\n\n");

        printf("Ingrese una opcion: ");
        scanf("%d", &option);
        fflush(stdin);

        switch(option)
        {
            case 1:// Importar canciones
                fflush(stdin);
                printf("Ingrese el nombre del archivo: ");
                scanf("%[^\n]", nombre);
                importarCanciones(nombre);
            break;
            case 2: // Exportar canciones
                fflush(stdin);
                printf("Ingrese el nombre del archivo: ");
                scanf("%[^\n]", nombre);
                exportarCanciones(nombre);
                break;
            case 3:
                agregarCancion();
                break;  // Agregar cancion
            case 4:
                fflush(stdin);
                printf("Ingrese el nombre de la cancion: ");
                scanf("%[^\n]", nombre);
                resultadoBusqueda = buscarCancionNombre(nombre);
                if(resultadoBusqueda != NULL)
                {
                    printf("Cancion encontrada: \n");
                    mostrarInfoCancion(resultadoBusqueda);
                } else {
                    printf("No se encontro la cancion\n");
                }
                break;  // Buscar por nombre
            case 5:  // Buscar por artista 
            buscarArtista();
            break;
            case 6:  // Buscar por genero
            buscarGenero();
            break;
            case 7: // Eliminar cancion
                printf("Ingrese el nombre de la cancion: ");
                scanf("%[^\n]", nombre);
                fflush(stdin);
                printf("Ingrese el artista de la cancion: ");
                scanf("%[^\n]", artista);
                fflush(stdin);
                printf("Ingrese el año de la cancion: ");
                scanf("%d", &anio);
                fflush(stdin);
                eliminarCancion(nombre, artista, anio);
                break;
            case 8: // Mostrar nombres listas
                mostrarListasReproduccion();
                break;  
            case 9: // Mostrar canciones lista
                printf("Ingrese el nombre de la lista: ");
                scanf("%[^\n]", nombre);
                fflush(stdin);
                mostrarCancionesPorLista(nombre);
                break; 
            case 10: // Mostrar todas las canciones
                mostrarCanciones();
                break;       
            case 11: exit(EXIT_SUCCESS); // Salir de la aplicacion
        }
    }
    
    return 0;
}

char * get_csv_field (char * tmp, int k) {
    int open_mark = 0;
    char* ret=(char*) malloc (100*sizeof(char));
    int ini_i=0, i=0;
    int j=0;
    while(tmp[i+1]!='\0'){

        if(tmp[i]== '\"'){
            open_mark = 1-open_mark;
            if(open_mark) ini_i = i+1;
            i++;
            continue;
        }

        if(open_mark || tmp[i]!= ','){
            if(k==j) ret[i-ini_i] = tmp[i];
            i++;
            continue;
        }

        if(tmp[i]== ','){
            if(k==j) {
               ret[i-ini_i] = 0;
               return ret;
            }
            j++; ini_i = i+1;
        }

        i++;
    }

    if(k==j) {
       ret[i-ini_i] = 0;
       return ret;
    }

    return NULL;
}

void importarCanciones(char* nombreArchivo)
{
    FILE* archivoEntrada;

    archivoEntrada=fopen(nombreArchivo, "r");

    if(archivoEntrada==NULL)
    {
        printf("ERROR AL IMPORTAR ARCHIVO CSV");
        exit(1);
    }

    char nombre[100];
    char artista[100];
    List* generos=createList();
    int anio;
    char nombreLista[20];

    char linea [1024];

    while (fgets (linea, 1023, archivoEntrada) != NULL) 
    {
        char *aux = get_csv_field(linea, 0);

        if (buscarCancionNombre(aux)==NULL);
        {
            for(size_t i=0;i<5;i++)
            {
                char *aux = get_csv_field(linea, i);
            
                if (i==0)
                {
                    strcpy(nombre, aux);     
                }
                else if (i==1)
                {
                    strcpy (artista, aux);
                }
                else if (i==2)
                {
                    pushFront(generos, aux);
                }
                else if (i==3)
                {
                    anio=atoi(aux);
                }
                else if (i==4)
                {
                    strcpy(nombreLista, aux);
                }
            }
            crearCancion(nombre, artista, generos, anio, nombreLista);
        }
    }
    fclose(archivoEntrada);
}


void crearCancion(char* nombre, char* artista, List* generos, int anio, char* nombreLista)
{
    Cancion* cancionAgregada=NULL;

    cancionAgregada=(Cancion*) malloc(sizeof(Cancion));
    cancionAgregada->Generos=createList();

    strcpy(cancionAgregada->Nombre, nombre);
    strcpy(cancionAgregada->Artista, artista);
    pushBack(cancionAgregada->Generos, generos);
    cancionAgregada->Anio=anio;

    ListaReproduccion *listaReproduccion = buscarListaReproduccion(nombreLista);
    if(!listaReproduccion) // La lista no existe
    {
        listaReproduccion = crearListaReproduccion(nombreLista);
    }

    listaReproduccion->Cantidad++;
    cancionAgregada->ListaReproduccion = listaReproduccion;
    pushBack(listaReproduccion->CancionesLista, cancionAgregada);
    pushFront(ListaGlobalCanciones, cancionAgregada);
}

void exportarCanciones(char *nombreArchivo)
{
    FILE *archivo = fopen(nombreArchivo, "w");
    if(!archivo)
    {
        printf("No se pudo crear el archivo\n");
        return;
    }

    Cancion *cancion = firstList(ListaGlobalCanciones);
    while(cancion)
    {
        fprintf(archivo, "%s, %s, ", cancion->Nombre, cancion->Artista);

        List *listaGeneros = cancion->Generos;
        char generos[100];
        char *aux = firstList(listaGeneros);
        bool masDeUno = false; // Si hay más de un género se agregan comillas al inicio y al final

        strcpy(generos, "");
        while(aux)
        {
            strcat(generos, aux);
            aux = nextList(listaGeneros);
            if(aux)
            {
                strcat(generos, ", ");
                masDeUno = true;
            }
        }

        if(masDeUno)
        {
            char copiaGeneros[100];
            strcpy(copiaGeneros, "\"");
            strcat(copiaGeneros, generos);
            strcat(copiaGeneros, "\"\0");
            fprintf(archivo, "%s, ", copiaGeneros);
        }
        else
        {
            fprintf(archivo, "%s, ", generos);
        }

        fprintf(archivo, "%d, %s\n", cancion->Anio, cancion->ListaReproduccion->NombreLista);

        cancion = nextList(ListaGlobalCanciones);
    }

    fclose(archivo);
    printf("\n");
}

void agregarCancion()
{
    Cancion* nuevaCancion = NULL;

    char* generos = NULL;
    char nombreCancion[100];
    char artistaCancion[100];
    char nombreLista[100];
    int anioCancion;

    nuevaCancion = (Cancion *) malloc(sizeof(Cancion));
    generos = (char *) malloc(100*sizeof(char));

    fflush(stdin);
    printf("Ingrese el nombre de la cancion: ");
    scanf("%[^\n]", nombreCancion);

    strcpy(nuevaCancion->Nombre, nombreCancion);

    fflush(stdin);
    printf("Ingrese el artista de la cancion: ");
    scanf("%[^\n]", artistaCancion);

    strcpy(nuevaCancion->Artista, artistaCancion);


    // Creamos una lista en caso de que sea mas de 1 genero
    fflush(stdin);
    nuevaCancion->Generos = createList();
    printf("Ingrese el/los genero(s) de la cancion separados por coma y sin espacios: ");
    scanf("%[^\n]", generos);

    int i = 0; // Recorre todo el string de géneros
    while(true)
    {
        char *aux = (char *) malloc(30 * sizeof(char)); // Guarda un solo género
        int k = 0; // Recorre la variable aux
        while(generos[i] != ',' && generos[i] != '\0')
        {
            aux[k] = generos[i];
            i++;
            k++;
        }
        aux[k] = '\0';
        pushBack(nuevaCancion->Generos, aux); // Se añade el género a la lista

        if(generos[i] == '\0') // Fin del string
        {
            break;
        }
        i++; // Salta las comas
    }

    fflush(stdin);
    printf("Ingrese el anio de la cancion: ");
    scanf("%d", &anioCancion);

    nuevaCancion->Anio = anioCancion;

    fflush(stdin);
    printf("Ingrese la lista de reproducción: ");
    scanf("%[^\n]", nombreLista);

    ListaReproduccion *listaReproduccion = buscarListaReproduccion(nombreLista);
    if(!listaReproduccion) // La lista no existe
    {
        listaReproduccion = crearListaReproduccion(nombreLista);
    }

    listaReproduccion->Cantidad++;
    nuevaCancion->ListaReproduccion = listaReproduccion;
    pushBack(listaReproduccion->CancionesLista, nuevaCancion);
    pushFront(ListaGlobalCanciones, nuevaCancion);
    printf("\n");
}

Cancion* buscarCancionNombre(char *nombre)
{
    Cancion *aux = firstList(ListaGlobalCanciones); 
    while(aux != NULL)
    {
        if(strcmp(aux->Nombre, nombre) == 0)
        {
            return aux;
        }
        aux = nextList(ListaGlobalCanciones);
    }
    return NULL;
}

ListaReproduccion *buscarListaReproduccion(char *nombre)
{
    ListaReproduccion *listaReproduccion = firstList(ListaGlobalListasReproduccion);
    while(listaReproduccion)
    {
        if(strcmp(listaReproduccion->NombreLista, nombre) == 0)
        {
            return listaReproduccion;
        }
        listaReproduccion = nextList(ListaGlobalListasReproduccion);
    }
    return NULL;
}

ListaReproduccion *crearListaReproduccion(char *nombre)
{
    ListaReproduccion *listaReproduccion = (ListaReproduccion *) malloc(sizeof(ListaReproduccion));
    strcpy(listaReproduccion->NombreLista, nombre); 
    listaReproduccion->CancionesLista = createList();
    listaReproduccion->Cantidad = 0;
    pushBack(ListaGlobalListasReproduccion, listaReproduccion);
    return listaReproduccion;
}

void eliminarCancion(char *nombre, char *artista, int anio)
{
    int contador = 0;
    Cancion *cancion = firstList(ListaGlobalCanciones);
    while(cancion)
    {
        if(strcmp(cancion->Nombre, nombre) == 0 && strcmp(cancion->Artista, artista) == 0 && cancion->Anio == anio)
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
        printf("No se encontraron canciones\n");
    }
    printf("\n");
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
            contador++;
            break;
        }
        listaReproduccion = nextList(ListaGlobalListasReproduccion);
    }

    if(contador == 0) // La lista no existe
    {
        printf("No se encontró la lista de reproducción\n");
    }
    printf("\n");
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

void mostrarCanciones()
{
    Cancion *cancion = firstList(ListaGlobalCanciones);
    while(cancion)
    {
        mostrarInfoCancion(cancion);
        cancion = nextList(ListaGlobalCanciones);
    }
    printf("\n");
}

void buscarArtista()
{
    char artista [30];
    int cont = 0;
 
    List *listaCanciones = ListaGlobalCanciones;
    Cancion *cancion = firstList(listaCanciones);
 
    printf("Ingrese nombre del artista: ");
    scanf("%[^\n]", &artista);
 
    while(cancion)
    {
        if(strcmp(cancion->Artista, artista) == 0)
        {
            mostrarInfoCancion(cancion);
            cont = 1;
        }
        cancion = nextList(listaCanciones);
    }
 
    if (cont == 0)
    {
        printf("No hay una cancion del artista ingresado\n");
    }
}
 
void buscarGenero()
{
    char genero_ [30];
    int cont = 0;
 
    List *listaCanciones = ListaGlobalCanciones;
    Cancion *cancion = firstList(listaCanciones);
 
    printf("Ingrese nombre del genero: ");
    scanf("%[^\n]", &genero_);
 
    while(listaCanciones){
 
        List *listaGeneros = cancion->Generos;
        char *genero = firstList(listaGeneros);
 
        while(listaGeneros)
        {
            if(strcmp(genero, genero_) == 0){
                mostrarInfoCancion(cancion);
                cont = 1;
            }
            
            genero = nextList(listaGeneros);
        }
 
        cancion = nextList(listaCanciones);
    }

    if(cont == 0)
    {
        printf("No hay una cancion del genero ingresado\n");
    }
}