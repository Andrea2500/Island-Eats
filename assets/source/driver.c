#include "../header/header.h"


void registrazione() {
    char username[60], password[60],peso[10];
    FILE *fp;
    printf("Inserisci i tuoi dati per procedere con la registrazione\n\n");
    printf("Inserisci username: ");
    scanf("%s",username);
    printf("Inserisci password: ");
    scanf("%s",password);
    printf("Inserisci in quintali il peso del tuo camion: ");
    scanf("%s",peso);
    while(atoi(peso) == 0){
        printf("\nInserisci un peso valido!\n\n");
        printf("Inserisci in quintali il peso del tuo camion: ");
        scanf("%s", peso);
    }
    fp = fopen("file/driver.txt", "a");
    fprintf(fp, "%s %s %d\n", username, password, atoi(peso));
    fclose(fp);
    pause("\n\nRegistrazione effettuata corretamente.\nVerrai reindirizzato nella tua dashboard.");
    menuDriver(username,atoi(peso));
    return;
}

void accesso() {
    char username[60], password[60], tmpUser[60], tmpPWD[60];
    int tmpPeso;
    int flag = 0;
    FILE *fp;

    printf("Inserisci le tue credenziali per accedere\n");
    printf("Inserisci username: ");
    scanf("%s",username);
    printf("Inserisci password: ");
    scanf("%s",password);

    fp = fopen("file/driver.txt" , "r");
    if(fp == NULL){
        pause("Errore durante l'esecuzione.\nRiprovare!");
        return;
    }

    while(fscanf(fp, "%s %s %d", tmpUser, tmpPWD, &tmpPeso) == 3){
        if(strcmp(username,tmpUser) == 0 && strcmp(password,tmpPWD) == 0){
            flag = 1;
            break;
        } 
    }
    fclose(fp);
    if (flag == 1){
        menuDriver(username,tmpPeso);
        return;
    }
    printf("\n Credenziali non valide.\n\n");
    printf("1. Riprovare\n");
    printf("2. Torna indietro\n");
    printf("Seleziona: ");
    char opt[100];
    scanf("%s",opt);
    if (atoi(opt) == 1){
        clear();
        accesso();
    }
    return;
}

void effettuaConsegna(char *username, int pesoCamion){
    
    int pesoSpesa, pesoTot, isolaSrc, isolaDest;

    printf("Seleziona gli alimenti che devi trasportare in questa consegna\n\n");
    printf("Indicare la quantità di lotti da aggiungere all'ordine:\n");
    pesoSpesa = preparaCarrello();
    printf("Inserici il codice dell'isola di partenza: ");
    isolaSrc = getCodiceIsola();
    printf("Inserici il codice dell'isola di destinazione: ");
    isolaDest = getCodiceIsola();
    clear();
    
    pesoTot = pesoCamion + pesoSpesa;
    printf("Riepilogo del viaggio\n");
    printf("Peso dell\'ordine: %d q (tot. %d q)\n",pesoSpesa,pesoTot);
    printf("Partenza: %d\n", isolaSrc + 1);
    printf("Destinazione: %d\n\n", isolaDest + 1);
    cercaPercorso(username,isolaSrc, isolaDest, pesoTot,0);
    pause("");

}

int preparaCarrello(){
    int pesoSpesa = 0;
    char qnt[20];

    for(int i = 0; i<(sizeof(inventario)/sizeof(Alimenti)); i++){
        printf("-%s (%d quintali/lotto): ",inventario[i].nome,inventario[i].pesoLotto);
        scanf("%s",qnt);
        pesoSpesa += atoi(qnt)*inventario[i].pesoLotto;
    }
    printf("\n\n");
    return pesoSpesa;
}

int getCodiceIsola(){
    char input[100];
    scanf("%s", input);
    while(atoi(input) < 1 || atoi(input) > 10 ){
        printf("Il valore inserito non è corretto!\nInserisci un codice valido (1-10): ");
        scanf("%s", input);
    }
    return atoi(input) - 1;
}

void registraViaggio(char *username, int pesoTrasportato, int partenza, int destinazione){
    FILE *fp;
    fp = fopen("file/storico.txt", "a");
    fprintf(fp, "%s %d %d %d\n",username,pesoTrasportato,partenza,destinazione);
    fclose(fp);
}

void visualizzaStorico(char *username){
    FILE *fp = fopen("file/storico.txt", "r");
    char tmpUser[100],opt[20];
    int tmpPeso,tmpSrc,tmpDest,i=1,flag = 0;
    printf("Storico consegne di %s\n\n",username);

    while(fscanf(fp, "%s %d %d %d",tmpUser,&tmpPeso,&tmpSrc,&tmpDest) == 4){
        if(strcmp(username, tmpUser) == 0){
            flag = 1;
            printf("%d) Da %d a %d (%d quintali)\n", i, tmpSrc+1, tmpDest+1, tmpPeso);
            i++;
        }
    }
    fclose(fp);

    if(flag == 0){
        pause("Non hai ancora effettuato consegne!\n");
    }else{
        printf("\n\n");
        printf("0. Continua\n");
        printf("Codice viaggio. Visualizza percorso aggiornato\n");
        printf("Inserisci il numero corrispondente: ");
    
        scanf("%s",opt);
        if(atoi(opt) == 0){
            return;
        }else{
            clear();
            visualizzaPercorsoStorico(username, atoi(opt));
        }
    }
    return;
}

void visualizzaPercorsoStorico(char *username, int posizione){
    FILE *fp = fopen("file/storico.txt", "r");
    char tmpUser[100],opt[20];
    int tmpPeso,tmpSrc,tmpDest,i=1;

    while(fscanf(fp, "%s %d %d %d",tmpUser,&tmpPeso,&tmpSrc,&tmpDest) == 4){
        if(strcmp(username, tmpUser) == 0){
            if(i == posizione){
                fclose(fp);
                printf("Percorso del viaggio da %d a %d. Trasportati %d quintali\n",tmpSrc+1,tmpDest+1,tmpPeso);
                cercaPercorso(username,tmpSrc, tmpDest, tmpPeso,1);
                pause("");
                clear();
                visualizzaStorico(username);
                return;
            }
            i++;
        }
    }
    fclose(fp);

    pause("Codice storico non trovato!\n");
    clear();
    visualizzaStorico(username);
    return;
}