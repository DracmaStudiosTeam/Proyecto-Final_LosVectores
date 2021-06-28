//********************************************************************************************************************************************************************************************************
//Nombre			: Final_LosVectores
//Autor				: Los Vectores {AKE GAMBOA ALEJANDRO, BRICENO EUAN RODRIGO DANIEL, NAHUAT CHI JOSE MARTIN, ORTIZ PALACIOS ANDRES ENRIQUE}
//Fecha				: 23/06/2021
//Version			: 1.0
//Descripcion		: Programa de analisis de promedios escolares en ANSI C
//********************************************************************************************************************************************************************************************************

#include <stdio.h>
#include <ctype.h> // toupper
#include <stdlib.h> //System, Exit, Remove
#include <locale.h> // setlocale
#include <string.h> // strlen, strcmp, strcpy
#include <windows.h> // system, gotoxy, getch2
#include <dir.h> //Direcciones

// Macros
#define ARRIBA 'w' // Presionar w para ir hacia arriba
#define ABAJO 's' // Presionar s para ir hacia abajo
#define ENTER 13
#define N 35 // Numero de caracteres que puede contener la variable nombre[N]
#define K 50 // Numero de alumnos
#define M 3 // Numero de grupos en total

// Estructuras
// Estructura de los nombres y las asignaturas
typedef struct
{
	char nombre[N]; // Nombre del alumno
	float esp; // Espanol
	float mate; // Matematicas
	float hist; // Historia
	float cienc; // Ciencias
	float artes; // Artes
	float tecno; // Tecnologia
	float fcye; // Formacion civica y etica
	float prom;
} asig;
// Estructura de los grupos
typedef struct
{
	asig numAlum[K];
} numGrupos;
numGrupos grupos[M]; // Numero de grupos que contienen K alumnos, cada uno

// Prototipos
void menuPrincipal(void); // 1
int solUsuario(void); // 2
void opcEsc(int opc, char usuario[], char defUsuario[], char contra[], char defContra[], int *cont1); // 3
void opc1(char usuario[]); // 3.1
void opc2(char nomContra[]); // 3.2
void opc3(char nomUsuario[], char defUsuario[]); // 3.3
void opc4(char nomContra[], char defContra[]); // 3.4
int opc5(char usuario[], char defUsuario[], char contra[], char defContra[]); // 3.5
void solAccion(int *opc); // 4
void opcEsc2(int opc, int * cont2); // 5
void selAlumno(int opc, int opc2, char opcSel[][100], char grupo[]); // 5.1
void opc2_0(char opcSel[][100], int opc); // 6
void selAsignatura(int numAlum, int opc, int enc, char opcSel[][100], char grupo[]); // 6.1
void visCalificaciones(int grupo, int numAlum, char asig[][30]); // 6.2
void verRanking(char grupo[], int gpo); // 6.3
void modCalificacion(int alum, int indexGrupo, char grupo[], int asig); // 6.4
void iniciarEstructura(int); // Iniciar estructura
int gotoxy(USHORT x, USHORT y); // API de Windows
char getch2(void); // API de Windows
void toString(char [], int); //Convertir int a string
void crearFicherosDirecciones(char *dirname); //Verificar si existen los ficheros y crealos en caso
int existeArchivoAccesar(char *dirname);//Se puede acceder al fichero

// Principal
int main()
{
	setlocale(LC_ALL, ""); // Imprimir caracteres especiales
	menuPrincipal(); // Engloba a todas las funciones utilizadas
	return 0; // Finalizacion sin errores
}

// Menu que se le despegara al usuario
void menuPrincipal(void)
{
	//Direccion en la cual se busca los archivos
	char dirname[50] = "Grupo";
	//Se checa si se tiene datos previos del programa
	crearFicherosDirecciones(dirname);
	
	int dt = 1; // Mantiene inicializado al bucle de manera infinita
	int opc1, opc2; // Determinan la opcion seleccionada
	int cont1 = 1; // Verdadero hasta tener usuario y contrasenia establecidos
	int cont2 = 1; // Verdadero hasta cerrar la sesion
	char usuario[9] = {'U', 's', 'u', 'a', 'r', 'i', 'o', '1'}; // Por defecto
	char contra[9] = {'U', 's', 'u', 'a', 'r', 'i', 'o', '1'}; // Por defecto
	char nomUsuario[100]; // Almacenara el nuevo nombre del usuario
	char nomContra[100]; // Almacenara la nueva contrasenia del usuario
	//Bucle que repite a todo el programa
	do
	{
		// Se procede a solicitar el usuario y la contrasena
		do
		{
			opc1 = solUsuario(); // Se almacena la opcion seleccionada
			opcEsc(opc1, nomUsuario, usuario, nomContra, contra, &cont1); // Se evalua que opcion se escogio
		} while (cont1 !=0);
		// Se procede a desplegar las opciones disponibles, una vez se haya ingresado al programa con exito
		do
		{
			solAccion(&opc2); // Almacenar la opcion seleccionada mediante puntero
			opcEsc2(opc2, &cont2); // Se procede a la opcion seleccionada
		} while (cont2 !=0); // Mientras no se cierre la sesion
		cont2 = 1; // Para que no haya ningun problema
	} while (dt !=0); // Mientras que no se haya iniciado sesion
}

// gotoxy
int gotoxy(USHORT x, USHORT y)
{
	COORD cp = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cp);
}

// getch2
char getch2(void)
{
	char c = 0; // Variable local
	DWORD modo, cont;
	HANDLE ih = GetStdHandle(STD_INPUT_HANDLE);
	// Desactivar la escritura en la terminal
	SetConsoleMode(ih, modo & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT));
	ReadConsoleA(ih, &c, 1, &cont, NULL);
	if (c ==0)
	{
		ReadConsoleA(ih, &c, 1, &cont, NULL);
	}
	SetConsoleMode(ih, modo); // Devolver el control normal
	return c;
}

// Menu principal, en donde se solicita el usuario y la contrasenia
int solUsuario(void)
{
	int i; // Contador
	int var = 0, continuar = 0, selec = 1, tecla; // Variables de control del apuntador (==>)
	const char *clave[] = {"Usuario", "Contraseña", "Entrar", "Añadir Usuario", "Añadir Contraseña", "Salir"};
	const char *titulo[] = {"PROGRAMA", "DE ANÁLISIS", "DE PROMEDIOS", "ESCOLARES"}; // Nombre de la plataforma
	do
	{
		system("CLS"); // Limpiar la pantalla
		system("COLOR 0A"); //Color para la consola
		// Imprimir margenes laterales de presentacion
		for (i = 0; i <=46; i++)
		{
			gotoxy(1+i, 0); printf("*"); // Margen lateral superior
			gotoxy(1+i, 7); printf("*"); // Margen lateral divisor
			gotoxy(1+i, 12); printf("*"); // Margen lateral inferior
		}
		// Imprimir margenes verticales de presentacion
		for (i = 0; i <=11; i++)
		{
			gotoxy(1, 1+i); printf("*"); // Margen vertical izquierdo
			gotoxy(47, 1+i); printf("*"); // Margen vertical derecho
		}
		// Imprimir las opciones del menu principal
		for (i = 0; i <4; i++)
		{
			gotoxy(3, 2+i); printf("%s", titulo[i]);
		}
		gotoxy(12, 1+i); putchar(169);
		gotoxy(1, 13); printf("Los Vectores"); // Imprimir el propietario del programa
		gotoxy(13, 13); putchar(169); printf(" 2021"); // Imprimir la fecha de elaboracion del programa
		for (i = 0; i <6; i++)
		{
			if (i <2)
			{
				gotoxy(25, 2+i); printf("%s", clave[i]); // Imprimir usuario y contrasena de primero
			} else if (i ==2)
			{
				gotoxy(25, 3+i); printf("%s", clave[i]); // Imprimir entrar de segundo
			} else
			{
				gotoxy(29, 5+i); printf("%s", clave[i]); // Imprimir anadir usuario, contrasena y salir de ultimo
			}
		}
		gotoxy(3, 8); printf("OTRAS"); gotoxy(3, 9); printf("OPCIONES");
		// Con esto, se movera la flecha de opciones inferiores
		if ((selec ==3 && tecla ==ABAJO) || (selec ==6 && tecla ==ARRIBA))
		{
			selec = 4; // Para que la flecha (==>) nunca apunte al vacio entre Contrasena y Entrar
		}
		if (selec ==3 && tecla ==ARRIBA)
		{
			selec = 2; // Para que la flecha (==>) nunca apunte al vacio entre Contrasena y Entrar
		}
		if (selec ==5 && tecla ==ABAJO)
		{
			selec = 7; // Para que la flecha (==>) nunca apunte al vacion entre Entrar y Anadir Usuario
		}
		// Ocupar tabulaciones para la flecha (==>)
		if (selec <5)
		{
			var = 0; // Cuando las opciones sean las 3 primeras
		} else
		{
			var = 4; // Cuando las opciones sean las 2 ultimas
		}
		gotoxy(20+var, 1+selec); printf("==>"); // Lee la nueva posicion de la flecha
		// Se encierra entre corchetes la opcion apuntada por la flecha (==>)
		if (selec ==1) // Para cuando la flecha (==>) apunta a Usuario
		{
			gotoxy(24, 1+selec); printf("["); gotoxy(25+strlen(clave[0]), 1+selec); printf("]");
		} else if (selec ==2) // Para cuando la flecha (==>) apunta a Contrasena
		{
			gotoxy(24, 1+selec); printf("["); gotoxy(25+strlen(clave[1]), 1+selec); printf("]");
		} else if (selec ==4) // Para cuando la flecha (==>) apunta a Entrar
		{
			gotoxy(24, 1+selec); printf("["); gotoxy(25+strlen(clave[2]), 1+selec); printf("]");
		} else if (selec ==7) // Para cuando la flecha (==>) apunta a Anadir Usuario
		{
			gotoxy(28, 1+selec); printf("["); gotoxy(29+strlen(clave[3]), 1+selec); printf("]");
		} else if (selec ==8) // Para cuando la flecha (==>) apunta a Anadir Contrasena
		{
			gotoxy(28, 1+selec); printf("["); gotoxy(29+strlen(clave[4]), 1+selec); printf("]");
		} else if (selec ==9) // Para cuando la flecha (==>) apunta a Salir
		{
			gotoxy(28, 1+selec); printf("["); gotoxy(29+strlen(clave[5]), 1+selec); printf("]");
		}
		do
		{
			gotoxy(0, 0); tecla = getch2(); // Lee la posicion de la flecha	
		} while (tecla !=ARRIBA && tecla !=ABAJO && tecla !=ENTER);
		// Cambia la posicion de la flecha con una variable de control
		switch (tecla)
		{
			case ARRIBA:
				selec--; // Disminucion porque se va hacia arriba
				if (selec <1) // Si ya no hay mas opciones arriba
				{
					selec = 9; // Se va hacia abajo
				}
			break;
			case ABAJO:
				selec++; // Aumento porque se va hacia abajo
				if (selec >9) // Si ya no hay mas opciones abajo
				{
					selec = 1; // Se regresa hacia arriba
				}
			break;
			case ENTER:
				continuar = 1; // Se sale del menu para redirigirse a la opcion escogida
			break;
		}
	} while (continuar !=1);
	return selec;
}

