#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LIBROS 100
#define MAX_USUARIOS 100
#define MAX_PRESTAMOS 100

// Definición de estructuras
typedef struct libro{
    char titulo[100];
    int edicion;
    char autor[60];
} Libro;

typedef struct usuario{
    char nombre[60];
    char identificacion[20];
    char tipo_usuario[15];
} Usuario;

typedef struct prestamo{
    char titulo_libro[100];
    char nombre_usuario[60];
    char fecha_prestamo[12];
    char fecha_devolucion[12];
} Prestamo;

// Funciones auxiliares
int buscar_libro(Libro libros[], int num_libros, char titulo[]);
int buscar_usuario(Usuario usuarios[], int num_usuarios, char identificacion[]);
int buscar_prestamo(Prestamo prestamos[], int num_prestamos, char titulo[], char identificacion[]);

// Funciones principales
void alta_libro(Libro libros[], int *num_libros);
void baja_libro(Libro libros[], int *num_libros, Prestamo prestamos[], int num_prestamos);
void listar_libros(Libro libros[], int num_libros);

void alta_usuario(Usuario usuarios[], int *num_usuarios);
void baja_usuario(Usuario usuarios[], int *num_usuarios, Prestamo prestamos[], int num_prestamos);
void listar_usuarios(Usuario usuarios[], int num_usuarios);

void realizar_prestamo(Libro libros[], int num_libros, Usuario usuarios[], int num_usuarios, Prestamo prestamos[], int *num_prestamos);
void realizar_devolucion(Libro libros[], int num_libros, Usuario usuarios[], int num_usuarios, Prestamo prestamos[], int *num_prestamos);
void listar_prestamos_usuario(Prestamo prestamos[], int num_prestamos, char identificacion[]);
void listar_prestamos_prestados(Prestamo prestamos[], int num_prestamos);

//Funciones para guardar los datos en ficheros
void escribir_libros_archivo(Libro libros);
void guardar_usuario_archivo(Usuario usuario);

int main(int argc, char *argv[]) {
	// Variables
    Libro libros[MAX_LIBROS];
    int num_libros = 0;

    Usuario usuarios[MAX_USUARIOS];
    int num_usuarios = 0;

    Prestamo prestamos[MAX_PRESTAMOS];
    int num_prestamos = 0;

    int opcion = 0;

    // Menú de opciones
    do {
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("1. Dar de alta libro\n");
        printf("2. Dar de baja libro\n");
        printf("3. Listar libros\n");
        printf("4. Dar de alta usuario\n");
        printf("5. Dar de baja usuario\n");
        printf("6. Listar usuarios\n");
        printf("7. Realizar prestamo\n");
        printf("8. Realizar devolucion\n");
        printf("9. Lista de libros prestados\n");
        printf("10. Lista de libros prestados por un usuario\n");
        printf("0. Salir\n");
        printf("Elija una opcion: ");
        scanf("%d", &opcion);
        system("cls");
        switch(opcion) {
            case 1:
                alta_libro(libros, &num_libros);
                break;
            case 2:
                baja_libro(libros, &num_libros, prestamos, num_prestamos);
                break;
            case 3:
                listar_libros(libros, num_libros);
                break;
            case 4:
            	
                alta_usuario(usuarios, &num_usuarios);
                break;
            case 5:
                baja_usuario(usuarios, &num_usuarios, prestamos, num_prestamos);
                break;
            case 6:
                listar_usuarios(usuarios, num_usuarios);
                break;
            case 7:
                realizar_prestamo(libros, num_libros, usuarios, num_usuarios, prestamos, &num_prestamos);
                break;
            case 8:
            	realizar_devolucion(libros, num_libros, usuarios, num_usuarios, prestamos, &num_prestamos);
                break;
            case 9:
				listar_prestamos_prestados(prestamos, num_prestamos);
                break;
            case 10:
			    printf("\nIngrese su numero de identificacion: ");
			    char identificacion[20];
			    fflush(stdin);
				scanf("%s", identificacion);
			    listar_prestamos_usuario(prestamos, num_prestamos, identificacion);
			    break;
            case 0:
            	printf("Saliendo del programa...\n");
            	break;
            default:
                printf("Opción no valida. Por favor, elija una opcion valida.\n");
        }
    }while(opcion != 0);

	return 0;
}

