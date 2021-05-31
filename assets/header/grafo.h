static Isola *grafo[10];

void creaGrafo();
void creaArco(Isola **grafo, int sorgente, int destinazione, int pesoMax);
void stampaGrafo(Isola **grafo);
void stampaAdiacenti(Isola *nodo);
void liberaGrafo(Isola **grafo);
void cercaPercorso(char *username, int partenza, int destinazione, int pesoTot, int flag);
void bfsPesata(int partenza, int destinazione, int *pred, int *dist, int pesoTot);
void visitaAdiacenti(Isola *grafo, Isola *isola, int *pred, int *dist, int pesoTot);
void stampaPercorso(int partenza, int destinazione, int *pred);