// De acuerdo con lo solicitado, se procede a presentarlo (Menu 1)
void opcEsc(int opc, char usuario[], char defUsuario[], char contra[], char defContra[], int *cont1)
{
	system("CLS"); // Limpiar la pantalla
	switch (opc)
	{
		case 1: opc1(usuario); break; // Opcion Usuario
		case 2: opc2(contra); break; // Opcion Contrasena
		case 4: *cont1 = opc5(usuario, defUsuario, contra, defContra); break; // Opcion Entrar
		case 7: opc3(usuario, defUsuario); break; // Opcion Anadir Usuario
		case 8: opc4(contra, defContra); break; // Opcion Anadir Contrasena
		case 9: exit(0); // Opcion Salir
	}	
}

// Opcion 1. Usuario
void opc1(char usuario[])
{
	int i, tecla, cont = 0, def = 1, selec = 1; // Controladores
	do
	{
		system("CLS"); // Limpiar la pantalla
		system("COLOR 0A"); //Color para la consola
		// Imprimir margenes laterales para el titulo
		for (i = 0; i <=strlen("USUARIO")+3; i++)
		{
			gotoxy(1+i, 0); printf("*"); // Margen lateral superior
			gotoxy(1+i, 2); printf("*"); // Margen lateral inferior
		}
		// Imprimir margenes verticales para el titulo
		for (i = 0; i <2; i++)
		{
			gotoxy(1, 1+i); printf("*"); // Margen vertical izquierdo
			gotoxy(strlen("USUARIO")+4, 1+i); printf("*"); // Margen vertical derecho
		}
		gotoxy(3, 1); printf("USUARIO"); // Imprimir el titulo del apartado escogido
		gotoxy(1, 4); printf("Introduzca Su Usuario: "); // Solicitar el usuario
		if (cont ==0) // Solicitar por primera vez / de nuevo el usuario
		{
			fflush(stdin); // Limpiar el buffer
			gets(usuario); // Leer el usuario
		} else
		{
			puts(usuario); // Imprimir el usuario cuando se muevan las flechas
		}
		gotoxy(2, 5+selec); printf("==>"); // Lee la nueva posicion de la flecha
		// Imprime los corchetes que indican que la flecha (==>) esta apuntando
		if (selec ==1)
		{
			gotoxy(6, 5+selec); printf("["); gotoxy(7+strlen("Guardar Cambios"), 5+selec); printf("]");
		} else
		{
			gotoxy(6, 5+selec); printf("["); gotoxy(7+strlen("Editar Usuario"), 5+selec); printf("]");
		}
		// Imprimir las opciones a escoger
		gotoxy(7, 6); printf("Guardar Cambios");
		gotoxy(7, 7); printf("Editar Usuario");
		// Leer el comando especial, el cual fue pulsado
		do
		{
			gotoxy(0, 0); tecla = getch2();
		} while (tecla !=ARRIBA && tecla !=ABAJO && tecla !=ENTER);
		// Definir el valor de selec para mover a la flecha
		switch (tecla)
		{
			case ARRIBA:
				selec--; // Disminucion porque se va hacia arriba
				if (selec <1) // Si ya no hay mas opciones arriba
				{
					selec = 2; // Se va hacia abajo
				}
			break;
			case ABAJO:
				selec++; // Aumento porque se va hacia abajo
				if (selec >2) // Si ya no hay mas opciones abajo
				{
					selec = 1; // Se regresa hacia arriba
				}
			break;
			case ENTER:
				if (selec ==2)
				{
					cont = -1;
				} else
				{
					def = 0;
				}
			break;
		}
		cont++; // Aumentar contador al momento de mover las flechas y no volver a solicitar el usuario
	} while (def !=0);
}

// Opcion 2. Contrasena
void opc2(char nomContra[])
{	
	int i, tecla, cont = 0, def = 1, selec = 1; // Controladores
	do
	{
		system("CLS"); // Limpiar la pantalla
		system("COLOR 0A"); //Color para la consola
		// Imprimir margenes laterales para el titulo
		for (i = 0; i <=strlen("CONTRASEÑA")+3; i++)
		{
			gotoxy(1+i, 0); printf("*"); // Margen lateral superior
			gotoxy(1+i, 2); printf("*"); // Margen lateral inferior
		}
		// Imprimir margenes verticales para el titulo
		for (i = 0; i <2; i++)
		{
			gotoxy(1, 1+i); printf("*"); // Margen vertical izquierdo
			gotoxy(strlen("CONTRASEÑA")+4, 1+i); printf("*"); // Margen vertical derecho
		}
		gotoxy(3, 1); printf("CONTRASEÑA"); // Imprimir el titulo del apartado escogido
		gotoxy(1, 4); printf("Introduzca Su Contraseña: "); // Solicitar la contrasena
		if (cont ==0) // Solicitar por primera vez / de nuevo la contrasena
		{
			fflush(stdin); // Limpiar el buffer
			gets(nomContra); // Leer la contrasena
		} else
		{
			puts(nomContra); // Imprimir la contrasena cuando se muevan las flechas
		}
		gotoxy(2, 5+selec); printf("==>"); // Lee la nueva posicion de la flecha
		// Imprime los corchetes que indican que la flecha (==>) esta apuntando
		if (selec ==1)
		{
			gotoxy(6, 5+selec); printf("["); gotoxy(7+strlen("Guardar Cambios"), 5+selec); printf("]");
		} else
		{
			gotoxy(6, 5+selec); printf("["); gotoxy(7+strlen("Editar Contraseña"), 5+selec); printf("]");
		}
		// Imprimir las opciones a escoger
		gotoxy(7, 6); printf("Guardar Cambios");
		gotoxy(7, 7); printf("Editar Contraseña");
		// Leer el comando especial, el cual fue pulsado
		do
		{
			gotoxy(0, 0); tecla = getch2();
		} while (tecla !=ARRIBA && tecla !=ABAJO && tecla !=ENTER);
		// Definir el valor de selec para mover a la flecha
		switch (tecla)
		{
			case ARRIBA:
				selec--; // Disminucion porque se va hacia arriba
				if (selec <1) // Si ya no hay mas opciones arriba
				{
					selec = 2; // Se va hacia abajo
				}
			break;
			case ABAJO:
				selec++; // Aumento porque se va hacia abajo
				if (selec >2) // Si ya no hay mas opciones abajo
				{
					selec = 1; // Se regresa hacia arriba
				}
			break;
			case ENTER:
				if (selec ==2)
				{
					cont = -1;
				} else
				{
					def = 0;
				}
			break;
		}
		cont++; // Aumentar contador al momento de mover las flechas y no volver a solicitar el usuario
	} while (def !=0);
}

// Opcion 3. Anadir Usuario
void opc3(char nomUsuario[], char defUsuario[])
{
	int i, tecla, cont = 0, def = 1, selec = 1, mostrar = 0; // Controladores
	do
	{
		system("CLS"); // Limpiar la pantalla
		system("COLOR 0A"); //Color para la consola
		// Imprimir margenes laterales para el titulo
		for (i = 0; i <=strlen("AÑADIR USUARIO")+3; i++)
		{
			gotoxy(1+i, 0); printf("*"); // Margen lateral superior
			gotoxy(1+i, 2); printf("*"); // Margen lateral inferior
		}
		// Imprimir margenes verticales para el titulo
		for (i = 0; i <2; i++)
		{
			gotoxy(1, 1+i); printf("*"); // Margen vertical izquierdo
			gotoxy(strlen("AÑADIR USUARIO")+4, 1+i); printf("*"); // Margen vertical derecho
		}
		gotoxy(3, 1); printf("AÑADIR USUARIO"); // Imprimir el titulo del apartado escogido
		gotoxy(1, 4); printf("**Usuario Anterior: ");
		// Mostrar / ocultar usuario anterior inmediato
		if (mostrar !=0)
		{
			gotoxy(strlen("**Usuario Anterior: ")+i-1, 4); printf("%s", defUsuario); // Mostrar usuario anterior inmedianto
		} else
		{
			for (i = 0; i <strlen(defUsuario); i++)
			{
				gotoxy(strlen("**Usuario Anterior: ")+i+1, 4); printf("#"); // Ocultar usuario anterior inmediato
			}
		}
		gotoxy(1, 5); printf("Introduzca Su Usuario Nuevo: "); // Solicitar el usuario nuevo
		if (cont ==0) // Solicitar por primera vez / de nuevo el usuario nuevo
		{
			fflush(stdin); // Limpiar el buffer
			gets(nomUsuario); // Leer el usuario nuevo
			strcpy(defUsuario, nomUsuario); // Actualizar el nombre de usuario
		} else
		{
			puts(nomUsuario); // Imprimir el usuario nuevo cuando se muevan las flechas
		}
		gotoxy(2, 6+selec); printf("==>"); // Lee la nueva posicion de la flecha
		// Imprime los corchetes que indican que la flecha (==>) esta apuntando
		if (selec ==1)
		{
			gotoxy(6, 6+selec); printf("["); gotoxy(7+strlen("Guardar Cambios"), 6+selec); printf("]");
		} else if (selec ==2)
		{
			gotoxy(6, 6+selec); printf("["); gotoxy(6+strlen("Editar Usuario Nuevo"), 6+selec); printf("]");
		} else
		{
			gotoxy(6, 6+selec); printf("["); gotoxy(7+strlen("Mostrar Usuario Anterior"), 6+selec); printf("]");
		}
		// Imprimir las opciones a escoger
		gotoxy(7, 7); printf("Guardar Cambios");
		gotoxy(7, 8); printf("Editar Usario Nuevo");
		gotoxy(7, 9); printf("Mostrar Usuario Anterior");
		// Leer el comando especial, el cual fue pulsado
		do
		{
			gotoxy(0, 0); tecla = getch2();
		} while (tecla !=ARRIBA && tecla !=ABAJO && tecla !=ENTER);
		// Definir el valor de selec para mover a la flecha
		switch (tecla)
		{
			case ARRIBA:
				selec--; // Disminucion porque se va hacia arriba
				if (selec <1) // Si ya no hay mas opciones arriba
				{
					selec = 3; // Se va hacia abajo
				}
			break;
			case ABAJO:
				selec++; // Aumento porque se va hacia abajo
				if (selec >3) // Si ya no hay mas opciones abajo
				{
					selec = 1; // Se regresa hacia arriba
				}
			break;
			case ENTER:
				if (selec ==2)
				{
					cont = -1;	
				} else if (selec ==3)
				{
					mostrar = 1; // Para que muestre el usuario anterior
				} else
				{
					def = 0;
				}
			break;
		}
		cont++; // Aumentar contador al momento de mover las flechas y no volver a solicitar el usuario
	} while (def !=0);
}

