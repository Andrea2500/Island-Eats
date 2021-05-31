#include "../header/header.h"


Isola *creaIsola(int isola, int pesoMax) {
    Isola *tmp;
    tmp = (Isola *)malloc(sizeof(Isola));
    if(tmp) {
        tmp->codice = isola;
        tmp->pesoMax = pesoMax;
        tmp->next = NULL;
    }
    return tmp;
}


Isola *inserisciIsolaInCoda(Isola *lista, Isola *isola) {
  if(lista) {
    lista->next = inserisciIsolaInCoda(lista->next, isola);
  } else {
    lista = isola;
  }
  return lista;
}


void liberaLista(Isola *lista) {
    if(lista) {
        liberaLista(lista->next);
        free(lista);
    }
}
