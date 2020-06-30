/**
 * La idea principal es utilizar una lista para guadar el historial de los archivos.
 * el archivo reciente se va a encontrar almacenado en la posición 0 de la lista
 * el archivo anterior se va a encontrar almacenado en la posición 1 de la lista
 * cuando se quiere ver el archivo anterior, el valor de reciente se hace 1 (anterior) y se abre el archivo (anterior)
 *  
 * si actual == 0 -> no existe siguiente y anterior = 1
 * si actual == 1 -> siguiente = 0 y anterior = 2
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/List.h"
#include "../includes/Type.h"

#define PATH "../files/hola.txt"

void openFile(const char* path);

int menuNoFile();

int menuSeveralFiles();

int main()
{
	List History = NULL;
	History = list_create();

	unsigned int actual = 0;
	int choice = 1;
	boolean firsTime = True;
	char firstFile[256];
	char fileName[256];

	while(choice != 2){
		unsigned int Hsize = list_size(History);
		if(Hsize == 0){
			choice = menuNoFile();
		}else{
			if(Hsize > 0){
				choice = menuSeveralFiles();
			}
		}
		if(choice == 1){

			setbuf(stdin, 0);
			printf("Archivo: ");
			gets(fileName);
			printf("\n");
			openFile(fileName);

			if(!firsTime){
				if(!strcmp(fileName, (char*)list_get(History, actual))){	//¿El archivo que se quiere abrir es el reciente?
					openFile((char*)list_get(History, actual));		//abrir el documento que se encuentra en actual
				}else{	//Cuando ya se ha abierto algún archivo
					if(actual == 0){		//solo hay dos archivos en el histórico
						list_insert(History, String(fileName), 0);
					}else{		//hay tres archivos en el histórico
						list_set(History, String(fileName), 0);
						actual = 0;
					}
				}
			}else{		//cuando el archivo se abre por primera vez
				list_insert(History, String(fileName), 0);
				strcpy(firstFile, fileName);
				firsTime = False;
			}
		}else{
			if(choice == 3){	//abrir reciente
				openFile((char*)list_get(History, actual));		//abrir el documento que se encuentra en actual
			}else{
				if(choice == 4){		//abrir anterior
					if(Hsize == 1){
						printf("\033[1;31m");
						printf("No existe el archivo anterior.\n");
						printf("\033[0m");
					}else{
						if(actual == 0){
							actual++;			//mover reciente al anterior
							openFile((char*)list_get(History, actual));		//imprimir anterior (reciente)
						}else{
							if(Hsize < 3){	//¿Hay menos de 3 elementos en el histórico?
								printf("\033[1;31m");
								printf("No existe el archivo anterior.\n");
								printf("\033[0m");
							}else{		//Hay 3 o más elementos en el histórico
								if(actual == Hsize-1){
									printf("\033[1;31m");
									printf("No existe el archivo anterior.\n");
									printf("\033[0m");
								}else{
									actual++;
									openFile((char*)list_get(History, actual));		//imprimir anterior (reciente)
								}
							}
						}
					}
				}else{
					if(choice == 5){
						if(actual == 0){
							printf("\033[1;31m");
							printf("No existe el archivo siguiente.\n");
							printf("\033[0m");
						}else{
							openFile((char*)list_get(History, actual-1));
							actual--;		//hacer el archivo "siguiente" que se acaba de abrir como reciente
						}
					}else{
						if(choice == 6){		//abrir el primer archivo que se abrió
							openFile(firstFile);
						}else{
							if(choice == 7){	//abrir el archivo reciente
								openFile((char*)list_get(History, actual));
							}
						}
					}
				}
			}
		}
	}

	return 0;
}

void openFile(const char* path){
	FILE *f  = fopen(path, "rt");
	if(f){
		setbuf(stdin, 0);
		printf("\033[1;34m");
		printf("Archivo: %s\n", path); 
		printf("\033[0m");
		printf("\n");
		while(!feof(f)){
			char line[127];
			fgets(line, 127, f);
			printf("\033[01;33m");
			printf("%s\n", line); 
		}
		printf("\033[0m");
		printf("\n");
		fclose(f);
	}else{
		printf("\033[1;31m");
		printf("No existe el archivo: %s\n", path);
		printf("\033[0m");
	}
}

int menuNoFile(){
	int choice;
	printf("\n");
	printf("1. Abrir archivo.\n");
	printf("2. Salir.\n");
	printf("Seleccione opción: ");
	scanf("%d", &choice);
	printf("\n");
	return choice;
}

int menuSeveralFiles(){
	int choice;
	printf("\n");
	printf("1. Abrir archivo.\n");
	printf("2. Salir.\n");
	printf("3. Mostrar reciente.\n");
	printf("4. Mostrar anterior.\n");
	printf("5. Mostrar siguiente.\n");
	printf("6. Mostrar primero.\n");
	printf("7. Mostrar último.\n");
	printf("Seleccione opción: ");
	scanf("%d", &choice);
	printf("\n");
	return choice;
}
