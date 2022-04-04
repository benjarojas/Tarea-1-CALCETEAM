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
    char Nombre[100];
    char Artista[100];
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
void buscarCancionNombre(char *nombre);
void buscarArtista();
void buscarGenero();

ListaReproduccion *buscarListaReproduccion(char *nombre);
ListaReproduccion *crearListaReproduccion(char *nombre);

Cancion *buscarCancion(char *nombreCancion, char *artista, int anio, char *nombreLista);

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
                buscarCancionNombre(nombre);
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

char *get_csv_field(char *linea, int indice)
{
    char *campo = (char *) malloc(100 * sizeof(char *)); // Guarda el string a retornar
    int i = 0; // Recorre la linea
    int k = 0; // Cuenta las comas
    int n = 0; // Recorre el campo
    bool comillas = false;

    while(linea[i] != '\0')
    {
        if(linea[i] == '\"')
        {
            comillas = !comillas;
        }

        if(k == indice)
        {
            if(linea[i] != '\"')
            {
                campo[n] = linea[i];
                n++;
            }
        }

        i++;

        if(linea[i] == ',' && !comillas)
        {
            k++;
            i++;
        }

        if(k > indice || linea[i] == '\0' || linea[i] == '\n')
        {
            campo[n] = '\0';
            return campo;
        }
    }

    return NULL;
}

void importarCanciones(char* nombreArchivo)
{
    FILE* archivoEntrada;

    archivoEntrada = fopen(nombreArchivo, "r");

    if(archivoEntrada == NULL)
    {
        printf("Error al importar archivo .csv");
        exit(EXIT_FAILURE);
    }

    char linea[1024];

    while (fgets (linea, 1023, archivoEntrada) != NULL) 
    {
        // Se guardan los datos según el campo que se recibe
        char *nombre = get_csv_field(linea, 0);
        char *artista = get_csv_field(linea, 1);
        int anio = atoi(get_csv_field(linea, 3));
        char *nombreLista = get_csv_field(linea, 4);

        char *strGeneros = get_csv_field(linea, 2); // Contiene el string de géneros incluyendo las comas
        List *listaGeneros = createList(); // Lista para guardar los géneros por separado
        int i = 0; // Recorre el string de géneros

        while(true)
        {
            char *genero = (char *) malloc(30 * sizeof(genero));
            int k = 0; // Recorre cada género que se añade a la lista
            while(strGeneros[i] != ',' && strGeneros[i] != '\0')
            {
                genero[k] = strGeneros[i];
                i++;
                k++;
            }

            genero[k] = '\0';
            pushBack(listaGeneros, genero);

            if(strGeneros[i] == ',')
            {
                i++; // Salta la coma
                if(strGeneros[i] == ' ')
                {
                    i++; // Salta el espacio después de la coma
                }
            }
            else
            {
                break; // Fin de la lista
            }
        }

        if(!buscarCancion(nombre, artista, anio, nombreLista)) // Se verifica que la canción no exista previamente
        {
            crearCancion(nombre, artista, listaGeneros, anio, nombreLista); // Se crea una variable tipo canción con los datos recopilados
        }
    }

    fclose(archivoEntrada);
    printf("\n");
}

void crearCancion(char* nombre, char* artista, List* generos, int anio, char* nombreLista)
{
    Cancion *cancionAgregada = (Cancion*) malloc(sizeof(Cancion)); // Reserva de memoria de variable tipo cancion

    //Se copia cada dato en los campos del registro
    strcpy(cancionAgregada->Nombre, nombre);
    strcpy(cancionAgregada->Artista, artista);
    cancionAgregada->Generos = generos;
    cancionAgregada->Anio = anio;

    ListaReproduccion *listaReproduccion = buscarListaReproduccion(nombreLista);
    if(!listaReproduccion) // La lista no existe
    {
        listaReproduccion = crearListaReproduccion(nombreLista); // Se crea lista de reproducción
    }

    listaReproduccion->Cantidad++;
    cancionAgregada->ListaReproduccion = listaReproduccion; 
    pushBack(listaReproduccion->CancionesLista, cancionAgregada); // Se agrega canción a lista correspondiente
    pushBack(ListaGlobalCanciones, cancionAgregada); // Se agrega canción a lista global de canciones
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
        fprintf(archivo, "%s,%s,", cancion->Nombre, cancion->Artista);

        List *listaGeneros = cancion->Generos;
        char generos[100];
        char *aux = firstList(listaGeneros);
        bool masDeUno = false; // Si hay más de un género se agregan comillas al inicio y al final

        strcpy(generos, "");
        while(aux)
        {
            strcat(generos, aux);
            aux = nextList(listaGeneros);
            if(aux) // La lista tiene más de un género
            {
                strcat(generos, ", ");
                masDeUno = true;
            }
        }

        if(masDeUno) // Se crea una copia del string de géneros para incluir las comillas
        {
            char copiaGeneros[100];
            strcpy(copiaGeneros, "\"");
            strcat(copiaGeneros, generos);
            strcat(copiaGeneros, "\"");
            fprintf(archivo, "%s,", copiaGeneros);
        }
        else
        {
            fprintf(archivo, "%s,", generos);
        }

        fprintf(archivo, "%d,%s\n", cancion->Anio, cancion->ListaReproduccion->NombreLista);

        cancion = nextList(ListaGlobalCanciones);
    }

    fclose(archivo);
    printf("\n");
}

