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

for (int fila = 0; fila < 9; fila++) {
    int usados[10] = {0}; // lista con los numeros posibles
    for (int col = 0; col < 9; col++) {
        int valor = n->sudo[fila][col];
        if (valor == 0) continue; // 0 = vacio = ignorar
        if (usados[valor]) return 0; // si ya el valor ya existe en la lista returna 0
        usados[valor] = 1; // el numero de esa posicion existe ahora
    }
}

for (int col = 0; col < 9; col++) {
    int usados[10] = {0}; //lista con los nuneros posibles
    for (int fila = 0; fila < 9; fila++) {
        int valor = n->sudo[fila][col];
        if (valor == 0) continue; // 0 = vacio = ignorar
        if (usados[valor]) return 0; //si el valor ya existe en la lista returna 0
        usados[valor] = 1; // el numero de esa posicion ya existe
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
    pushBack(list, newNode);
  }

  return list;
}


int is_final(Node* n){
    return 0;
}

Node* DFS(Node* initial, int* cont){
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