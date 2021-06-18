//********************************************************************************************************************************************************************************************************
//Nombre			: Propuesta de Proyecto
//Autor				: AKE GAMBOA ALEJANDRO
//Fecha				: 18/06/2021
//Version			: 3.0
//Descripcion		: Interfaz de usuario 01
//********************************************************************************************************************************************************************************************************

#include <stdio.h>
#include <stdlib.h> // exit
#include <locale.h> // setlocale
#include <string.h> // strlen, strcmp, strcpy
#include <windows.h> // system, gotoxy, getch2

// Macros
#define ARRIBA 'w'
#define ABAJO 's'
#define ENTER 13

// Prototipos
void menuPrincipal(void); // 1
int solUsuario(void); // 2
void opcEsc(int opc, char usuario[], char defUsuario[], char contra[], char defContra[], int *cont1); // 3
void opc1(char usuario[]); // 3.1
void opc2(char nomContra[]); // 3.2
void opc3(char nomUsuario[], char defUsuario[]); // 3.3
void opc4(char nomContra[], char defContra[]); // 3.4
int opc5(char usuario[], char defUsuario[], char contra[], char defContra[]); // 3.5
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
	int opc1; // Determina la opcion seleccionada
	int cont1 = 1; // Verdadero hasta tener usuario y contrasenia establecidos
	int cont2 = 1; // Verdadero hasta cerrar la sesion
	char usuario[9] = {'U', 's', 'u', 'a', 'r', 'i', 'o', '1'}; // Por defecto
	char contra[9] = {'U', 's', 'u', 'a', 'r', 'i', 'o', '1'}; // Por defecto
	char nomUsuario[100]; // Almacenara el nuevo nombre del usuario
	char nomContra[100]; // Almacenara la nueva contrasenia del usuario
	//Estructura que se repite hasta que ya se haya iniciado sesion
	do
	{
		opc1 = solUsuario(); // Se almacena la opcion seleccionada
		opcEsc(opc1, nomUsuario, usuario, nomContra, contra, &cont1); // Se evalua que opcion se escogio
	} while (cont1 !=0); // Mientras que no se haya iniciado sesion
	// Se procede a desplegar las opciones disponibles, una vez se haya ingresado al programa con exito
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

// De acuerdo con lo solicitado, se procede a presentarlo
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
		for (i = 0; i <=strlen("AÑADIR USUARIO")+3; i++)
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
				// Imprimir las opciones a escoger
				gotoxy(7, 6); printf("Reintentar");
				gotoxy(7, 7); printf("Volver Al Menú Principal");
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
void solAccion(void)
{
	
}