// Opcion 4. Anadir Contrasena
void opc4(char nomContra[], char defContra[])
{
	int i, tecla, cont = 0, def = 1, selec = 1, mostrar = 0; // Controladores
	do
	{
		system("CLS"); // Limpiar la pantalla
		system("COLOR 0A"); //Color para la consola
		// Imprimir margenes laterales para el titulo
		for (i = 0; i <=strlen("AÑADIR CONTRASEÑA")+3; i++)
		{
			gotoxy(1+i, 0); printf("*"); // Margen lateral superior
			gotoxy(1+i, 2); printf("*"); // Margen lateral inferior
		}
		// Imprimir margenes verticales para el titulo
		for (i = 0; i <2; i++)
		{
			gotoxy(1, 1+i); printf("*"); // Margen vertical izquierdo
			gotoxy(strlen("AÑADIR CONTRASEÑA")+4, 1+i); printf("*"); // Margen vertical derecho
		}
		gotoxy(3, 1); printf("AÑADIR CONTRASEÑA"); // Imprimir el titulo del apartado escogido
		gotoxy(1, 4); printf("**Contraseña Anterior: ");
		// Mostrar / ocultar contrasena anterior inmediata
		if (mostrar !=0)
		{
			gotoxy(strlen("**Contraseña Anterior: ")+i-1, 4); printf("%s", defContra); // Mostrar contrasena anterior inmedianta
		} else
		{
			for (i = 0; i <strlen(defContra); i++)
			{
				gotoxy(strlen("**Contraseña Anterior: ")+i+1, 4); printf("#"); // Ocultar contrasena anterior inmediata
			}
		}
		gotoxy(1, 5); printf("Introduzca Su Contraseña Nueva: "); // Solicitar la contrasena nueva
		if (cont ==0) // Solicitar por primera vez / de nuevo la contrasena nueva
		{
			fflush(stdin); // Limpiar el buffer
			gets(nomContra); // Leer la contrasena nueva
			strcpy(defContra, nomContra); // Actualizar la contrasena de usuario
		} else
		{
			puts(nomContra); // Imprimir la contrasena nueva cuando se muevan las flechas
		}
		gotoxy(2, 6+selec); printf("==>"); // Lee la nueva posicion de la flecha
		// Imprime los corchetes que indican que la flecha (==>) esta apuntando
		if (selec ==1)
		{
			gotoxy(6, 6+selec); printf("["); gotoxy(7+strlen("Guardar Cambios"), 6+selec); printf("]");
		} else if (selec ==2)
		{
			gotoxy(6, 6+selec); printf("["); gotoxy(7+strlen("Editar Contraseña Nueva"), 6+selec); printf("]");
		} else
		{
			gotoxy(6, 6+selec); printf("["); gotoxy(7+strlen("Mostrar Contraseña Anterior"), 6+selec); printf("]");
		}
		// Imprimir las opciones a escoger
		gotoxy(7, 7); printf("Guardar Cambios");
		gotoxy(7, 8); printf("Editar Contraseña Nueva");
		gotoxy(7, 9); printf("Mostrar Contraseña Anterior");
		// Leer el comando especial, el cual fue pulsado
		do
		{
			gotoxy(0, 0); tecla = getch2();
		} while (tecla !=ARRIBA && tecla !=ABAJO && tecla !=ENTER);
		// Definir el valor de selec para mover a la flecha
		switch (tecla)
		{
			case ARRIBA:
				selec--; // Disminucion porque se va hacia arriba
				if (selec <1) // Si ya no hay mas opciones arriba
				{
					selec = 3; // Se va hacia abajo
				}
			break;
			case ABAJO:
				selec++; // Aumento porque se va hacia abajo
				if (selec >3) // Si ya no hay mas opciones abajo
				{
					selec = 1; // Se regresa hacia arriba
				}
			break;
			case ENTER:
				if (selec ==2)
				{
					cont = -1;	
				} else if (selec ==3)
				{
					mostrar = 1; // Para que muestre la contrasena anterior
				} else
				{
					def = 0;
				}
			break;
		}
		cont++; // Aumentar contador al momento de mover las flechas y no volver a solicitar el usuario
	} while (def !=0);
}

// Opcion 5. Entrar
int opc5(char usuario[], char defUsuario[], char contra[], char defContra[])
{
	int cont1, i, tecla, def = 1, selec = 1; // Controladores
	do
	{
		system("CLS"); // Limpiar la pantalla
		system("COLOR 0A"); //Color para la consola
		// Imprimir margenes laterales para el titulo
		for (i = 0; i <=strlen("ENTRAR")+3; i++)
		{
			gotoxy(1+i, 0); printf("*"); // Margen lateral superior
			gotoxy(1+i, 2); printf("*"); // Margen lateral inferior
		}
		// Imprimir margenes verticales para el titulo
		for (i = 0; i <2; i++)
		{
			gotoxy(1, 1+i); printf("*"); // Margen vertical izquierdo
			gotoxy(strlen("ENTRAR")+4, 1+i); printf("*"); // Margen vertical derecho
		}
		gotoxy(3, 1); printf("ENTRAR"); // Imprimir el titulo del apartado escogido
		if (strcmp(usuario, defUsuario) ==0 && strcmp(contra, defContra) ==0)
		{	
			gotoxy(1, 4); printf("Nombre De Usuario Y Password Correctos");
			cont1 = 0; // Si el usuario y contrasena son correctos
		} else
		{
			gotoxy(1, 4); printf("Nombre De Usuario O Password Incorrectos");
		}
		// Leer el comando especial, el cual fue pulsado, de acuerdo a si son o no correcto los datos
		do
		{
			if (cont1 !=0) // Si el usuario y contrasena son correctos
			{
				// Imprimir las opciones a escoger
				gotoxy(7, 6); printf("Reintentar");
				gotoxy(7, 7); printf("Volver Al Menú Principal");
				gotoxy(2, 5+selec); printf("==>"); // Lee la nueva posicion de la flecha
				// Imprime los corchetes que indican que la flecha (==>) esta apuntando
				if (selec ==1)
				{
					gotoxy(6, 5+selec); printf("["); gotoxy(7+strlen("Reintentar"), 5+selec); printf("]");
				} else if (selec ==2)
				{
					gotoxy(6, 5+selec); printf("["); gotoxy(7+strlen("Volver Al Menú Principal"), 5+selec); printf("]");
				}
				gotoxy(0, 0); tecla = getch2();
				// Definir el valor de selec para mover a la flecha
				switch (tecla)
				{
					case ARRIBA:
						selec--; // Disminucion porque se va hacia arriba
						if (selec <1) // Si ya no hay mas opciones arriba
						{
							selec = 2; // Se va hacia abajo
						}
					break;
					case ABAJO:
						selec++; // Aumento porque se va hacia abajo
						if (selec >2) // Si ya no hay mas opciones abajo
						{
							selec = 1; // Se regresa hacia arriba
						}
					break;
					case ENTER:
						if (selec !=1)
						{
							def = 0; // Para salirse y volver al inicio
						}
					break;
				}
			} else
			{
				def = 0; // Para salirse y volver al inicio
			}
		} while ((tecla !=ARRIBA && tecla !=ABAJO && tecla !=ENTER) && def !=0); // Mientras que los datos no sean correctos
	} while (def !=0); // Mientras que aun no sean correcto los datos
	return cont1; // Devolver el valor del contador el cual se devuelve cuando los datos son correctos
}

// Menu secundario, donde se solicita la accion a realizar, una vez iniciado sesion
void solAccion(int *opc)
{
	int i; // Contador
	int var = 0, continuar = 0, selec = 1, tecla; // Variables de control del apuntador (==>)
	const char *titulo[] = {"PROGRAMA", "DE ANÁLISIS", "DE PROMEDIOS", "ESCOLARES"}; // Nombre de la plataforma
	const char *opciones[] = {"Modificar Calificaciones", "Visualizar Calificaciones", "Visualizar Ranking"}; // Opciones
	do
	{
		system("CLS"); // Limpiar la pantalla
		system("COLOR 0A"); //Color para la consola
		// Imprimir margenes laterales de presentacion
		for (i = 0; i <=47; i++)
		{
			gotoxy(1+i, 0); printf("*"); // Margen lateral superior
			gotoxy(1+i, 2); printf("*"); // Margen lateral divisor
			gotoxy(1+i, 9); printf("*"); // Margen lateral inferior
		}
		// Imprimir margenes verticales de presentacion
		for (i = 0; i <=7; i++)
		{
			gotoxy(1, 1+i); printf("*"); // Margen vertical izquierdo
			gotoxy(48, 1+i); printf("*"); // Margen vertical derecho
		}
			for (i = 0; i <4; i++)
			{
				gotoxy(3, 4+i); printf("%s", titulo[i]); // Imprimir el titulo
			}
		// Imprimir las opciones del menu
		for (i = 0; i <2; i++)
		{
			gotoxy(22, 4+i); printf("%s", opciones[i]); // Imprimir las primeras 2 opciones
		}
		gotoxy(22, 7); printf("%s", opciones[i]); // Imprimir la ultima opcion
		gotoxy(12, 7); putchar(169); // Imprimir el logo de marca registrada
		gotoxy(34, 1); printf("Cerrar Sesión");
		// Para no imprimir la flecha (==>) entre los espacios de las opciones
		if (selec ==3 && tecla ==ABAJO)
		{
			selec = 4;
		} else if (selec ==3 && tecla ==ARRIBA)
		{
			selec = 2;
		} else if (selec ==0 && tecla ==ARRIBA)
		{
			selec = -2;
		} else if (selec ==-1 && tecla ==ABAJO)
		{
			selec = 1;
		}
		if (selec ==-2) // Para cuando se encuentre senalando la opcion Cerrar Sesion
		{
			var = 12; // Tabular la flecha
		} else
		{
			var = 0; // No tabular la flecha
		}
		gotoxy(17+var, 3+selec); printf("==>"); // Imprimir la flecha (==>)
		// Encerrar con corchetes la opcion que actualmente apunta la flecha (==>)
		if (selec ==1)
		{
			gotoxy(21, 3+selec); printf("["); gotoxy(22+strlen(opciones[0]), 3+selec); printf("]");
		} else if (selec ==2)
		{
			gotoxy(21, 3+selec); printf("["); gotoxy(22+strlen(opciones[1]), 3+selec); printf("]");
		} else if (selec ==4)
		{
			gotoxy(21, 3+selec); printf("["); gotoxy(22+strlen(opciones[2]), 3+selec); printf("]");
		} else
		{
			gotoxy(33, 3+selec); printf("["); gotoxy(47, 3+selec); printf("]");
		}
		do
		{
			gotoxy(0, 0); tecla = getch2(); // Lee la posicion de la flecha	
		} while (tecla !=ARRIBA && tecla !=ABAJO && tecla !=ENTER);
		// Cambia la posicion de la flecha con una variable de control
		switch (tecla)
		{
			case ARRIBA:
				selec--; // Disminucion porque se va hacia arriba
				if (selec <-2) // Si ya no hay mas opciones arriba
				{
					selec = 4; // Se va hacia abajo
				}
			break;
			case ABAJO:
				selec++; // Aumento porque se va hacia abajo
				if (selec >4) // Si ya no hay mas opciones abajo
				{
					selec = -2; // Se regresa hacia arriba
				}
			break;
			case ENTER:
				continuar = 1; // Se sale del menu para redirigirse a la opcion escogida
			break;
		}
	} while (continuar !=1); // Mientras no se haya seleccionado alguna opcion
	*opc = selec; // Guardar la opcion seleccionada
}