void agregarCancion()
{
    // Creamos variables para recibir los datos de entrada
    char nombreCancion[100];
    char artistaCancion[100];
    char nombreLista[100];
    char generos[100];
    int anioCancion;

    // Creamos una lista de generos en caso de que la nueva canción tenga mas de uno
    List *listaGeneros = createList();

    // Limpiamos el buffer de stdin y leemos nombre
    fflush(stdin);
    printf("Ingrese el nombre de la cancion: ");
    scanf("%[^\n]", nombreCancion);

    // Limpiamos el buffer de stdin y leemos artista
    fflush(stdin);
    printf("Ingrese el artista de la cancion: ");
    scanf("%[^\n]", artistaCancion);

    // Limpiamos el buffer de stdin y leemos los generos separados por comas
    fflush(stdin);
    printf("Ingrese el/los genero(s) de la cancion separados por coma y sin espacios: ");
    scanf("%[^\n]", generos);

    // Recorre todo el string de géneros
    int i = 0; 
    while(true)
    {
        char *aux = (char *) malloc(30 * sizeof(char)); // Creamos un string auxiliar para cada genero
        int k = 0; // Recorre la variable aux
        // Mientras el elemento actual no sea NULL o una coma
        while(generos[i] != ',' && generos[i] != '\0')
        {
            aux[k] = generos[i]; // Copiamos caracter a caracter
            i++;
            k++;
        }
        aux[k] = '\0'; // Insertamos el carácter NULL (fin del string)
        pushBack(listaGeneros, aux); // Se añade el género al final de la lista

        // Si llegamos al carácter NULL
        if(generos[i] == '\0') break;
        i++; // Salta las comas
    }

    // Limpiamos el buffer stdin y leemos el año
    fflush(stdin);
    printf("Ingrese el año de la cancion: ");
    scanf("%d", &anioCancion);

    // Limpiamos el buffer stdin y leemos el nombre de la lista
    fflush(stdin);
    printf("Ingrese la lista de reproducción: ");
    scanf("%[^\n]", nombreLista);

    // Se agrega la canción solo si no existe o se encuentra en una lista distinta a la ingresada
    if(!buscarCancion(nombreCancion, artistaCancion, anioCancion, nombreLista))
    {
        crearCancion(nombreCancion, artistaCancion, listaGeneros, anioCancion, nombreLista);
    }
    else
    {
        printf("La canción ingresada ya existe en la lista de reproducción.\n");
    }
    printf("\n");
}

// Busca la canción específica según los datos ingresados
Cancion* buscarCancion(char *nombreCancion, char *artista, int anio, char *nombreLista)
{
    Cancion *cancion = firstList(ListaGlobalCanciones);
    while(cancion)
    {
        if(strcmp(cancion->Nombre, nombreCancion) == 0 && strcmp(cancion->Artista, artista) == 0
           && cancion->Anio == anio && strcmp(cancion->ListaReproduccion->NombreLista, nombreLista) == 0)
        {
            return cancion;
        }
        cancion = nextList(ListaGlobalCanciones);        
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
    Cancion *cancion = lastList(ListaGlobalCanciones);
    while(cancion) // Se recorre la lista global de canciones
    {
        if(strcmp(cancion->Nombre, nombre) == 0 && strcmp(cancion->Artista, artista) == 0 && cancion->Anio == anio)
        {
            ListaReproduccion *listaReproduccion = cancion->ListaReproduccion;
            List *listaCanciones = listaReproduccion->CancionesLista;
            Cancion *aux = lastList(listaCanciones);
            while(aux) // Se recorre la lista de reproducción de la canción a eliminar
            {
                if(aux == cancion)
                {
                    popCurrent(ListaGlobalCanciones); // Se elimina la canción de la lista global
                    popCurrent(listaCanciones); // Se elimina la canción de la lista de reproducción
                    cancion = getCurrent(ListaGlobalCanciones); // Actualiza la variable con el nodo actual
                    listaReproduccion->Cantidad--; // Se reduce la cantidad de canciones de la lista
                    contador++;
                    break; // Se rompe el ciclo una vez la canción fue eliminada en ambas listas
                }
                aux = prevList(listaCanciones);
            }
        }
        else
        {
            cancion = prevList(ListaGlobalCanciones);
        }
    }

    if(contador == 0) // La canción ingresada no existe
    {
        printf("No se encontraron canciones\n");
    }
    printf("\n");
}

void mostrarListasReproduccion()
{
    int contador = 0;
    ListaReproduccion *listaReproduccion = firstList(ListaGlobalListasReproduccion);
    while(listaReproduccion)
    {
        printf("Nombre de la lista: %s\n", listaReproduccion->NombreLista);
        printf("Cantidad de canciones: %zd\n\n", listaReproduccion->Cantidad);
        contador++;
        listaReproduccion = nextList(ListaGlobalListasReproduccion);
    }

    if(contador == 0)
    {
        printf("No hay listas de reproducción para mostrar.\n\n");
    }
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
        printf("No se encontró la lista de reproducción\n\n");
    }
}

