# sistemas-de-archivos

El programa necesita llevar el control de los préstamos de libros realizados por los estudiantes y personal docente.

Los datos que desean corresponden a:

Libro
- titulo
- edición
- autor

Usuario
- nombre
- identificación
- tipo usuario (estudiante | docente)

Préstamo
- titulo libro
- nombre usuario
- fecha préstamo
- fecha devolución
Se le pide crear la aplicación utilizando lenguaje C, utilizando un fichero para cada una de las entidades y/o relaciones.

Las estructuras a utilizar son:

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


La aplicación debe permitir realizar como mínimo las siguientes acciones
• Dar de alta y baja
• Libros, Usuarios y Préstamos
• Ver la lista de:
    • Libros, Usuarios y Préstamos
• Listar los libros que tiene a préstamo un usuario determinado
• Listar los libros que se encuentren prestados (puntos extras: también presentar el usuario que tiene prestado el libro )

Nota:
- No se permitirá eliminar libros y/o usuarios que se encuentren prestados.