// De acuerdo con lo solicitado, se procede a presentarlo (Menu 2)
void opcEsc2(int opc, int *cont2)
{
	char opciones[4][100] = {"Modificar Calificaciones", "Visualizar Calificaciones", "Visualizar Ranking"}; // Opciones
	system("CLS"); // Limpiar la pantalla
	switch(opc)
	{
		case -2: *cont2 = 0; break; // Opcion Cerrar Sesion
		case 1: opc = 0; opc2_0(opciones, opc); break; // Opcion Modificar Calificaciones
		case 2: opc = 1; opc2_0(opciones, opc); break; // Opcion Visualizar Calificaciones
		case 4: opc = 2; opc2_0(opciones, opc); break; // Opcion Visualizar Ranking
	}
}

// Opcion 1, 2, 3, para las 3 opciones se utiliza una misma funcion
void opc2_0(char opcSel[][100], int opc)
{
	int i, tecla, def = 1, selec = 1, var = 0; // Controladores
	char grupos[4] = {'A', 'B', 'C'};
	do
	{
		for (i = 0; i <=strlen(opcSel[opc]); i++)
		{
			opcSel[opc][i] = toupper(opcSel[opc][i]); // Pasar a mayusculas al titulo seleccionado
		}
		system("CLS"); // Limpiar la pantalla
		system("COLOR 0A"); //Color para la consola
		// Imprimir margenes laterales
		for (i = 0; i <=strlen("Visualizar Calificaciones")+3; i++)
		{
			gotoxy(1+i, 0); printf("*"); // Margen lateral superior
			gotoxy(1+i, 2); printf("*"); // Margen lateral delineador
			gotoxy(1+i, 11); printf("*"); // Margen lateral inferior
		}
		// Imprimir margenes verticales
		for (i = 0; i <11; i++)
		{
			gotoxy(1, 1+i); printf("*"); // Margen vertical izquierdo
			gotoxy(strlen("Visualizar Calificaciones")+4, 1+i); printf("*"); // Margen vertical derecho
		}
		gotoxy(3, 1); printf(opcSel[opc]); // Imprimir el titulo del apartado escogido
		gotoxy(3, 4); printf("Seleccionar Grupo:"); // Solicitar el grupo a editar
		// Mueve la coordenada x de acuerdo con la posicion de selec
		if (selec ==4)
		{
			var = 10; // Si selec senala a Regresar
		} else
		{
			var = 0; // Si selec senala a A, B, C
		}
		gotoxy(4+var, 5+selec); printf("==>"); // Lee la nueva posicion de la flecha
		// Imprime los corchetes que indican que la flecha (==>) esta apuntando
		if (selec !=4)
		{
			gotoxy(8, 5+selec); printf("["); gotoxy(9+strlen("A"), 5+selec); printf("]"); // Si los corchetes senalan a A, B, C
		} else
		{
			gotoxy(18, 5+selec); printf("["); gotoxy(19+strlen("Regresar"), 5+selec); printf("]"); // Si Senalan a Regresar
		}
		// Imprimir las opciones a escoger
		gotoxy(9, 6); printf("A"); // Grupo A
		gotoxy(9, 7); printf("B"); // Grupo B
		gotoxy(9, 8); printf("C"); // Grupo C
		gotoxy(19, 9); printf("Regresar"); // Para regresar al menu 2
		// Leer el comando especial, el cual fue pulsado
		do
		{
			gotoxy(0, 0); tecla = getch2();
		} while (tecla !=ARRIBA && tecla !=ABAJO && tecla !=ENTER);
		// Definir el valor de selec para mover a la flecha
		switch (tecla)
		{
			case ARRIBA:
				selec--; // Disminucion porque se va hacia arriba
				if (selec <1) // Si ya no hay mas opciones arriba
				{
					selec = 4; // Se va hacia abajo
				}
			break;
			case ABAJO:
				selec++; // Aumento porque se va hacia abajo
				if (selec >4) // Si ya no hay mas opciones abajo
				{
					selec = 1; // Se regresa hacia arriba
				}
			break;
			case ENTER:
				if (opc !=2) // Para que la seleccion de los alumnos aparezca nada mas en MODIFICAR CALIFICACIONES y VISUALIZAR CALIFICACIONES
				{
					switch (selec) // De acuerdo a que grupo se haya escogido
					{
						case 1: selAlumno(0, opc, opcSel, grupos); break; // Si se selecciona el grupo A
						case 2: selAlumno(1, opc, opcSel, grupos); break; // Si se selecciona el grupo B
						case 3: selAlumno(2, opc, opcSel, grupos); break; // Si se selecciona el grupo C
						case 4: def = 0; break; // Para la opcion Regresar
					}
				} else
				{
					
					// Se procede a desplegar el ranking, de acuerdo con el grupo seleccionado
					switch(selec)
					{
						case 1: verRanking(grupos, 0); break; // Si se selecciona el grupo A
						case 2: verRanking(grupos, 1); break; // Si se selecciona el grupo B
						case 3: verRanking(grupos, 2); break; // Si se selecciona el grupo C
						case 4: def = 0; break; // Para la opcion Regresar
					}
				}	
			break;
		}
	} while (def !=0); // Mientras no se haya seleccionado aun, ninguna opcion
}

// Opcion que despliega la lista del grupo seleccionado. Funge para los 3 grupos existentes
void selAlumno(int opc, int opc2, char opcSel[][100], char grupo[])
{
	int i, tecla, def = 1, selec = 1, var = 0; // Controladores
	do
	{
		for (i = 0; i <=strlen(opcSel[opc2]); i++)
		{
			opcSel[opc2][i] = toupper(opcSel[opc2][i]); // Pasar a mayusculas el encabezado seleccionado
		}
		system("CLS"); // Limpiar la pantalla
		system("COLOR 0A"); //Color para la consola
		// Imprimir margenes laterales
		for (i = 0; i <=40; i++)
		{
			gotoxy(1+i, 0); printf("*"); // Margen lateral superior
			gotoxy(1+i, 2); printf("*"); // Margen lateral delineador
			gotoxy(1+i, 4); printf("*"); // Margen lateral delineador
			gotoxy(1+i, K+9); printf("*"); // Margen lateral inferior
		}
		// Imprimir margenes verticales
		for (i = 0; i <K+8; i++)
		{
			gotoxy(1, 1+i); printf("*"); // Margen vertical izquierdo
			gotoxy(41, 1+i); printf("*"); // Margen vertical derecho
		}
		gotoxy(3, 1); printf(opcSel[opc2]); // Imprimir el titulo del apartado escogido
		gotoxy(30, 3); printf("*"); gotoxy(32, 3); printf("Grupo: "); gotoxy (39, 3); putchar(grupo[opc]); // Imprimir el grupo seleccionado
		gotoxy(3, 5); printf("Seleccionar Alumno:");
		// Mueve la coordenada x de acuerdo con la posicion de selec
		if (selec ==51)
		{
			var = 21; // Si selec senala a Regresar
		} else
		{
			var = 0; // Si selec senala a A, B, C
		}
		gotoxy(6+var, 6+selec); printf("==>"); // Lee la nueva posicion de la flecha
		// Imprime los corchetes que indican que la flecha (==>) esta apuntando
		if (selec !=51)
		{
			gotoxy(10, 6+selec); printf("["); gotoxy(11+strlen("Nombre_Alumno00"), 6+selec); printf("]"); // Si los corchetes senalan a cualquier alumno
		} else
		{
			gotoxy(31, 6+selec); printf("["); gotoxy(32+strlen("Regresar"), 6+selec); printf("]"); // Si Senalan a Regresar
		}
		// Imprimir la lista de los nombres de los alumnos registrados, previo a la utilizacion de este programa
		for (i = 0; i <K; i++)
		{
			//strcpy(grupos[opc].numAlum[i].nombre, "Nombre_Alumno"); // Imprimir el nombre de los alumno del grupo seleccionado
			gotoxy(11, 7+i); printf("%s", grupos[opc].numAlum[i].nombre);
			if (i <9)
			{
				gotoxy(11+strlen("Nombre_Alumno"), 7+i); printf("0%d", i+1); // Para los primeros 10 alumnos
			} else
			{
				gotoxy(11+strlen("Nombre_Alumno"), 7+i); printf("%d", i+1); // Para los 40 alumnos restantes
			}
		}
		gotoxy(32, K+7); printf("Regresar"); // Para regresar al menu MODIFICAR CALIFICACIONES
		// Leer el comando especial, el cual fue pulsado
		do
		{
			gotoxy(0, 0); tecla = getch2();
		} while (tecla !=ARRIBA && tecla !=ABAJO && tecla !=ENTER);
		// Definir el valor de selec para mover a la flecha
		switch (tecla)
		{
			case ARRIBA:
				selec--; // Disminucion porque se va hacia arriba
				if (selec <1) // Si ya no hay mas opciones arriba
				{
					selec = K+1; // Se va hacia abajo
				}
			break;
			case ABAJO:
				selec++; // Aumento porque se va hacia abajo
				if (selec >51) // Si ya no hay mas opciones abajo
				{
					selec = 1; // Se regresa hacia arriba
				}
			break;
			case ENTER:
				
				if (selec !=51)
				{
					selAsignatura(selec-1, opc, opc2, opcSel, grupo);
				} else
				{
					def = 0; break; // Para la opcion Regresar
				}
			break;
		}
	} while (def !=0); // Mientras no se haya seleccionado aun, ninguna opcion
}