void mostrarInfoCancion(Cancion *cancion)
{
    printf("Nombre: %s\n", cancion->Nombre);
    printf("Artista: %s\n", cancion->Artista);
    printf("Generos: ");

    List *listaGeneros = cancion->Generos;
    char *genero = firstList(listaGeneros);
    while(genero)
    {
        printf("%s", genero);
        genero = nextList(listaGeneros);

        if(genero)
        {
            printf(", ");
        }
    }

    printf("\nAño: %d\n", cancion->Anio);
    printf("Lista de Reproducción: %s\n\n", cancion->ListaReproduccion->NombreLista);
}

void mostrarCanciones()
{
    int contador = 0;
    Cancion *cancion = firstList(ListaGlobalCanciones);
    while(cancion)
    {
        mostrarInfoCancion(cancion);
        contador++;
        cancion = nextList(ListaGlobalCanciones);
    }

    if(contador == 0)
    {
        printf("No hay canciones para mostrar.\n\n");
    }
}

// Buscar una canción según su nombre
void buscarCancionNombre(char *nombre)
{
    int contador = 0; // Contador en caso de que exista más de una canción con ese nombre
    // Creamos un puntero hacia un tipo canción para recorrer la lista
    Cancion *cancion = firstList(ListaGlobalCanciones); 
    while(cancion != NULL) // Si no hemos llegado al final de la lista
    {
        // Si encontramos una canción con ese nombre
        if(strcmp(cancion->Nombre, nombre) == 0)
        {
            // Mostramos la canción por pantalla
            mostrarInfoCancion(cancion);
            contador++; // Aumentamos el contador
        }
        cancion = nextList(ListaGlobalCanciones); // Siguiente nodo de la lista
    }

    if(contador == 0) // La canción ingresada no existe
    {
        printf("No se encontraron canciones\n\n");
    }
}

void buscarArtista()
{
    char artista[30];
    int cont = 0;
 
    List *listaCanciones = ListaGlobalCanciones;
    Cancion *cancion = firstList(listaCanciones); // Inicializo cancion en la primera posicion de la lista global
 
    printf("Ingrese nombre del artista: ");
    scanf("%[^\n]", artista); // Se guarda el nombre del artista

    while(cancion) // Se recorre la lista de canciones
    {
        if(strcmp(cancion->Artista, artista) == 0) // se compara el nombre del artista con el de la cancion
        {
            mostrarInfoCancion(cancion); // Mostramos info de canción por pantalla
            cont = 1;
        }
        cancion = nextList(listaCanciones); // Se avanza a la siguiente canción
    }
 
    if (cont == 0) // En caso de que el artista no exista
    {
        printf("No hay una cancion del artista ingresado\n\n");
    }
}
 
void buscarGenero()
{
    char genero[30];
    int cont = 0;
 
    List *listaCanciones = ListaGlobalCanciones;
    Cancion *cancion = firstList(listaCanciones);
 
    printf("Ingrese nombre del genero: ");
    scanf("%[^\n]", genero);
 
    while(cancion) // Se recorre la lista global de canciones
    {
        List *listaGeneros = cancion->Generos; // Se accede a los géneros de la canción
        char *aux = firstList(listaGeneros);
 
        while(aux) // Se recorre la lista de géneros de la canción
        {
            if(strcmp(genero, aux) == 0) // El género buscado se encuentra en la lista de géneros
            {
                mostrarInfoCancion(cancion);
                cont = 1;
                break;
            }
            
            aux = nextList(listaGeneros);
        }
 
        cancion = nextList(listaCanciones);
    }

    if(cont == 0)
    {
        printf("No hay una cancion del genero ingresado\n\n");
    }
}