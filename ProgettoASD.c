/* inclusione delle librerio */
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>

/* struttura dinamica ad albero bianrio */
typedef struct albero
{
    int             anno;                   /* valore intero compreso tra 1900 e 2021 */

    char            id_veicolo[7],          /* valore alfanumerico composto da 4 lettere e 2 numeri */
                    nome_proprietario[7],   /* valore alfanumerico composto da 3 lettere e 3 numeri */
                    modelli[19];            /* valore alafanumerico composto da caratteri alfanumerici (puo' essere composto da sole lettere o da soli numeri o da un isieme di questi*/
    struct  albero  *sx,                    /* puntatore al nodo sinistro dell'albero */
                    *dx;                    /* puntatore al nodo destro dell'albero */
}albero;


/****************************************************/
/*              DICHIARAZIONI FUNZIONI              */
/****************************************************/

/* funzione per l'apertura del file in lettura */
int ApriFileLettura(FILE **file);

/* funzione per l'apertura del file in scrittura */
int ApriFileScrittura(FILE **file);

/* funzione che inserisce i valori */
int Inserimento(albero **radice, albero *nodo, int *passi);

/* funzione che controlla se i valori tra i nodi sono uguali */
int NodiUguali(albero *n1, albero *n2);

/* funzione che controlla se un nodo è minore dell'altro */
int NodoMinore(albero *n1, albero *n2);

/* funzione che visita l'albero in modo simmetrico e stampa gli id dei veicoli */
void StampaIdAlbero(albero *nodo);

/* funzione che cerca nell'albero e stampa i valori dell'id del veicolo scelto */
int CercaIdAlbero(albero *radice, char id_veicolo[6], int *passi);

/* funzione che verifica se il nome dell'id_veicolo e' accettabile */
void VerificaIdVeicolo(char id_veicolo[7]); 

/* funzione che inserisce nuovo veicolo nell'albero specificato dall'utente e ristampa tutto il file aggiornato */
void InserisciNuovoElemento(albero **radice, albero *nodo, FILE *file, int *passi);

/* funzione che crea l'albero */
void CreaAlbero(albero **radice, albero *nodo, FILE *file, int *passi);

/* funzione che stampa l'albero sul file */
void StampaAlbero(albero *nodo, FILE *file);

/* funzione che stampa effetivamente l'albero su file senza aprirlo e chiuderlo */
void StampaAlberoParziale(albero *nodo, FILE *file);

/* funzione che rimuove un elemento dall'albero e ristampa i dati su file */
int RimuoviElemento(albero **radice, char id_veicolo[7], FILE *file, int *passi);

/* funzione che restitusce il valore piu' grande */
int RicercaMax(albero *nodo, int *passi);

/* funzione che restituisce il valore piu' piccolo */
int RicercaMin(albero *nodo, int *passi);