// Opcion que despliega la lista de asignaturas del plan de estudios, una vez se haya seleccionado el alumno
// Funge para los 3 grupos existentes, para MODIFICAR CALIFICACIONES, y para VISUALIZAR CALIFICACIONES
void selAsignatura(int numAlum, int opc, int enc, char opcSel[][100], char grupo[])
{
	int i, tecla, def = 1, selec = 1, var = 0, tab, tab2, tab3; // Controladores
	char asig[8][30] = {"Español", "Matemáticas", "Historia", "Ciencias", "Artes", "Tecnología", "Formación Cívica Y Ética"};
	do
	{
		for (i = 0; i <=strlen(opcSel[enc]); i++)
		{
			opcSel[enc][i] = toupper(opcSel[enc][i]); // Pasar a mayusculas el encabezado seleccionado
		}
		system("CLS"); // Limpiar la pantalla
		system("COLOR 0A"); //Color para la consola
		if (enc ==0) // Para MODIFICAR CALIFICACIONES
		{
			tab = 0; // Para y
			tab2 = 0; // Para x
			tab3 = 0; // Para x
		} else // Para VISUALIZAR CALIFICACIONES
		{
			tab = 1; // Para y
			tab2 = 33; // Para x
			tab3 = 3; // Para x
		}
		// Imprimir margenes laterales
		for (i = 0; i <=49+tab; i++)
		{
			gotoxy(1+i, 0); printf("*"); // Margen lateral superior
			gotoxy(1+i, 2); printf("*"); // Margen lateral delineador
			gotoxy(1+i, 4); printf("*"); // Margen lateral delineador
			gotoxy(1+i, 6); printf("*"); // Margen lateral delineador
			gotoxy(1+i, 19+tab); printf("*"); // Margen lateral inferior
		}
		// Imprimir margenes verticales
		for (i = 0; i <19+tab; i++)
		{
			gotoxy(1, 1+i); printf("*"); // Margen vertical izquierdo
			gotoxy(50+tab, 1+i); printf("*"); // Margen vertical derecho
		}
		gotoxy(3, 1); printf(opcSel[enc]); // Imprimir el titulo del apartado escogido
		gotoxy(39+tab, 3); printf("* Grupo: "); gotoxy (48+tab, 3); putchar(grupo[opc]); // Imprimir el grupo seleccionado
		gotoxy(3, 5); printf("%s", grupos[opc].numAlum[numAlum].nombre); // Imprimir el nombre del alumno
		if (numAlum <9)
		{
			gotoxy(16, 5); printf("0%d", numAlum+1); // Imprime el numero de los primeros 10 alumnos
		} else
		{
			gotoxy(16, 5); printf("%d", numAlum+1); // Imprime el numero de los 40 alumnos restantes
		}
		if (enc ==0)
		{
			gotoxy(3, 8); printf("Seleccionar Asignatura:"); // Para MODIFICAR CALIFICACIONES
		} else
		{
			gotoxy(3, 8); printf("Calificaciones Por Asignatura:"); // Para VISUALIZAR CALIFICACIONES
		}
		// Imprimir la lista de asignaturas propuestas en el plan de estudios
		for (i = 0; i <8; i++)
		{
			gotoxy(11-tab3, 10+i); printf("%s", asig[i]);
		}
		gotoxy(41-tab2, 17+tab); printf("Regresar"); // Imprimir la etiqueta regresar
		// De acuerdo con el encabezado escogido, se procede a MODIFICAR CALIFICACIONES o a VISUALIZAR CALIFICACIONES
		if (enc ==0) // Para MODIFICAR CALIFICACIONES
		{
			// Mueve la coordenada x de acuerdo con la posicion de selec
			if (selec ==8)
			{
				var = 30; // Si selec senala a Regresar
			} else
			{
				var = 0; // Si selec senala a alguna asignatura propuesta en el plan de estudios
			}
			gotoxy(6+var, 9+selec); printf("==>"); // Lee la nueva posicion de la flecha
			// Imprime los corchetes que indican que la flecha (==>) esta apuntando
			if (selec !=8)
			{
				gotoxy(10, 9+selec); printf("["); gotoxy(11+strlen(asig[selec-1]), 9+selec); printf("]"); // Si los corchetes senalan a alguna asignatura
			} else
			{
				gotoxy(40, 9+selec); printf("["); gotoxy(41+strlen("Regresar"), 9+selec); printf("]"); // Si Senalan a Regresar
			}
			// Leer el comando especial, el cual fue pulsado
			do
			{
				gotoxy(0, 0); tecla = getch2();
			} while (tecla !=ARRIBA && tecla !=ABAJO && tecla !=ENTER);
			// Definir el valor de selec para mover a la flecha
			switch (tecla)
			{
				case ARRIBA:
					selec--; // Disminucion porque se va hacia arriba
					if (selec <1) // Si ya no hay mas opciones arriba
					{
						selec = 8; // Se va hacia abajo
					}
				break;
				case ABAJO:
					selec++; // Aumento porque se va hacia abajo
					if (selec >8) // Si ya no hay mas opciones abajo
					{
						selec = 1; // Se regresa hacia arriba
					}
				break;
				case ENTER:
					if (selec !=8) // Si se selecciona alguna asignatura del plan de estudios
					{
						modCalificacion(numAlum, opc, grupo, selec); // Presentar la interfaz de usuario en la que se le solicitara el cambio al usuario, de la calificacion
					} else
					{
						def = 0; // Para la opcion Regresar
					}
			}
		} else // Para VISUALIZAR CALIFICACIONES
		{
			gotoxy(3, 18); printf("==>"); // Imprime la flecha en la opcion Regresar
			gotoxy(7, 18); printf("["); gotoxy(8+strlen("Regresar"), 18); printf("]"); // Imprime la etiqueta Regresar
			visCalificaciones(opc, numAlum, asig); // Visualizar las calificaciones mediante esta funcion
			// Solamente lee al comando especial ENTER
			do
			{
				gotoxy(0, 0); tecla = getch2();
			} while (tecla !=ARRIBA && tecla !=ABAJO && tecla !=ENTER);
			// Para cuando se haya finalizado la visualizacion de las calificaciones
			if (tecla ==ENTER)
			{
				def = 0; // Para cuando se presione a Regresar
			}
		}
	} while (def !=0); // Mientras no se haya seleccionado aun, ninguna opcion
}

