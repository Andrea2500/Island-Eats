#include "../header/header.h"


void creaGrafo() {
    for(int i = 0; i < 10; i++) {
        grafo[i] = malloc(sizeof(Isola));
        grafo[i]->codice = i;
    }
    creaArco(grafo, 0, 1, 38);
    creaArco(grafo, 1, 2, 21);
    creaArco(grafo, 2, 3, 38);
    creaArco(grafo, 3, 4, 28);
    creaArco(grafo, 4, 5, 35);
    creaArco(grafo, 5, 6, 34);
    creaArco(grafo, 6, 7, 40);
    creaArco(grafo, 7, 0, 24);
    creaArco(grafo, 6, 8, 17);
    creaArco(grafo, 7, 8, 10);
    creaArco(grafo, 0, 8, 30);
    creaArco(grafo, 1, 8, 4);
    creaArco(grafo, 8, 9, 29);
    creaArco(grafo, 9, 2, 20);
    creaArco(grafo, 9, 3, 13);
    creaArco(grafo, 9, 4, 5);
    creaArco(grafo, 9, 5, 28);
}


void creaArco(Isola **grafo, int sorgente, int destinazione, int pesoMax) {
    Isola *tmp = creaIsola(destinazione, pesoMax);
    grafo[sorgente] = inserisciIsolaInCoda(grafo[sorgente], tmp);
    /*
    tmp = creaIsola(sorgente, pesoMax);
    grafo[destinazione] = inserisciIsolaInCoda(grafo[destinazione], tmp);
    */
}


void stampaGrafo(Isola **grafo) {
    for(int i = 0; i < 10; i++) {
        stampaAdiacenti(grafo[i]);
        printf("\n");
    }
}


void stampaAdiacenti(Isola *nodo) {
    if(nodo) {
        printf(" Isola %d peso %d", nodo->codice + 1, nodo->pesoMax);
        if(nodo->next) {
            printf(" ->");
        }
        stampaAdiacenti(nodo->next);
    }
}


void liberaGrafo(Isola **grafo) {
    for(int i = 0; i < 10; i++) {
        liberaLista(grafo[i]);
    }
}


void cercaPercorso(char *username, int partenza, int destinazione, int pesoTot, int flag) {
    int pred[10];
    int dist[10];

    bfsPesata(partenza, destinazione, pred, dist, pesoTot);
    
    if(dist[destinazione] != -1){
        printf("\nIl percorso da seguire è:\n");
        stampaPercorso(partenza, destinazione, pred);
        printf("\n\nIl numero di ponti da percorrere è: %d\n",dist[destinazione]);
        if(flag == 0){
            registraViaggio(username, pesoTot, partenza, destinazione);
        }
    } else {
        printf("\nIl tuo camion è troppo pesante per poter passare dall'isola %d all'isola %d\n", partenza + 1, destinazione + 1);
    }
    printf("\n");
}


void bfsPesata(int partenza, int destinazione, int *pred, int *dist, int pesoTot) {

    int colore[10];

    for(int i = 0; i < 10; i++) {
        colore[i] = 0;
        pred[i] = -1;
        dist[i] = -1;
    }
  
    dist[partenza] = 0;
    colore[partenza] = 1;

    int coda[12];
    creaCoda(coda);
    accoda(coda, grafo[partenza]->codice);
    Isola *isola, *tmp;
    
    while(!codaVuota(coda)) {
        isola = grafo[leggiInTesta(coda)];

        tmp = isola;
        while(tmp->next) {
            if(colore[tmp->next->codice] == 0 && (tmp->next->pesoMax * 10) >= pesoTot) {
                colore[tmp->next->codice] = 1;
                pred[tmp->next->codice] = isola->codice;
                dist[tmp->next->codice] = dist[isola->codice] + 1;
                accoda(coda, tmp->next->codice);
            }
            tmp = tmp->next;
        }
        decoda(coda);
        colore[isola->codice] = 2;
    }

}


void stampaPercorso(int partenza, int destinazione, int *pred) {
    if(partenza == destinazione) {
        printf("%d ", partenza + 1);
    }  else {
        stampaPercorso(partenza, pred[destinazione], pred);
        printf("-> %d ", destinazione + 1);
    }
}