//buscardor de libros
int buscar_libro(Libro libros[], int num_libros, char titulo[]) {
    for(int i = 0; i < num_libros; i++) {
        if(strcmp(libros[i].titulo, titulo) == 0) {
            return i;
        }
    }
    return -1;
}
//buscardor de usuarios
int buscar_usuario(Usuario usuarios[], int num_usuarios, char identificacion[]) {
    int i;
    for(i = 0; i < num_usuarios; i++) {
        if(strcmp(usuarios[i].identificacion, identificacion) == 0) {
            return i;
        }
    }
    return -1;
}

//buscador de prestamos
int buscar_prestamo(Prestamo prestamos[], int num_prestamos, char titulo[], char identificacion[]) {
    int i;
    for(i = 0; i < num_prestamos; i++) {
        if(strcmp(prestamos[i].titulo_libro, titulo) == 0 && strcmp(prestamos[i].nombre_usuario, identificacion) == 0) {
            return i;
        }
    }
    return -1;
}

void alta_libro(Libro libros[], int *num_libros) {
	
    if(*num_libros == MAX_LIBROS) {
        printf("No se pueden dar de alta más libros. Se alcanzo el maximo permitido.\n");
        return;
    }

    // Leer datos del libro
    Libro nuevo_libro;
    printf("\n--- DAR DE ALTA LIBRO ---\n");
    printf("Ingrese el titulo del libro: ");
    fflush(stdin);
	gets(nuevo_libro.titulo);
	fflush(stdin);
    printf("Ingrese la edicion del libro: ");
    scanf("%d", &nuevo_libro.edicion);
    printf("Ingrese el autor del libro: ");
    fflush(stdin);
    gets(nuevo_libro.autor);

    // Verificar si el libro ya existe
    int pos = buscar_libro(libros, *num_libros, nuevo_libro.titulo);
    if(pos != -1) {
        printf("El libro ya existe en la lista de libros.\n");
        return;
    }
	
    // Agregar libro a la lista
    libros[*num_libros] = nuevo_libro;
    *num_libros += 1;
    printf("Libro dado de alta exitosamente.\n");
    escribir_libros_archivo(nuevo_libro);
}  

void escribir_libros_archivo(Libro libros) {
    FILE* archivo = fopen("libros.txt","at");
    if(archivo == NULL) {
        printf("No se pudo abrir el archivo\n");
        return;
    }

    fprintf(archivo, "Titulo: %s\nEdicion: %d\nAutor: %s\n", libros.titulo, libros.edicion, libros.autor);
    fprintf(archivo, "---------------------------\n");

    fclose(archivo);
    printf("Datos de libros guardados en el archivo libros.txt\n");
}

void baja_libro(Libro libros[], int *num_libros, Prestamo prestamos[], int num_prestamos) {
    // Verificar si no hay libros
    if(*num_libros == 0) {
        printf("No hay libros en la lista.\n");
        return;
    }

    // Leer título del libro a dar de baja
    printf("\n--- DAR DE BAJA LIBRO ---\n");
	char titulo[100];
	printf("Titulo del libro a dar de baja: ");
	fflush(stdin);
	scanf("%s", titulo);
	titulo[strcspn(titulo, "\n")] = 0; // Quitar el salto de línea
	
	// Buscar el libro
	int indice_libro = buscar_libro(libros, *num_libros, titulo);
	if(indice_libro == -1) {
	    printf("El libro no se encuentra en la biblioteca\n");
	    return;
	}
	
	// Verificar si el libro está prestado
	if(buscar_prestamo(prestamos, num_prestamos, titulo, prestamos->nombre_usuario) != -1) {
		printf("----------------------------------------------------------\n");
	    printf("El libro se encuentra prestado y no puede ser dado de baja\n");
	    printf("----------------------------------------------------------\n");
	    return;
	}
	
	// Eliminar el libro de la lista de libros
	for(int i = indice_libro; i < *num_libros - 1; i++) {
	    libros[i] = libros[i+1];
	}
	(*num_libros)--;
	printf("El libro ha sido eliminado correctamente\n");
}                                    

