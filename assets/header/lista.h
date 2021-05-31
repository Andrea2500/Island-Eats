typedef struct i {
    int codice;
    int pesoMax;
    struct i *next;
} Isola;

Isola *creaIsola(int isola, int pesoMax);
Isola *inserisciIsolaInCoda(Isola *lista, Isola *isola);
void liberaLista(Isola *lista);