/********************************************************/
/*              DEFINIZIONE FUNZIONE MAIN               */
/********************************************************/
int main (void)
{
    /* dichiarazione variabili locali */
    int     opzione,            /* variabile utilizzata per scegliere come proseguire */
            verifica,           /* variabile di controllo per verificare il corretto inserimento */
            controllo,          /* utilizzato per il comportamento in base al tentativo di apertura del file */
            passi;              /* variabile utilizzata per il conteggio dei passi degli algoritmi */
    char    id_veicolo[7];      /* id del veicolo scelto dall'utente */
    FILE    *dati = NULL;       /* file */
    albero  *radice = NULL,     /* nodo radice */
            *nodo   = NULL;     /* nodo per l'inserimento */
    

    do
    {
        controllo = ApriFileLettura(&dati);            	/* apro il file in lettura */
        if (controllo == 1)                           	/* caso in cui sia stato aperto correttamente il file */
        {
            /* lettura dei dati da file e creazione dell'albero */
            CreaAlbero(&radice, nodo, dati, &passi);

            /* visualizzazione degli id dei veicoli */
            printf("\nLista degli id dei veicoli che sono stati analizzati:\n");
            StampaIdAlbero(radice);     		/* stampa gli id dei veicoli contenuti nel file */

            /* scelta e validazione dell'opzione da parte dell'utente */
            do
            {

                printf("\nSelezionare l'opzione che si vuole eseguire:\n(1) Cerca\n(2) Inserisci nuovo elemento\n(3) Rimuovi un elemento\n(4) Calcola il valore piu' grande e quello piu' piccolo\n(0) Termina\n\nNumero:\t");
                verifica = scanf("%d", &opzione);
                if ((verifica == 0) || ((opzione !=0) && (opzione != 1) && (opzione != 2) && (opzione != 3) && (opzione != 4)))
                    printf("Opzione non valida...\tRiprovare\n");
                while(getchar() != '\n');
            }while((verifica == 0) || ((opzione !=0) && (opzione != 1) && (opzione != 2) && (opzione != 3) && (opzione != 4)));

            switch (opzione)
            {
            case 1:             /* caso in cui l'utente abbia scelto di effettuare una ricerca */

                passi = 0;
                VerificaIdVeicolo(id_veicolo);      /* acquisiszione dell'id del veicolo scelto */
                /* ricerca dei dati relativi al veicolo scelto */
                if( !CercaIdAlbero(radice, id_veicolo, &passi))
                    printf("\nNon e' stato trovato alcun veicolo, (attenzione inserire lettere maiuscole!)\n");
                    
                printf("\nI passi compiuti dall'algoritmo per trovare e stampare i dati del veicolo richiesto sono: %d\n", passi);
		        printf("\n------------------------------------------------------------------------------------------------\n");
                
                break;

            case 2:             /* caso in cui l'utente desidera aggiungere un elemento*/
                passi = 0;
                InserisciNuovoElemento(&radice, nodo, dati, &passi);

                printf("\nI passi compiuti dall'algoritmo per inserire i dati sono: %d\n", passi);
		        printf("\n------------------------------------------------------------------------------------------------\n");

                break;

            case 3:             /* caso in cui l'utente abbia scelto di rimuovere un elemento */
                passi = 0;
		        VerificaIdVeicolo(id_veicolo);
                if(RimuoviElemento(&radice, id_veicolo, dati, &passi) == 0)
                    printf("\nNon e' stato trovato nessun elemento da eliminare\n");
                else
                    printf("\nVeicolo rimosso\n");
                printf("\nI passi compiuti dall'algoritmo per rimuovere l'elemento selezionato sono: %d\n", passi);
		        printf("\n------------------------------------------------------------------------------------------------\n");

                break;

            case 4:		/* caso in cui l'utente abbia scelto di trovare il valore piu' grande e piu' piccolo */
                passi = 0;
                RicercaMax(radice, &passi);
                printf("\nI passi compiuti dall'algoritmo per trovare il valore piu' grande sono: %d\n", passi);
                passi = 0;
                RicercaMin(radice, &passi);
                printf("\nI passi compiuti dall'algoritmo per trovare il valore piu' piccolo sono: %d\n", passi);
		        printf("\n------------------------------------------------------------------------------------------------\n");

                break;
                
            default:
                break;
            }


            /* assegnazione a nodo e radice di valore = NULL per evitare conflitti quando viene riletto il file e ricreata la struttura */
            nodo = NULL;
            radice = NULL;
        }
        else                                    /* caso in cui il file non venga aperto correttamente, esce dal do while e termina il programma*/
        {
            printf("\nNon e' stato possibile aprire correttamente il file...\nPerfavore controllare la sua esistenza e/o posizione\n");
            opzione = 0;
        }

        fclose(dati);                           /* chiusura del file */
    } while (opzione != 0);


    printf("\nFINE PROGRAMMA\n");
    return 0;

}/* end main */


/****************************************************/
/*              DEFINIZIONE FUNZIONI                */
/****************************************************/

/* ApriFileLettura */
int ApriFileLettura(FILE **file)
{
    /* apro il file in lettura */
    *file = fopen("dati.txt", "r");
    /* verifico la corretta apertura del file */
    if(*file == NULL)
        return 0;
    else 
        return 1;
}/* end ApriFileLettura */

/* ApriFileScrittura */
int ApriFileScrittura(FILE **file)
{
    /* apro il file in scrittura */
    *file = fopen("dati.txt", "w");
    /* verifico la corretta apertura del file */
    if(*file == NULL)
        return 0;
    else 
        return 1;
}/* end ApriFileScrittura */

/* Inserimento */
int Inserimento(albero **radice, albero *nodo, int *passi)
{
    /* dichiarazione variabili locali */
    int     esito;          /* variabile di ritorno */
    albero  *attuale,       /* nodo attuale */
            *padre;         /* nodo padre */

    /* scorrimento dell'albero per il posizionamento della foglia */
    for(attuale = padre = *radice;
        ((attuale != NULL) && (!NodiUguali(attuale, nodo)));
        padre = attuale, attuale = NodoMinore(nodo, attuale) ? attuale -> sx : attuale -> dx)
	{
    		*passi += 1;
	}
    /* verifica che non ci siano ripetizioni */
    if(attuale != NULL)
        esito = 0;
    else
    {          
        esito = 1;

        if(attuale == *radice)  /* nel caso l'albero sia vuoto, inserimento dell'elemento come radice */
        {
            *radice = nodo;
        }
        else                    /* altrimenti l'inserimento avviene a sinistra se l'elemento è minore, altrimenti a destra */
        { 
            if(NodoMinore(nodo, padre))
                padre -> sx = nodo;
            else
                padre -> dx = nodo;
        }
        *passi += 1;
    }    
    return esito;
}/* end Inserimento */

