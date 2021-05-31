#include "../header/header.h"


void creaCoda(int *Q) {
    for(int i = 0; i < 12; i++) {
        Q[i] = 0;
    }
    Q[11] = 1;
}


int codaVuota(int *Q) {
    return Q[0] == 0;
}


int codaPiena(int *Q) {
    return Q[0] == Q[11];
}


void accoda(int *Q, int isola) {
    if(codaVuota(Q)){
        Q[0]++;
    }
    Q[Q[11]] = isola;
    if(Q[11] == 10) {
        Q[11] = 1;
    } else {
        Q[11]++;
    }    
}


void decoda(int *Q) {
    Q[0] = (Q[0] % 10) + 1;
    if (codaPiena(Q)) {
        Q[0] = 0;
        Q[11] = 1;
    }
}


int leggiInTesta(int *Q) {
    return Q[Q[0]];
}