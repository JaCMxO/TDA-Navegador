#ifndef __LIST_H__
#define __LIST_H__

#include "Type.h"

typedef enum{False, True, Error} boolean;
typedef struct strList *List;

//Crear un ejemplar List con memoria dinámica y asigna NULL, NULL y 0 a sus elementos
List list_create();

//Verificar si la lista está vacía
boolean list_isEmpty(List l);

//Extrae el tamaño de la lista
unsigned int list_size(List l);

//Agrega un elemento al final de la lista e incrementa el tamaño en uno
void list_add(List l, Type value);

//Devuelve el elemento en la posición p
Type list_get(List l, unsigned int index);

//Reemplaza el elemento en la posición p por el valor recibido
boolean list_set(List l, Type value, unsigned int index);

//Elimina y devuelve el elemento de la posición p y decrementa el tamaño en uno
Type list_remove(List l, unsigned int index);

//Inserta un nuevo elemento en la posición index e incrementa el tamaño en uno
void list_insert(List l, Type value, unsigned int index);

//Elimina todos los elemetos de la lista y a la lista
void list_destroy(List l);

#endif	/* __LIST_H__ */