/* NodiUguali */
int NodiUguali(albero *n1, albero *n2)
{
    /* dichiarazione variabili locali */ 
    int esito = 0;  /* valore di ritorno */

    /* controllo se i valori tra i nodi sono uguali */
    if(strcmp(n1 -> id_veicolo, n2 -> id_veicolo) == 0)
        esito = 1;
    return esito;
}/* end NodiUguali */


/* NodoMinore */
int NodoMinore(albero *n1, albero *n2)
{
    /* dichiarazione variabili locali */
    int esito = 0;  /* variabile di ritorno */
    /* se il primo e' minore del secondo, ritorna 1 */
    if(strcmp(n1 -> id_veicolo, n2 -> id_veicolo) < 0)
        esito = 1;
    return esito;
}/* end NodoMinore*/

/* StampaIdAlbero */
void StampaIdAlbero(albero *nodo)
{
    if(nodo != NULL)
    {
        /* analizza l'albero partendo dal sotto albero sinistro per poi procedere verso destra */
        StampaIdAlbero(nodo -> sx);
        printf("\t%s\n", nodo -> id_veicolo);
        StampaIdAlbero(nodo -> dx);
    }
}/* end StampaIdAlbero */

/* CercaIdAlbero */
int CercaIdAlbero(albero *radice, char id_veicolo[6], int *passi)
{
    /* dichiarazione variabili locali */
    albero  *attuale;      /* nodo attuale */
    int     esito = 0;     /* variabile di ritorno */

    /* scorrimento dell'albero per trovare il nodo passato alla funzione */
    for (attuale = radice;
        (attuale != NULL) && (strcmp(attuale -> id_veicolo, id_veicolo) != 0);
        attuale = (strcmp(id_veicolo, attuale -> id_veicolo) < 0) ? attuale -> sx: attuale -> dx)
	{
    		*passi += 1;
	}

    /* caso in cui abbia trovato un id veicolo con lo stesso nome */
    if(attuale != NULL)
    {
        esito = 1;
        /* stampa del nodo */
        printf("\nEcco i dati riguardanti il veicolo selezionato:\n");
        printf("%s\t%s\t%s\t%d\n",
                attuale -> id_veicolo,  attuale -> nome_proprietario,   attuale -> modelli, attuale -> anno);
        *passi += 1;

    }
    return esito;
}/* end CercaIdAlbero */

/* VerificaIdVeicolo */
void VerificaIdVeicolo(char id_veicolo[7])
{
    /* dichiarazione variabili locali */
    int esito,
        lunghezza_id;     /* variabile utilizzata per controllare la lunghezza dell'id del veicolo inserito dall'utente */
    
    /* scelta dell veicolo da parte dell'utente */
    printf("\nInserire l'id di un veicolo sopra-visualizzato:\n");
    do
    {
        esito = (scanf("\n%s", id_veicolo));
        lunghezza_id = strlen(id_veicolo);

        if((esito != 1) || (lunghezza_id != 6))
            printf("\nErrore nell'aquisizione dell'id del veicolo scelto...\nControllare la lunghezza dell'id inserito\n");
        while (getchar() != '\n');
    } while ((esito != 1) || (lunghezza_id != 6));
}/* end VerificaIdVeicolo*/

