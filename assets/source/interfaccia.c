#include "../header/header.h"


void pause(char *messaggio){
    fflush(stdin);
    char c[10];

    printf("\n\n");
    printf("%s", messaggio);
    printf("\n");
    printf("Digita un carattere per continuare...");  
    scanf("%s", c);

    fflush(stdin);
}


void chiudi() {
    exit(0);
}


void clear(){
    system("clear");
}


void menu() {
    fflush(stdin);
    fflush(stdout);
    clear();
    char sel[64];

    printf("Benvenuto in I-Eats!\nProcedi selezionando la voce di interesse\n\n");
    printf("1. Registrati\n");
    printf("2. Accedi\n");
    printf("99. Chiudi\n");
    printf("\n");
    printf("Inserisci il numero corrispondente: ");
    scanf("%s", sel);

    clear();

    switch(atoi(sel)) {
        case 1:
            registrazione();
            break;
        case 2:
            accesso();
            break;
        case 99:
            chiudi();
            break;
        default:
            break;
    }
    return;
}


void menuDriver( char *username, int pesoCamion){
    clear();
    printf("Benvenuto %s, a secco il tuo camion pesa %d quintali\n\n",username,pesoCamion);
    fflush(stdin);
    fflush(stdout); 
    char sel[64];

    printf("1. Effettua consegna\n");
    printf("2. Storico consegne\n");
    printf("3. Logout\n");
    printf("99. Chiudi\n");
    printf("\n");
    printf("Inserisci il numero corrispondente: ");
    scanf("%s", sel);

    clear();

    switch(atoi(sel)) {
        case 1:
            effettuaConsegna(username, pesoCamion);
            break;
        case 2:
            visualizzaStorico(username);
            break;
        case 3:
            return;
            break;
        case 99:
            chiudi();
            break;
        default:
            menuDriver(username, pesoCamion);
            break;
    }
    menuDriver(username, pesoCamion);
    return;
}