// Presenta la interfaz de usuario en la que el usuario podra ingresar la nota nueva, la cual la haya considerado pertinente el usuario
void modCalificacion(int alum, int indexGrupo, char grupo[], int asig)
{
	int i, tecla, cont = 0, def = 1, selec = 1; // Controladores
	// Asignaturas del plan de estudios de la escuela secundaria
	char materias[7][30] = {"Español", "Matemáticas", "Historia", "Ciencias", "Artes", "Tecnología", "Formación Cívica Y Ética"};
	do
	{
		system("CLS"); // Limpiar la pantalla
		system("COLOR 0A"); //Color para la consola
		// Imprimir margenes laterales para el titulo
		for (i = 0; i <=strlen(materias[asig-1])+3; i++)
		{
			gotoxy(1+i, 0); printf("*"); // Margen lateral superior
			gotoxy(1+i, 2); printf("*"); // Margen lateral inferior
		}
		// Imprimir margenes verticales para el titulo
		for (i = 0; i <2; i++)
		{
			gotoxy(1, 1+i); printf("*"); // Margen vertical izquierdo
			gotoxy(strlen(materias[asig-1])+4, 1+i); printf("*"); // Margen vertical derecho
		}
		gotoxy(3, 1); printf(materias[asig-1]); // Imprimir la asignatura escogida
		gotoxy(1, 4); printf("Alumno: "); puts(grupos[indexGrupo].numAlum[alum].nombre); // Imprimir el nombre del alumno
		if (alum <9)
		{
			gotoxy(22, 4); printf("0%d", alum+1); // Para los primeros 10 alumnos
		} else
		{
			gotoxy(22, 4); printf("%d", alum+1); // Para los 40 alumnos restantes
		}
		gotoxy(35, 4); printf("Grupo: "); gotoxy(42, 4); putchar(grupo[indexGrupo]); // Imprimir el grupo del alumno seleccionado
		gotoxy(1, 6); printf("Introduzca La Calificación Nueva: "); // Solicitar la nota mas actualizada
		// Se realiza la siguiente condicion de acuerdo a si se desea corregir la califacion, o alguna otra opcion
		if (cont ==0) // Si se desea corregir la calificacion
		{
			// De acuerdo con la asginatura seleccionada, se procedera a almacenar la nueva nota en dicha asignatura
			switch (asig)
			{
				case 1: scanf("%f", &grupos[indexGrupo].numAlum[alum].esp); break; // Para Espanol
				case 2: scanf("%f", &grupos[indexGrupo].numAlum[alum].mate); break; // Para Matematicas
				case 3: scanf("%f", &grupos[indexGrupo].numAlum[alum].hist); break; // Para Historia
				case 4: scanf("%f", &grupos[indexGrupo].numAlum[alum].cienc); break; // Para Ciencias
				case 5: scanf("%f", &grupos[indexGrupo].numAlum[alum].artes); break; // Para Artes
				case 6: scanf("%f", &grupos[indexGrupo].numAlum[alum].tecno); break; // Para Tecnologia
				case 7: scanf("%f", &grupos[indexGrupo].numAlum[alum].fcye); break; // Para Formacion civica y etica
			}
		} else // Si se oprimen las flechas de movimiento del puntero, se imprimira la calificacion ingresada
		{
			switch (asig)
			{
				case 1: printf("%.1f", grupos[indexGrupo].numAlum[alum].esp); break; // Para Espanol
				case 2: printf("%.1f", grupos[indexGrupo].numAlum[alum].mate); break; // Para Matematicas
				case 3: printf("%.1f", grupos[indexGrupo].numAlum[alum].hist); break; // Para Historia
				case 4: printf("%.1f", grupos[indexGrupo].numAlum[alum].cienc); break; // Para Ciencias
				case 5: printf("%.1f", grupos[indexGrupo].numAlum[alum].artes); break; // Para Artes
				case 6: printf("%.1f", grupos[indexGrupo].numAlum[alum].tecno); break; // Para Tecnologia
				case 7: printf("%.1f", grupos[indexGrupo].numAlum[alum].fcye); break; // Para Formacion civica y etica
			}
		}
		cont = 1; // Para que la flecha se pueda mover sin que se vuelva a solicitar de nuevo la calificacion
		gotoxy(2, 7+selec); printf("==>"); // Lee la nueva posicion de la flecha
		// Imprime los corchetes que indican que la flecha (==>) esta apuntando
		if (selec ==1)
		{
			gotoxy(6, 7+selec); printf("["); gotoxy(7+strlen("Guardar Cambios"), 7+selec); printf("]");
		} else
		{
			gotoxy(6, 7+selec); printf("["); gotoxy(7+strlen("Editar Calificación"), 7+selec); printf("]");
		}
		// Imprimir las opciones a escoger
		gotoxy(7, 8); printf("Guardar Cambios");
		gotoxy(7, 9); printf("Editar Calificación");
		// Leer el comando especial, el cual fue pulsado
		do
		{
			gotoxy(0, 0); tecla = getch2();
		} while (tecla !=ARRIBA && tecla !=ABAJO && tecla !=ENTER);
		// Definir el valor de selec para mover a la flecha
		switch (tecla)
		{
			case ARRIBA:
				selec--; // Disminucion porque se va hacia arriba
				if (selec <1) // Si ya no hay mas opciones arriba
				{
					selec = 2; // Se va hacia abajo
				}
			break;
			case ABAJO:
				selec++; // Aumento porque se va hacia abajo
				if (selec >2) // Si ya no hay mas opciones abajo
				{
					selec = 1; // Se regresa hacia arriba
				}
			break;
			case ENTER:
				if (selec ==1) // Si el apuntador (==>) se encuentra en Guardar Cambios
				{
					def = 0; // Para cuando se desee salir
				} else
				{
					cont = 0; // Para cuando se desee modificar la calificacion
				}
			break;
		}
	} while (def !=0); // Mientras no se apriente a Guardar Cambios
	
	//Antes de salir de la funcion calcular el promedio del alumno de nuevo
	grupos[indexGrupo].numAlum[alum].prom = (grupos[indexGrupo].numAlum[alum].esp+grupos[indexGrupo].numAlum[alum].mate+grupos[indexGrupo].numAlum[alum].hist+grupos[indexGrupo].numAlum[alum].cienc+grupos[indexGrupo].numAlum[alum].artes+grupos[indexGrupo].numAlum[alum].tecno+grupos[indexGrupo].numAlum[alum].fcye)/7;

	//archivo al cual se accede
	FILE *archivo;
	
	//Direccion en la cual se busca los archivos
	char dirname[50] = "Grupo";
	
	//nombre del archivo de texto
	char nombreAlumno[20] = "/Nombre_Alumno";
	
	//Extension del archivo
	char* extension = ".txt";
	
	//String de la conversion del int
	char convertirInt[10];

	if(indexGrupo == 0){
		//Nombre de la carpeta
		char* nombreCarpeta = "/A";
	
		//Se crea la direccion de la carpeta
		strcat(dirname,nombreCarpeta);
		
		//Agrega el numero del alumno
		toString(convertirInt, alum+1);
				
		//Se le agrega al string
		strcat(nombreAlumno,convertirInt);
		
		//Se le agrega la extension
		strcat(nombreAlumno,extension);
				
		//Se tiene la dirrecion del txt del alumno 'contador'
		strcat(dirname,nombreAlumno);
	
		//Elimina el anterior archivo
		remove(dirname);
		
		//crea los ficheros
		archivo = fopen(dirname, "w");
								
		/* fopen() regresa NULL si la ultima operacion no se pudo completar */
		if(archivo == NULL)
		{
			/* Si no se puede crear, salir del programa */
			printf("No se pudo crear el archivo.\n");
			exit(EXIT_FAILURE);
		}
		
		//Modificar el archivo de texto que contiene estos datos
		fwrite (&grupos[indexGrupo].numAlum[alum], sizeof(asig), 20, archivo);
		
		//Checa si la funcion anterior funciono de manera correcta
		if(fwrite != 0){
		//printf("El contenido se escribio de manera correcta!\n");
		}else{ 
		printf("Error al escribir en el archivo!\n");
		}
		// Cierra archivo
		fclose (archivo);
	}
	
	if(indexGrupo == 1){
		
		//Nombre de la carpeta
		char* nombreCarpeta = "/B";
	
		//Se crea la direccion de la carpeta
		strcat(dirname,nombreCarpeta);
		
		//Agrega el numero del alumno
		toString(convertirInt, alum+1);
				
		//Se le agrega al string
		strcat(nombreAlumno,convertirInt);
		
		//Se le agrega la extension
		strcat(nombreAlumno,extension);
				
		//Se tiene la dirrecion del txt del alumno 'contador'
		strcat(dirname,nombreAlumno);
	
		//crea los ficheros
		archivo = fopen(dirname, "w");
								
		/* fopen() regresa NULL si la ultima operacion no se pudo completar */
		if(archivo == NULL)
		{
			/* Si no se puede crear, salir del programa */
			printf("No se pudo crear el archivo.\n");
			exit(EXIT_FAILURE);
		}
		
		//Modificar el archivo de texto que contiene estos datos
		fwrite (&grupos[indexGrupo].numAlum[alum], sizeof(asig), 20, archivo);
		
		//Checa si la funcion anterior funciono de manera correcta
		if(fwrite != 0){
		//printf("El contenido se escribio de manera correcta!\n");
		}else{ 
		printf("Error al escribir en el archivo!\n");
		}
		// Cierra archivo
		fclose (archivo);
	}
	
	if(indexGrupo == 2){
		
		//Nombre de la carpeta
		char* nombreCarpeta = "/C";
		
		//Se crea la direccion de la carpeta
		strcat(dirname,nombreCarpeta);
		
		//Agrega el numero del alumno
		toString(convertirInt, alum+1);
				
		//Se le agrega al string
		strcat(nombreAlumno,convertirInt);
		
		//Se le agrega la extension
		strcat(nombreAlumno,extension);
				
		//Se tiene la dirrecion del txt del alumno 'contador'
		strcat(dirname,nombreAlumno);
	
		//crea los ficheros
		archivo = fopen(dirname, "w");
								
		/* fopen() regresa NULL si la ultima operacion no se pudo completar */
		if(archivo == NULL)
		{
			/* Si no se puede crear, salir del programa */
			printf("No se pudo crear el archivo.\n");
			exit(EXIT_FAILURE);
		}
		
		//Modificar el archivo de texto que contiene estos datos
		fwrite (&grupos[indexGrupo].numAlum[alum], sizeof(asig), 20, archivo);
		
		//Checa si la funcion anterior funciono de manera correcta
		if(fwrite != 0){
		//printf("El contenido se escribio de manera correcta!\n");
		}else{ 
		printf("Error al escribir en el archivo!\n");
		}
		// Cierra archivo
		fclose (archivo);
	}
}

// Se imprime el ranking de los 3 mejores, de acuerdo con el grupo seleccionado
void verRanking(char grupo[], int gpo)
{
	int i, j; // Contadores
	int pos[3]; // Almacena las posiciones de los 3 mejores
	float mejor[3] = {0, 0, 0}; // Almacena a los 3 promedio mas alto de acuerdo al grupo solicitado
	// Determinar los 3 mejores alumnos de los 50 alumnos que son en total
	for (i = 0; i <3; i++) // Cambia de posicion del Ranking
	{
		for (j = 0; j <K; j++) // Cambia de alumno
		{
			if (grupos[gpo].numAlum[j].prom >mejor[i])
			{
				mejor[i] = grupos[gpo].numAlum[j].prom; // Se almacena a los mejores promedios
				pos[i] = j; // Se almacena la posicion de los mejores promedios
			}
		}
		grupos[gpo].numAlum[pos[i]].prom = 0; // Se iguala a 0 el promedio de los dos mejores para que no vuelvan a ser contabilizados en la segunda y tercera ronda
	}
	// Se le vuelven a reasignar sus promedios originales de los mejores 3
	for (i = 0; i <3; i++)
	{
		grupos[gpo].numAlum[pos[i]].prom = mejor[i];
	}
	// Impresion de la interfaz del Ranking
	int tecla, def = 1; // Controladores nuevos, para la interfaz
	// Se procede a imprimir la interfaz
	do
	{
		system("CLS"); // Limpiar la pantalla
		system("COLOR 0A"); //Color para la consola
		// Imprimir margenes laterales
		for (i = 0; i <=32; i++)
		{
			gotoxy(1+i, 0); printf("*"); // Margen lateral superior
			gotoxy(1+i, 2); printf("*"); // Margen lateral delineador
			gotoxy(1+i, 12); printf("*"); // Margen lateral inferior
		}
		// Imprimir margenes verticales
		for (i = 0; i <12; i++)
		{
			gotoxy(1, 1+i); printf("*"); // Margen vertical izquierdo
			gotoxy(33, 1+i); printf("*"); // Margen vertical derecho
		}
		gotoxy(3, 1); printf("VISUALIZAR RANKING"); // Imprimir el titulo del apartado escogido
		gotoxy(21, 1); printf(" - Grupo: "); gotoxy (31, 1); putchar(grupo[gpo]); // Imprimir el grupo seleccionado
		gotoxy(2, 4); printf("Top: 3 Mejores Promedios:");
		// Imprimir a los 3 mejores promedios, una vez ya determinados
		for (i = 0; i <3; i++)
		{
			gotoxy(5, 6+i); printf("%d. ", i+1); printf("%s", grupos[gpo].numAlum[pos[i]].nombre); // Imprime el nombre
			// Imprime el numero de alumno
			if (pos[i] <9)
			{
				gotoxy(21, 6+i); printf("0%d", pos[i]+1); // Para los primeros 10 alumnos de la lista
			} else
			{
				gotoxy(21, 6+i); printf("%d", pos[i]+1); // Para los 40 alumnos restantes de la lista
			}
			// Imprime los puntitos como un decorado representativo para la visualizacion del usuario
			for (j = 0; j <3; j++)
			{
				gotoxy(24+j, 6+i); printf(".");
			}
			gotoxy(28, 6+i); printf("%.1f", mejor[pos[i]]); // Imprime el promedio
		}
		gotoxy(23, 10); printf("Regresar"); // Imprimir la etiqueta Regresar
		gotoxy(18, 10); printf("==>"); // Imprime a la flecha (==>)
		// Imprime los corchetes que indican que la flecha (==>) esta apuntando
		gotoxy(22, 10); printf("["); gotoxy(31, 10); printf("]");
		// Leer el comando especial, el cual fue pulsado
		do
		{
			gotoxy(0, 0); tecla = getch2();
		} while (tecla !=ARRIBA && tecla !=ABAJO && tecla !=ENTER);
		if (tecla ==ENTER)
		{
			def = 0; // Para cuando se decida salir del Ranking
		}
	} while (def !=0); // Mientras no se haya seleccionado aun, ninguna opcion	
}