/* InserisciNuvoElemento */
void InserisciNuovoElemento(albero **radice, albero *nodo, FILE *file, int *passi)
{
    int esito_id,
        esito_proprietario,
        esito_modello,
        esito_anno,
        i = 0;

    /* creazione di un nuovo nodo */
    nodo =(albero*)malloc(sizeof(albero));
    nodo -> dx = nodo -> sx = NULL;
   
    /* ciclo che permette di richiedere all'utente di inserire nuovamente l'id del veicolo correttamente prima di procedere con la prossima domanda */ 
    do
    {
        printf("\nInserire l'id del veicolo:\n\t");
        /* acquisizione e controllo dell'id inserito dall'utente */
        if((scanf("%s", nodo -> id_veicolo)) == 1)
        {
            i = 0;
            /* controllo dell'id inserito dall'utente */
            do
            {
                /* controllo dei primi 4 valori come lettere maiuscole */
                if((i < 5) && ((nodo -> id_veicolo[i] > 64) && (nodo -> id_veicolo[i] < 91)))
                    esito_id = 1;
                /* controllo degli ultimi 2 valori come numeri */
                else if(((i >= 4) && (i < 7)) && ((nodo -> id_veicolo[i] > 47) && (nodo -> id_veicolo[i] < 58)))
                    esito_id = 1;
                else			/* caso in cui l'utente non ha inserito un id accettabile */
                {
                    esito_id = 0;
                    printf("\nIl valore immesso non e' corretto\nInserire solo 4 lettere maiuscole e 2 numeri\n");
                }   
                i++;
            } while ((i < 6) && (esito_id == 1));
        }/* fine del controllo */
    } while (esito_id != 1); 
        
    /* ciclo che permette di richiedere all'utente di inserire nuovamente il nome del proprietario del veicolo correttamente prima di procedere con la prossima domanda */
    do
    {
        printf("\nInserire il nome del proprietario\n\t");
        /* acquisizione e controllo del proprietario inserito dall'utente */
        if((scanf("%s", nodo -> nome_proprietario)) == 1)
        {
            i = 0;
            /* controllo del proprietario inserito dall'utente */
            do
            {
                /* controllo dei primi 3 valori come lettere maiuscole */
                if((i < 4) && ((nodo -> nome_proprietario[i] > 64) && (nodo -> nome_proprietario[i] < 91)))
                    esito_proprietario = 1;
                /* controllo degli ultimi 3 valori come numeri */
                else if(((i >= 3) && (i < 7)) && ((nodo -> nome_proprietario[i] > 47) && (nodo -> nome_proprietario[i] < 58)))
                    esito_proprietario = 1;
                else				/* caso in cui l'utente non ha inserito un nome accettabile */
                {
                    esito_proprietario = 0;
                    printf("\nIl valore immesso non e' corretto\nInserire solo 3 lettere maiuscole e 3 numeri\n");
                }
                i++;
            } while ((i < 6) && (esito_proprietario == 1));
        }/* fine del controllo */
    } while (esito_proprietario != 1);
        
    /* ciclo che permette di richiedere all'utente di inserire nuovamente il modello del veicolo correttamente prima di procedere con la prossima domanda */
    do
    {
        printf("\nInserire il modello del veicolo\nNB. I caratteri dopo uno spazio non verranno acquisiti\n\t");
        /* acquisizione e controllo del modello inserito dall'utente */
        if((scanf("%s", nodo -> modelli) ) == 1 && (strlen(nodo -> modelli) < 19))
            esito_modello = 1;
        else					/* caso in cui l'utente non ha inserito un nome accettabile */
        {
            esito_modello = 0;
            printf("\nIl valore immesso non e' corretto\nInserire massimo 20 caratteri separati da un trattino\n");
        }
        while (getchar() != '\n');
    } while (esito_modello != 1);
        
    /* ciclo che permette di richiedere all'utente di inserire l'anno finche' non ne viene inserito uno accettabile*/
    do
    {
         printf("\nInserire l'anno del veicolo\n\t");
        /* acquisizione e controllo dell'anno del veicolo inserito dall'utente */
        if(((scanf("%d", &nodo -> anno)) == 1) && ((nodo -> anno > 1899) && (nodo -> anno < 2022)))
            esito_anno = 1;
        else					/* caso in cui l'utente non ha inserito un nome accettabile */
        {
            esito_anno = 0;
            printf("\nIl valore immesso non e' corretto\nInserire correttamente l'anno\n");
        }   
        while (getchar() != '\n'); 
    } while (esito_anno != 1);

    /* richiamo alla funzione per inserire il nodo appena creato nell'albero */
    Inserimento(radice, nodo, passi);
    /* stampa l'albero aggiornato nel file */
    StampaAlbero(*radice, file);

}/* end InserisciNuovoElemento */

/* CreaAlbero */
void CreaAlbero(albero **radice, albero *nodo, FILE *file, int *passi)
{
    int     esito;
    /* acquisizione dei dati dal file */
    do                   
    {
        /* creazione di un nuovo nodo */
        nodo = (albero*)malloc(sizeof(albero));
        nodo -> dx = nodo -> sx = NULL;
        /* lettura dei valori del nodo successivo */
        esito = fscanf(file, "%s    %s  %s  %d", 
                      (nodo -> id_veicolo),  (nodo -> nome_proprietario),    (nodo -> modelli),  &(nodo -> anno));
        if(esito == 4)
            if( !Inserimento(radice, nodo, passi))        /* chiamata alla funzione che crea l'albero */
                printf("\nInserimento non riuscito\n");
    } while ( esito != EOF );

}/* end CreaAlbero */

