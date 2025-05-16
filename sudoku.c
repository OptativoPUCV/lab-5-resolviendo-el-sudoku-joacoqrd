#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
  /*
  1- No debe repetirse un numero en una columna
  2- No debe repetirse un numero en una fila
  3- No debe repetirse un numero en una sub matriz
  */
//verificar jas filas
for (int fila = 0; fila < 9; fila++) {
    int usados[10] = {0}; // lista con los numeros posibles
    for (int col = 0; col < 9; col++) {
        int valor = n->sudo[fila][col];
        if (valor == 0) continue; // 0 = vacio = ignorar
        if (usados[valor]) return 0; // si ya el valor ya existe en la lista returna 0
        usados[valor] = 1; // el numero de esa posicion existe ahora
    }
}
//verificar columnas
for (int col = 0; col < 9; col++) {
    int usados[10] = {0}; //lista con los nuneros posibles
    for (int fila = 0; fila < 9; fila++) {
        int valor = n->sudo[fila][col];
        if (valor == 0) continue; // 0 = vacio = ignorar
        if (usados[valor]) return 0; //si el valor ya existe en la lista returna 0
        usados[valor] = 1; // el numero de esa posicion ya existe
    }
}
//verificacion submatriz
for (int iniFila = 0; iniFila < 9; iniFila += 3) { //recorro las filas de 3 en 3 porque una submatriz es de 3 cosos
    for (int iniCol = 0; iniCol < 9; iniCol += 3) { // recorro las columnas de 3 en 3 porque una submatriz es de 3 cosos 
        int usados[10] = {0}; //lista con los numeros posibles
        //recorrer la submatriz
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                int valor = n->sudo[iniFila + i][iniCol + j]; //valor en las matriz completa pero en la submatriz
                if (valor == 0) continue;
                if (usados[valor]) return 0;
                usados[valor] = 1;
            }
        }
    }
}
return 1;
}


List* get_adj_nodes(Node* n){
  List* list=createList();
  if (n == NULL) return list;

  int fila = -1, col = -1;
  for (int i = 0; i < 9 && fila == -1; i++) { //recorrer matriz
    for (int j = 0; j < 9; j++) {
      if (n->sudo[i][j] == 0) { //si encuentra casilla valida
        fila = i;
        col = j;
        break;
      }
    }
  }
  if (fila == -1) return list;

  for (int k = 1; k <= 9; k++){
    Node* newNode = copy(n);
    newNode->sudo[fila][col] = k;
        if (is_valid(newNode)) { //si cumple las condiciones, agrega
            pushBack(list, newNode);
        } else {
            free(newNode); 
        }
    }

  return list;
}


int is_final(Node* n){
  for (int fila = 0 ; fila < 9 ; fila++){
    for (int col = 0 ; col < 9 ; col++){
      if (n->sudo[fila][col] == 0) return 0;
    }
  }
    return 1;
}

Node* DFS(Node* initial, int* cont){
  Stack* S = createStack(); //creo la pila como en el ejemplo
  push(S, initial); //meto  el nodo como en el ejemplo
  cont = 0; //creo el contador pedido

  while (size(S) != 0){ //mientras que hayan elementos en la fila
    Node* n = top(initial);
    pop(S); //eliminamos el actual
    cont++; //aumentamos el contador
    if (is_final(n)) return n; // si da una solucion al sudoku, ta bien y termina

    List* adjNodes = get_adj_nodes(n); //creo una lista con las opciones validas
    Node* aux = first(adjNodes); 

    while (aux != NULL){
      push (S, aux); //agrego una nueva posible solucion a la pila
      aux = next(adjNodes);
    }
    free (n);
  }
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/