// Despliega las notas finales obtuvidas, por cada alumno, de un determinado grupo, y finalmente despliega su promedio final
void visCalificaciones(int grupo, int numAlum, char asig[][30])
{
	int i, j, x; // Contadores
	// Se imprimen puntitos (.) como decoracion
	// 1. For: Va cambiando la longitud de las asignaturas
	for (i = 0; i <7; i++)
	{
		// 2. For: Va imprimiendo los puntitos (.)
		for (j = 0; j <49-((strlen(asig[i])+14)); j++)
		{
			x = 9+strlen(asig[i]); // Mide la longitud de la asignatura y le suma 12
			gotoxy(x+j, 10+i); printf("."); // Se imprimen los puntitos
		}
	}
	// Imprime las calificaciones del alumno seleccionado, por asignatura
	gotoxy(45, 10); printf("%.1f", grupos[grupo].numAlum[numAlum].esp); // Para Espanol
	gotoxy(45, 11); printf("%.1f", grupos[grupo].numAlum[numAlum].mate); // Para Matematicas
	gotoxy(45, 12); printf("%.1f", grupos[grupo].numAlum[numAlum].hist); // Para Historia
	gotoxy(45, 13); printf("%.1f", grupos[grupo].numAlum[numAlum].cienc); // Para Ciencias
	gotoxy(45, 14); printf("%.1f", grupos[grupo].numAlum[numAlum].artes); // Para Artes
	gotoxy(45, 15); printf("%.1f", grupos[grupo].numAlum[numAlum].tecno); // Para Tecnologia
	gotoxy(45, 16); printf("%.1f", grupos[grupo].numAlum[numAlum].fcye); // Para Formacion Civica Y Etica
	gotoxy(x+j-9, 18); printf ("Promedio: "); printf("%.1f", grupos[grupo].numAlum[numAlum].prom); // Para Promedio
}

// Inicializar las calificaciones y promedios de todos los alumnos, por cada grupo, por defecto
void iniciarEstructura(int index)
{
	int j; // Contadores
	// Llena, por defecto, las calificaciones del alumno seleccionado, por asignatura
	
	for (j = 0; j <K; j++) // Va cambiando el numero de alumno
	{
		strcpy(grupos[index].numAlum[j].nombre, "Nombre_Alumno"); // Para Nombre
		grupos[index].numAlum[j].esp = 1; // Para Espanol
		grupos[index].numAlum[j].mate = 1; // Para Matematicas
		grupos[index].numAlum[j].hist = 1; // Para Historia
		grupos[index].numAlum[j].cienc = 1; // Para Ciencias
		grupos[index].numAlum[j].artes = 1; // Para Artes
		grupos[index].numAlum[j].tecno = 1; // Para Tecnologia
		grupos[index].numAlum[j].fcye = 1; // Para Formacion Civica Y Etica
		// Calcular el promedio
		grupos[index].numAlum[j].prom = (grupos[index].numAlum[j].esp+grupos[index].numAlum[j].mate+grupos[index].numAlum[j].hist+grupos[index].numAlum[j].cienc+grupos[index].numAlum[j].artes+grupos[index].numAlum[j].tecno+grupos[index].numAlum[j].fcye)/7;
	}
}

int existeArchivoAccesar(char *dirname)
{
	// Checa si existe el archivo
	if (access(dirname, F_OK) == -1)
		return 0;
	
	return 1;
}

//Convertir a string
void toString(char str[], int num)
{
	int i, rem, len = 0, n;
	
	n = num;
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	for (i = 0; i < len; i++)
	{
		rem = num % 10;
		num = num / 10;
		str[len - (i + 1)] = rem + '0';
	}
	str[len] = '\0';
}