void listar_libros(Libro libros[], int num_libros) {
	
    if(num_libros == 0) {
        printf("No hay libros registrados.\n");
        return;
    }
    printf("\n--- LISTA DE LIBROS ---\n");
    for(int i = 0; i < num_libros; i++) {
        printf("---------------------\n");
		printf("Titulo: %s\n", libros[i].titulo);
        printf("Edicion: %d\n", libros[i].edicion);
        printf("Autor: %s\n", libros[i].autor);
        printf("---------------------\n");
    }
}

// Dar de alta un usuario
void alta_usuario(Usuario usuarios[], int *num_usuarios) {
    // Verificar si se ha llegado al límite de usuarios
    if(*num_usuarios >= MAX_USUARIOS) {
        printf("No se pueden agregar mas usuarios.\n");
        return;
    }

    // Obtener los datos del usuario
    Usuario nuevo_usuario;
    printf("\n--- AGREGAR USUARIO ---\n");
    printf("Nombre: ");
    fflush(stdin);
	scanf("%s",nuevo_usuario.nombre);
    printf("Identificacion: ");
    fflush(stdin);
    scanf("%s", nuevo_usuario.identificacion);
    printf("Tipo de usuario (estudiante | docente): ");
    scanf("%s", nuevo_usuario.tipo_usuario);

    // Verificar si el usuario ya existe
    if(buscar_usuario(usuarios, *num_usuarios, nuevo_usuario.identificacion) != -1) {
        printf("El usuario ya existe.\n");
        return;
    }

    // Agregar el usuario al arreglo
    usuarios[*num_usuarios] = nuevo_usuario;
    (*num_usuarios)++;
    printf("El usuario ha sido agregado exitosamente.\n");
    guardar_usuario_archivo(nuevo_usuario);
}

void guardar_usuario_archivo(Usuario usuario) {
    FILE *archivo_usuarios = fopen("usuarios.txt", "at");
    if (archivo_usuarios == NULL) {
        printf("No se pudo abrir el archivo de usuarios.\n");
        return;
    }
    
    fprintf(archivo_usuarios, "Nombre: %s\nIdentificacion: %s\nTipo de usuario: %s\n", usuario.nombre, usuario.identificacion, usuario.tipo_usuario);
    fprintf(archivo_usuarios, "---------------------------\n");
    fclose(archivo_usuarios);
    
    printf("Datos del usuario guardados en el archivo usuarios.txt\n");
}


// Dar de baja un usuario
void baja_usuario(Usuario usuarios[], int *num_usuarios, Prestamo prestamos[], int num_prestamos) {
    // Obtener la identificación del usuario
    char identificacion[20];
    printf("\n--- ELIMINAR USUARIO ---\n");
    printf("Identificacion del usuario: ");
    fflush(stdin);
    scanf("%s", identificacion);

    // Verificar si el usuario tiene préstamos pendientes
    int indice_prestamo = buscar_prestamo(prestamos, num_prestamos, prestamos->titulo_libro, identificacion);
    if(indice_prestamo != -1) {
    	printf("---------------------------------------------------------------\n");
        printf("El usuario tiene prestamos pendientes y no puede ser eliminado.\n");
        printf("---------------------------------------------------------------\n");
        return;
    }

    // Buscar el usuario en el arreglo y eliminarlo
    int indice_usuario = buscar_usuario(usuarios, *num_usuarios, identificacion);
    if(indice_usuario == -1) {
        printf("El usuario no existe.\n");
        return;
    }

    for(int i = indice_usuario; i < (*num_usuarios) - 1; i++) {
        usuarios[i] = usuarios[i + 1];
    }
    (*num_usuarios)--;
    printf("El usuario ha sido eliminado exitosamente.\n");
}

// Listar los usuarios
void listar_usuarios(Usuario usuarios[], int num_usuarios) {
    printf("\n--- LISTADO DE USUARIOS ---\n");
    for(int i = 0; i < num_usuarios; i++) {
        printf("-----------------------------\n");
		printf("Nombre: %s\n", usuarios[i].nombre);
        printf("Identificacion: %s\n", usuarios[i].identificacion);
        printf("Tipo de usuario: %s\n", usuarios[i].tipo_usuario);
        printf("-----------------------------\n");
    }
}

