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
			list_insert(History, String(fileName), 0);
		}else{
			if(choice == 3){
				openFile(fileName);
			}else{
				if(choice == 4){
					if(Hsize == 1){
						printf("No existe el archivo anterior.\n");
					}else{
						actual++;
						openFile((char*)list_get(History, actual));
						list_insert(History, String((char*)list_get(History, actual)), 1);		//FIXME: revisar en caso de error lógico
					}
				}else{
					if(choice == 5){
						if(actual == 0){
							printf("No existe el archivo siguiente.\n");
						}else{
							openFile((char*)list_get(History, 0));
							actual--;
						}
					}else{
						if(choice == 6){
							openFile((char*)list_get(History, 0));
						}else{
							if(choice == 7){
								openFile((char*)list_get(History, Hsize-1));
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
}

int menuNoFile(){
	int choice;
	printf("1. Abrir archivo.\n");
	printf("2. Salir.\n");
	printf("Seleccione opción: ");
	scanf("%d", &choice);
	printf("\n");
	return choice;
}

int menuSeveralFiles(){
	int choice;
	printf("1. Abrir archivo.\n");
	printf("2. Salir.\n");
	printf("3. Mostrar reciente.\n");
	printf("4. Mostrar Anterior.\n");
	printf("5. Mostrar Siguiente.\n");
	printf("6. Mostrar primero.\n");
	printf("7. Mostrar último.\n");
	printf("Seleccione opción: ");
	scanf("%d", &choice);
	printf("\n");
	return choice;
}