//Funcion para crear las direccion en las cuales se van a guardar los ficheros 
//seguido de los ficheros en caso de no tener previamente las carpetas y ficheros
void crearFicherosDirecciones(char *dirname){
	int check;
	//Contador para el nombre de los ficheros
	int contador = 1;
	int fila;
	//archivo al cual se accede
	FILE *archivo;
	//Direccion
	char aux[50];
	//Direccion de la carpeta del grupo en la que se encuentra
	char auxCarpetaGrupo[50];
	//String de la conversion del int
	char convertirInt[10];
	
	//Nombre de la carpeta
	char* nombreCarpeta = "/A";
	//Extension del archivo
	char* extension = ".txt";
	
	//Verificar si existe la dirrecion 'Grupo'
	if (existeArchivoAccesar(dirname)){
	
		//printf("'%s' is a directory.\n", dirname);
		
		//Se crea la ruta de la carpeta 'Gruppo/A'
		strcpy(aux, dirname);
		strcat(aux,nombreCarpeta);
		
		//Se guarda la ruta de la carpeta 'Gruppo/A'
		strcpy(auxCarpetaGrupo, aux);
		
		//printf("Ruta del archivo: %s", aux);
		
			for (fila = 0; fila <K; fila++)
			{
				//Lectura de archivos para structura
				FILE *inf;
				
				//Guarda la ruta del grupo
				strcpy(aux, auxCarpetaGrupo);
				//nombre del archivo de texto
				char nombreAlumno[20] = "/Nombre_Alumno";
				
				//Agrega el numero del alumno
				toString(convertirInt, contador);
				
				//Se le agrega al string
				strcat(nombreAlumno,convertirInt);
				
				//Se le agrega la extension
				strcat(nombreAlumno,extension);
				
				//Se tiene la dirrecion del txt del alumno 'contador'
				strcat(aux,nombreAlumno);
				
				//Se checa si existe los archivos de alumnos
				if (existeArchivoAccesar(aux)){
					//Abre los archivos para leer
					inf = fopen (aux, "r");
					//No existe
					if (inf == NULL) {
						fprintf(stderr, "\nError to open the file\n");
						exit (1);
					}
					//Se leen todos los datos del archivo de texto y se almancena en el struct
					while(fread(&grupos[0].numAlum[fila], sizeof(asig), 1, inf)){
						//Impresion de lectura de todos los archivos
						//printf ("Nombre = %s esp = %.1f mate = %.1f hist = %.1f cien = %.1f artes = %.1f tecno = %.1f fcye = %.1f prom = %.1f \n", inp.nombre, inp.esp, inp.mate, inp.hist, inp.cienc, inp.artes, inp.tecno, inp.fcye, inp.prom);
					}
					//Se cierra archivo abierto
					fclose (inf);
					
					//printf("archivo %s se creo\n", nombreAlumno);
				}else{
					//Se creara estrucura si no existe la carpeta grupos
					iniciarEstructura(0);
					check = mkdir(auxCarpetaGrupo);
					
					//Checa si la carpeta 'Grupo/A' existe
					if (!check){
						//printf("Directorio '%s' creado\n", auxCarpetaGrupo);
						//Creacion de archivos de texto 
						for (fila = 0; fila <K; fila++)
						{
							//Crea la ruta de los ficheros a crear
							strcpy(aux, auxCarpetaGrupo);
							char nombreAlumno[20] = "/Nombre_Alumno";
							
							toString(convertirInt, contador);
							strcat(nombreAlumno,convertirInt);
							
							strcat(nombreAlumno,extension);
							
							strcat(aux,nombreAlumno);
							
							//Checa si existen
							if (archivo = fopen(aux, "r")) {
								fclose(archivo);
								//printf("Archivo existe %s \n", nombreAlumno);
							} else {
								
								//crea los ficheros
								archivo = fopen(aux, "w");
								
								/* fopen() regresa NULL si la ultima operacion no se pudo completar */
								if(archivo == NULL)
								{
									/* Si no se puede crear, salir del programa */
									printf("No se pudo crear el archivo.\n");
									exit(EXIT_FAILURE);
								}
								
								//Lee el los datos del struct y lo pone dentro del archivo
								fwrite (&grupos[0].numAlum[fila], sizeof(asig), 1, archivo);
								
								//Checa si la funcion anterior funciono de manera correcta
								if(fwrite != 0){
									//printf("El contenido se escribio de manera correcta!\n");
								}else{ 
									printf("Error al escribir en el archivo!\n");
								}
								// Cierra archivo
								fclose (archivo);
							}
							//Contador para el nombre de los ficheros
							contador++;
						}
					}else {
					//	printf("No se puede crear el directorio '%s'\n", auxCarpetaGrupo);
					}
				}
				contador++;
			}
		contador = 1;
		
		strcpy(aux, dirname);
		nombreCarpeta = "/B";
		
		//Direccion de la carpeta'Grupo/B'
		strcat(aux,nombreCarpeta);
		strcpy(auxCarpetaGrupo, aux);
		
		
		for (fila = 0; fila <K; fila++)
		{
			//Lectura de archivos para structura
			FILE *inf;
			
			//Guarda la ruta del grupo
			strcpy(aux, auxCarpetaGrupo);
			//nombre del archivo de texto
			char nombreAlumno[20] = "/Nombre_Alumno";
			
			//Agrega el numero del alumno
			toString(convertirInt, contador);
			
			//Se le agrega al string
			strcat(nombreAlumno,convertirInt);
			
			//Se le agrega la extension
			strcat(nombreAlumno,extension);
			
			//Se tiene la dirrecion del txt del alumno 'contador'
			strcat(aux,nombreAlumno);
			
			//Checa si existen los ficheros
			if (existeArchivoAccesar(aux)){
				
				//Lee el fichero optenido
				inf = fopen (aux, "r");
				if (inf == NULL) {
					fprintf(stderr, "\nError to open the file\n");
					exit (1);
				}
				//Se llena todos los datos del struct
				while(fread(&grupos[1].numAlum[fila], sizeof(asig), 1, inf)){
					//Impresion de lectura
					//printf ("Nombre = %s esp = %.1f mate = %.1f hist = %.1f cien = %.1f artes = %.1f tecno = %.1f fcye = %.1f prom = %.1f \n", inp.nombre, inp.esp, inp.mate, inp.hist, inp.cienc, inp.artes, inp.tecno, inp.fcye, inp.prom);
				}
				//Se cierra el fichero
				fclose (inf);
				
				//printf("archivo %s se creo\n", nombreAlumno);
			}else{
				//Temporal para pruebas, cuando acabe solo se creara estrucura si no existe la carpeta grupos
				iniciarEstructura(1);
				check = mkdir(auxCarpetaGrupo);
				
				//Checa sino existe la ruta 'Grupo/B'
				if (!check){
					//printf("Directorio '%s' creado\n", auxCarpetaGrupo);
					//Creacion de archivos de texto 
					for (fila = 0; fila <K; fila++)
					{
						//Direccion de los ficheros
						strcpy(aux, auxCarpetaGrupo);
						char nombreAlumno[20] = "/Nombre_Alumno";
						
						toString(convertirInt, contador);
						strcat(nombreAlumno,convertirInt);
						
						strcat(nombreAlumno,extension);
						
						strcat(aux,nombreAlumno);
						
						//Verifica que no existe
						if (archivo = fopen(aux, "r")) {
							fclose(archivo);
							//printf("Archivo existe %s \n", nombreAlumno);
						} else {
							//Crea el fichero con los datos del struct
							archivo = fopen(aux, "w");
							
							/* fopen() regresa NULL si la ultima operacion no se pudo completar */
							if(archivo == NULL)
							{
								/* Si no se puede crear, salir del programa */
								printf("No se pudo crear el archivo.\n");
								exit(EXIT_FAILURE);
							}
							
							//Lee el los datos del struct y lo pone dentro del archivo
							fwrite (&grupos[1].numAlum[fila], sizeof(asig), 1, archivo);
							
							//Checa si la funcion anterior funciono de manera correcta
							if(fwrite != 0){
								//printf("El contenido se escribio de manera correcta!\n");
							}else{ 
								//printf("Error al escribir en el archivo!\n");
							}
							// Cierra archivo
							fclose (archivo);
						}
						contador++;
					}
					contador = 1;
				}else {
					//printf("No se puede crear el directorio '%s'\n", aux);
				}
			}
			contador++;
		}
		
		contador = 1;
		strcpy(aux, dirname);
		nombreCarpeta = "/C";
		
		//Direccion de 'Grupo/C'
		strcat(aux,nombreCarpeta);
		strcpy(auxCarpetaGrupo, aux);
		
		
		for (fila = 0; fila <K; fila++)
		{
			//Lectura de archivos para structura
			FILE *inf;
			
			//Guarda la ruta del grupo
			strcpy(aux, auxCarpetaGrupo);
			//nombre del archivo de texto
			char nombreAlumno[20] = "/Nombre_Alumno";
			
			//Agrega el numero del alumno
			toString(convertirInt, contador);
			
			//Se le agrega al string
			strcat(nombreAlumno,convertirInt);
			
			//Se le agrega la extension
			strcat(nombreAlumno,extension);
			
			//Se tiene la dirrecion del txt del alumno 'contador'
			strcat(aux,nombreAlumno);
			
			//Verifica si existe direccion
			if (existeArchivoAccesar(aux)){
				//Abre el finchero para ver si existe
				inf = fopen (aux, "r");
				if (inf == NULL) {
					fprintf(stderr, "\nError to open the file\n");
					exit (1);
				}
				//Lee los datos y los pone en el struct
				while(fread(&grupos[2].numAlum[fila], sizeof(asig), 1, inf)){
					//Impresion de lectura
					//printf ("Nombre = %s esp = %.1f mate = %.1f hist = %.1f cien = %.1f artes = %.1f tecno = %.1f fcye = %.1f prom = %.1f \n", inp.nombre, inp.esp, inp.mate, inp.hist, inp.cienc, inp.artes, inp.tecno, inp.fcye, inp.prom);
				}
				fclose (inf);
				
				//printf("archivo %s se creo\n", nombreAlumno);
			}else{
				//Se creara estrucura si no existe la carpeta grupos
				iniciarEstructura(2);
				check = mkdir(auxCarpetaGrupo);
				
				//Verifica si existe la carpeta 'Grupo/C'
				if (!check){
					//printf("Directorio '%s' creado\n", auxCarpetaGrupo);
					//Creacion de archivos de texto 
					for (fila = 0; fila <K; fila++)
					{
						strcpy(aux, auxCarpetaGrupo);
						char nombreAlumno[20] = "/Nombre_Alumno";
						
						toString(convertirInt, contador);
						strcat(nombreAlumno,convertirInt);
						
						strcat(nombreAlumno,extension);
						
						strcat(aux,nombreAlumno);
						
						//Verifica que no exista
						if (archivo = fopen(aux, "r")) {
							fclose(archivo);
							//printf("Archivo existe %s \n", nombreAlumno);
						} else {
							//Crea el fichero
							archivo = fopen(aux, "w");
							
							/* fopen() regresa NULL si la ultima operacion no se pudo completar */
							if(archivo == NULL)
							{
								/* Si no se puede crear, salir del programa */
								printf("No se pudo crear el archivo.\n");
								exit(EXIT_FAILURE);
							}
							
							//Lee el los datos del struct y lo pone dentro del archivo
							fwrite (&grupos[2].numAlum[fila], sizeof(asig), 1, archivo);
							
							//Checa si la funcion anterior funciono de manera correcta
							if(fwrite != 0){
								//printf("El contenido se escribio de manera correcta!\n");
							}else{ 
								printf("Error al escribir en el archivo!\n");
							}
							// Cierra archivo
							fclose (archivo);
						}
						contador++;
					}
					contador = 1;
				}else {
					//printf("No se puede crear el directorio '%s'\n", aux);
				}
			}
			contador++;
		}
		//Crear la direccion Grupo y las carpetas A,B,C
	}else{
		check = mkdir(dirname);
		
		//Se crea Grupo
		if (!check){
			//printf("Directorio '%s' creado\n", dirname);
			
			//Direccion de 'Grupo/A'
			strcpy(aux, dirname);
			strcat(aux,nombreCarpeta);
			
			strcpy(auxCarpetaGrupo, aux);
			
			//Se crea Grupo/A
			check = mkdir(auxCarpetaGrupo);
			//Se creara estrucura si no existe la carpeta grupos
			iniciarEstructura(0);
			if (!check){
				//printf("Directorio '%s' creado\n", auxCarpetaGrupo);
				
				//Creacion de archivos de texto 
				for (fila = 0; fila <K; fila++)
				{
					//Direccion de los ficheros
					strcpy(aux, auxCarpetaGrupo);
					char nombreAlumno[20] = "/Nombre_Alumno";
					
					toString(convertirInt, contador);
					strcat(nombreAlumno,convertirInt);
					
					strcat(nombreAlumno,extension);
					
					strcat(aux,nombreAlumno);
					
					//Verifica que no existen
					if (archivo = fopen(aux, "r")) {
						fclose(archivo);
						//printf("Archivo existe %s \n", nombreAlumno);
					} else {
						//Crea los fichetos
						archivo = fopen(aux, "w");
						
						/* fopen() regresa NULL si la ultima operacion no se pudo completar */
						if(archivo == NULL)
						{
							/* Si no se puede crear, salir del programa */
							printf("No se pudo crear el archivo.\n");
							exit(EXIT_FAILURE);
						}
						
						//Lee el los datos del struct y lo pone dentro del archivo
						fwrite (&grupos[0].numAlum[fila], sizeof(asig), 1, archivo);
						
						//Checa si la funcion anterior funciono de manera correcta
						if(fwrite != 0){
							//printf("El contenido se escribio de manera correcta!\n");
						}else{ 
							printf("Error al escribir en el archivo!\n");
						}
						// Cierra archivo
						fclose (archivo);
					}
					contador++;
				}
				contador = 1;
			}else {
				//printf("No se puede crear el directorio '%s'\n", auxCarpetaGrupo);
			}
			
			strcpy(aux, dirname);
			nombreCarpeta = "/B";
			
			//Direccion de 'Grupo/B'
			strcat(aux,nombreCarpeta);
			
			strcpy(auxCarpetaGrupo, aux);
			//Se crea Grupo/B
			check = mkdir(auxCarpetaGrupo);
			//Se creara estrucura si no existe la carpeta grupos
			iniciarEstructura(1);
			if (!check){
				//printf("Directorio '%s' creado\n", auxCarpetaGrupo);
				
					//Creacion de archivos de texto 
					for (fila = 0; fila <K; fila++)
					{
						//Direccion del fichero
						strcpy(aux, auxCarpetaGrupo);
						char nombreAlumno[20] = "/Nombre_Alumno";
							
						toString(convertirInt, contador);
						strcat(nombreAlumno,convertirInt);
							
						strcat(nombreAlumno,extension);
							
						strcat(aux,nombreAlumno);
						
						//Verifica si existe fichero	
						if (archivo = fopen(aux, "r")) {
							fclose(archivo);
							//printf("Archivo existe %s \n", nombreAlumno);
						} else {
							//Crea el fichero
							archivo = fopen(aux, "w");
								
							/* fopen() regresa NULL si la ultima operacion no se pudo completar */
							if(archivo == NULL)
							{
								/* Si no se puede crear, salir del programa */
								printf("No se pudo crear el archivo.\n");
								exit(EXIT_FAILURE);
							}
								
							//Lee el los datos del struct y lo pone dentro del archivo
							fwrite (&grupos[1].numAlum[fila], sizeof(asig), 1, archivo);
								
							//Checa si la funcion anterior funciono de manera correcta
							if(fwrite != 0){
								//printf("El contenido se escribio de manera correcta!\n");
							}else{ 
								printf("Error al escribir en el archivo!\n");
							}
							// Cierra archivo
							fclose (archivo);
						}
						contador++;
					}
					contador = 1;
				}else {
				//printf("No se puede crear el directorio '%s'\n", auxCarpetaGrupo);
				}
			
			
			strcpy(aux, dirname);
			nombreCarpeta = "/C";
			
			//Direccion de 'grupo/C'
			strcat(aux,nombreCarpeta);
			
			strcpy(auxCarpetaGrupo, aux);
			
			//Se crea Grupo/C
			check = mkdir(auxCarpetaGrupo);
			//Se creara estrucura si no existe la carpeta grupos
			iniciarEstructura(2);
			if (!check){
				//printf("Directorio '%s' creado\n", auxCarpetaGrupo);
				
				//Creacion de archivos de texto 
				for (fila = 0; fila <K; fila++)
				{
					//Direccion del fichero
					strcpy(aux, auxCarpetaGrupo);
					char nombreAlumno[20] = "/Nombre_Alumno";
					
					toString(convertirInt, contador);
					strcat(nombreAlumno,convertirInt);
					
					strcat(nombreAlumno,extension);
					
					strcat(aux,nombreAlumno);
					
					//Verifica que no exista
					if (archivo = fopen(aux, "r")) {
						fclose(archivo);
						//printf("Archivo existe %s \n", nombreAlumno);
					} else {
						//Crea el fichero
						archivo = fopen(aux, "w");
						
						/* fopen() regresa NULL si la ultima operacion no se pudo completar */
						if(archivo == NULL)
						{
							/* Si no se puede crear, salir del programa */
							printf("No se pudo crear el archivo.\n");
							exit(EXIT_FAILURE);
						}
						
						//Lee el los datos del struct y lo pone dentro del archivo
						fwrite (&grupos[2].numAlum[fila], sizeof(asig), 1, archivo);
						
						//Checa si la funcion anterior funciono de manera correcta
						if(fwrite != 0){
							//printf("El contenido se escribio de manera correcta!\n");
						}else{ 
							printf("Error al escribir en el archivo!\n");
						}
						// Cierra archivo
						fclose (archivo);
					}
					contador++;
				}
				contador = 1;
			}else {
				//printf("No se puede crear el directorio '%s'\n", auxCarpetaGrupo);
			}
			
		}else {
			//printf("No se puede crear el directorio '%s'\n", dirname);
		}
	}
}