// Función para realizar un préstamo
void realizar_prestamo(Libro libros[], int num_libros, Usuario usuarios[], int num_usuarios, Prestamo prestamos[], int *num_prestamos) {
    // Variables
    char identificacion[20];
    char titulo[100];
    int indice_usuario, indice_libro;
    Prestamo prestamo;

    // Pedir identificación de usuario
    printf("\nIngrese identificacion del usuario: ");
    scanf("%s", identificacion);

    // Buscar si el usuario existe
    indice_usuario = buscar_usuario(usuarios, num_usuarios, identificacion);
    if(indice_usuario == -1) {
        printf("\nEl usuario no existe\n");
        return;
    }

    // Pedir título del libro
    printf("\nIngrese titulo del libro: ");
    fflush(stdin);
    scanf(" %[^\n]", titulo);

    // Buscar si el libro existe
    indice_libro = buscar_libro(libros, num_libros, titulo);
    if(indice_libro == -1) {
        printf("\nEl libro no existe\n");
        return;
    }

    // Crear registro de préstamo
    strcpy(prestamo.titulo_libro, titulo);
    strcpy(prestamo.nombre_usuario, usuarios[indice_usuario].identificacion);

    // Pedir fechas de préstamo y devolución
    printf("\nIngrese fecha de prestamo (formato: dd/mm/aaaa): ");
    scanf("%s", prestamo.fecha_prestamo);
    printf("Ingrese fecha de devolucion (formato: dd/mm/aaaa): ");
    scanf("%s", prestamo.fecha_devolucion);

    // Agregar préstamo al arreglo de préstamos
    prestamos[*num_prestamos] = prestamo;
    (*num_prestamos)++;

    // Mostrar mensaje de éxito
    printf("\nEl prestamo se ha realizado exitosamente\n");
}

// Función para realizar una devolución
void realizar_devolucion(Libro libros[], int num_libros, Usuario usuarios[], int num_usuarios, Prestamo prestamos[], int *num_prestamos) {
    char titulo[100];
    char identificacion[20];
    int indice_prestamo;
	printf("\n--- REALIZAR DEVOLUCION ---\n");
    // Pedir título del libro
    printf("Ingrese titulo del libro: ");
    fflush(stdin);
    fgets(titulo, 100, stdin);
    titulo[strlen(titulo) - 1] = '\0';

    // Pedir identificación del usuario
    printf("Ingrese identificacion del usuario: ");
    fflush(stdin);
    scanf("%s", identificacion);

    // Buscar préstamo en la lista
    indice_prestamo = buscar_prestamo(prestamos, *num_prestamos, titulo, identificacion);

    if (indice_prestamo == -1) {
        printf("\nNo se encontro un prestamo con esos datos.\n");
        return;
    }

    // Actualizar disponibilidad del libro
    int indice_libro = buscar_libro(libros, num_libros, titulo);
    libros[indice_libro].edicion++;

    // Actualizar estado del usuario
    int indice_usuario = buscar_usuario(usuarios, num_usuarios, identificacion);
    strcpy(usuarios[indice_usuario].tipo_usuario, "estudiante");

    // Eliminar el préstamo
    for (int i = indice_prestamo; i < *num_prestamos - 1; i++) {
        prestamos[i] = prestamos[i + 1];
    }

    (*num_prestamos)--;

    printf("\nSe ha registrado la devolucion del libro.\n");
}


void listar_prestamos_usuario(Prestamo prestamos[], int num_prestamos, char identificacion[]) {
    printf("\n--- PRESTAMOS DEL USUARIO CON IDENTIFICACION: %s ---\n", identificacion);
    printf("Titulo del libro\tFecha de prestamo\tFecha de devolucion\n");

    for(int i = 0; i < num_prestamos; i++) {
        if(strcmp(prestamos[i].nombre_usuario, identificacion) == 0) {
            printf("-----------------------------------\n");
            printf("%s\t|\t %s\t|\t %s\n", prestamos[i].titulo_libro, prestamos[i].fecha_prestamo, prestamos[i].fecha_devolucion);
        }
    }
}

void listar_prestamos_prestados(Prestamo prestamos[], int num_prestamos) {
    printf("\n--- LISTA DE LIBROS PRESTADOS ---\n");
    for (int i = 0; i < num_prestamos; i++) {
        printf("---------------------\n");
        printf("Libro: %s\n", prestamos[i].titulo_libro);
        printf("Usuario: %s\n", prestamos[i].nombre_usuario);
        printf("Fecha prestamo: %s\n\n", prestamos[i].fecha_prestamo);
        printf("---------------------\n");
    }
}
