/********************************************
*  Programmazione I - Esonero Novembre 2018 *
*  @author: Gramoschi Rafael                *
********************************************/
#include <stdio.h>
#define BGRED   "\x1b[41m"// RED "\x1B[31m"
#define BGCYAN "\x1b[46m"
#define BGMAGENTA "\x1b[45m"
#define BGGREEN "\x1b[42m"
#define RESET "\x1B[0m"

int n; // numero giorni da prevedere
int k; // numero azioni comprate

int maxValore = -1000;
int maxValxGrafico = 0;
int indiceMax;
int minValore = 1000;
int indiceMin;

int somma = 0;

int ammontare = 0;
int guadagno = 0;

int main(){
    // richiesta numero di giorni da prevedere
    printf("\n[?] Quanti giorni vuoi prevedere? ");
    scanf("%d", &n );

    // calcolo ammontare e guadagno in base a 'k' (azioni comprate)
    printf("[?] Quante azioni hai intenzione di comprare? ");
    scanf("%d", &k );

    // inizializzazione valori e quotazioni delle azioni
    int val_azione[n];
    int quotazione[n-1];

    // Richiesta input e popolamento array
    printf("\n");
    for(int i=0; i<n; i++){

        printf("[?] Rosco, quanto vale l'azione il giorno %d ? ", i+1);
        scanf("%d", &val_azione[i]);

        if( i>0 && i<n ){
            //es.
            //quotazione[0] = val_azione[1] - val_azione[0]
            quotazione[i-1] = val_azione[i] - val_azione[i-1];
        }
    }

    // output dei dati immessi
    printf("\n");

    for(int i=0; i<n; i++){
        printf("[!] Valore azione giorno %d: %d\n", i+1, val_azione[i]);

        if( i<(n-1) ){
            printf("[!] Quotazione: %d\n", quotazione[i]);
        }
    }

    printf("\n[*] Dammi un momento, sto analizzando i dati ...\n");

    // controllo giorni migliori
    // vedendo minore e maggiore tra i valori
    for(int a=0; a<n; a++){
        if( val_azione[a] >= maxValore ){
            if( a == 0 ){
              maxValxGrafico = val_azione[a];
              continue;
            }
            indiceMax = a;
            maxValore = val_azione[a];
            if( maxValxGrafico < maxValore){
              maxValxGrafico = maxValore;
            }
        }
    }
    //printf("\n[DEBUG] MASSIMO VALORE: %d, MASSIMO PER IL GRAFICO: %d\n", maxValore, maxValxGrafico);

    for(int b=0; b<=indiceMax; b++){
        if( val_azione[b] <= minValore ){
            indiceMin = b;
            minValore = val_azione[b];
        }
    }
    //printf("\n[DEBUG] MINIMO VALORE: %d\n", minValore);

    for(int c=indiceMin; c<indiceMax; c++){
        somma += quotazione[c];
    }
/////////////////// CALCOLA E STAMPA MATRICE GRAFICO //////////////////
    //// CREA MATRICE CON DATI
    printf("\n");
    int matrix[maxValxGrafico][n];
    for(int g=0; g<n; g++){
      for(int v=val_azione[g]; v>=0; v--){
        if( val_azione[g]<maxValxGrafico ){
          for(int k=val_azione[g]+1;k<=maxValxGrafico;k++){
            matrix[k][g] = 1000;
          }
        }

        matrix[v][g] = val_azione[g];
      }
    }

    //////////////// STAMPA GRAFICO ////////////////
    printf("\n");
    printf("Val. azioni:\n\n");
    for(int x=maxValxGrafico; x>=0; x--){
      printf("%+3d)    ", x);
      for(int y=0; y<n; y++){
        if( matrix[x][y] == 1000 ){
          printf("%5s","");
          continue;
        }
        printf("%5d", matrix[x][y]);
      }
      printf("\n");
    }

    printf("\nGiorno: ");
    for(int g=0; g<n; g++){
        if(g+1==indiceMin+1){
          printf( "%4s" BGMAGENTA "%d" RESET, "", g+1);
        }else if(g+1 == indiceMax+1){
          printf( "%4s" BGCYAN "%d" RESET, "", g+1);
        }else{
          printf("%5d", g+1);
        }
    }
    printf("\n\n");

///////////////////////////////////////////////////////////////////////

    if(somma > 0){
        printf( "[OK]" BGMAGENTA " Compra il giorno %d" BGCYAN " e vendi il giorno %d" RESET "\n\n", indiceMin+1, indiceMax+1);
        // ammontare = totale riscosso dalla vendita
        ammontare = k * val_azione[indiceMax];
        guadagno = ammontare - ( k * val_azione[indiceMin] );
        printf( BGMAGENTA "Se compri %d azioni," BGCYAN "l'ammontare è %d," BGGREEN " ed il guadagno è %d." RESET "\n\n", k, ammontare, guadagno);

    }else if( somma <= 0 ){
        somma = 0;
        printf( BGRED "[ X ] Non comprare. Non c'e' guadagno." RESET);
        printf("\n\n");
    }

    printf("DONE.\n\n");

}

