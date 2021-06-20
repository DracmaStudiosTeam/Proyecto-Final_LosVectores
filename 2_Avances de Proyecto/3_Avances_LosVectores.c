//********************************************************************************************************************************************************************************************************
//Nombre			: Avances_LosVectores
//Autor				: Los Vectores: Ake Gamboa Alejandro; Euan Briceno Rodrigo Daniel; Nahuat Chi Jose Martin; Ortiz Palacios Andres Enrique
//Fecha				: 10/06/2021
//Version			: 1.0
//Descripcion		: Programa de analisis de promedios escolares en ANSI C
//********************************************************************************************************************************************************************************************************

#include <stdio.h>
#include <ctype.h> // toupper
#include <stdlib.h> // exit
#include <locale.h> // setlocale
#include <string.h> // strlen, strcmp, strcpy
#include <windows.h> // system, gotoxy, getch2

// Macros
#define ARRIBA 'w' // Presionar w para ir hacia arriba
#define ABAJO 's' // Presionar s para ir hacia abajo
#define ENTER 13
#define N 100 // Numero de caracteres que puede contener la variable nombre[N]
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
void selAlumno(int opc, int opc2, char opcSel[][100], char grp[]); // 5.1
void opc2_0(char opcSel[][100], int opc);
int gotoxy(USHORT x, USHORT y); // API de Windows
char getch2(void); // API de Windows

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
					switch (selec)
					{
						case 1: selAlumno(0, opc, opcSel, grupos); break; // Si se selecciona el grupo A
						case 2: selAlumno(1, opc, opcSel, grupos); break; // Si se selecciona el grupo B
						case 3: selAlumno(2, opc, opcSel, grupos); break; // Si se selecciona el grupo C
						case 4: def = 0; break; // Para la opcion Regresar
					}
				} else
				{
					switch(selec)
					{
						case 4: def = 0;
					}
				}
				
			break;
		}
	} while (def !=0); // Mientras no se haya seleccionado aun, ninguna opcion
}

// Opcion que despliega la lista del grupo seleccionado. Funge para los 3 grupos existentes
void selAlumno(int opc, int opc2, char opcSel[][100], char grp[])
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
		gotoxy(30, 3); printf("*"); gotoxy(32, 3); printf("Grupo: "); gotoxy (39, 3); putchar(grp[opc]); // Imprimir el grupo seleccionado
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
			strcpy(grupos[opc].numAlum[i].nombre, "Nombre_Alumno"); // Imprimir el nombre de los alumno del grupo seleccionado
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
				switch (selec)
				{
					
					case 51: def = 0; break; // Para la opcion Regresar
				}
			break;
		}
	} while (def !=0); // Mientras no se haya seleccionado aun, ninguna opcion
}