/* StampaAlbero */
void StampaAlbero(albero *nodo, FILE *file)
{
    /* scorrimento dell'albero partendo dalla radice e stampa di ogni valore su file */
    if(ApriFileScrittura(&file))
    {
        StampaAlberoParziale(nodo, file);
    }
    else				
        printf("\nCi sono stati problemi durante l'apertura del file, controllare la sua esistenza e/o posizione\n");
    fclose(file);
}/* end StampaAlbero */

/* StampaAlberoParziale */
void StampaAlberoParziale(albero *nodo, FILE *file)
{
    if(nodo != NULL)
    {
        /* analizzo l'albero partendo dal sotto albero sinistro per poi procedere verso destra */
 	    fprintf(file, "%s\t%s\t%s\t%d\n\r", 
                (nodo -> id_veicolo),  (nodo -> nome_proprietario),    (nodo -> modelli),  (nodo -> anno));

        StampaAlberoParziale(nodo -> sx, file);
        StampaAlberoParziale(nodo -> dx, file);

    }
} /* end StampaAlberoParziale */

/* RimuoviElemento */
int RimuoviElemento(albero **radice, char id_veicolo[7], FILE *file, int *passi)
{
    /* dichiarazione variabili locali */
    int     rimosso;		/* variabile di ritorno */
    albero  *attuale,
            *padre,
            *sostituto;
    
    /* scorrimento dell'albero per il posizionamento della foglia */
    for(attuale = padre = *radice;
        ((attuale != NULL) && ((strcmp(attuale -> id_veicolo, id_veicolo) != 0)));
        padre = attuale, attuale = (( strcmp(id_veicolo, attuale -> id_veicolo) < 0) ? (attuale -> sx) : (attuale -> dx)))
	{
    		*passi += 1;
	}

    /* se 'attuale' è vuoto significa che non ci sta nulla da poter rimuovere*/ 
    if(attuale == NULL)
        rimosso = 0;
    else
    {
        rimosso = 1;
        if(attuale -> sx == NULL)
        {
            if(attuale == *radice)
                *radice = attuale -> dx;
            else
                if((strcmp(id_veicolo, padre -> id_veicolo)) < 0 )
                    padre -> sx = attuale -> dx;
                else
                    padre -> dx = attuale -> dx;
	        *passi += 1;
        }
        else
            if(attuale -> dx == NULL)
            {
                if(attuale == *radice)
                    *radice = attuale -> sx;
                else
                    if( (strcmp(id_veicolo, padre -> id_veicolo ) < 0))
                        padre -> sx = attuale -> sx;
                    else
                        padre -> dx = attuale -> sx;
		        *passi += 1;
            }
            else
            {
                sostituto = attuale;
                for(padre = sostituto, attuale = sostituto -> sx;
                    (attuale -> dx != NULL); padre = attuale, attuale = attuale -> dx)
                {
                    *passi += 1;
                }
                strcpy(sostituto -> id_veicolo, attuale -> id_veicolo);

                if(padre == sostituto)
                    padre -> sx = attuale -> sx;
                else    
                    padre -> dx = attuale -> sx;
		        *passi += 1;

            }
        free(attuale);
    }
    /* stampa l'albero aggiornato nel file */
    StampaAlbero(*radice, file);

    return (rimosso);
} /* end RimuoviElemento */

/* RicercaMax */
int RicercaMax(albero *nodo, int *passi)
{
    /* funzione ricorsiva che scorre l'albero fino a sinistra fino ad arrivare all'estremo */
    if(nodo -> sx != NULL)
    {
        RicercaMax(nodo -> sx, passi);
        *passi += 1;
    }
    else	/* raggiunto l'estremo stampo l'id */
    {
        printf("\nIl valore piu`grande e':\t%s\n", nodo -> id_veicolo);
        *passi += 1;        
    }
    return 0;
}/* end RicercaMax */
 
/* RicercaMin */
int RicercaMin(albero *nodo, int *passi)
{
    /* funzione ricorsiva che scorre l'albero fino a sinistra fino ad arrivare all'estremo */
    if(nodo -> dx != NULL)
    {
        RicercaMin(nodo -> dx, passi);
        *passi += 1;
    }
    else	/* raggiunto l'estremo stampo l'id */
    {
        printf("\nIl valore piu' piccolo e':\t%s\n", nodo -> id_veicolo);
        *passi += 1;        
    }
    return 0;
}/* end RicercaMin */
