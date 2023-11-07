#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

typedef char oitem; 

typedef struct tpno_aux {   
    struct tpno_aux *antatual;  
    oitem info;  
    struct tpno_aux *prox;   
} nohh; 

typedef struct {   
    nohh *ini;   
    nohh *fim;   
    int tam;   
} listadupenc;

listadupenc *inicializa_listadupenc(){
    listadupenc *lista = (listadupenc*) malloc(sizeof(listadupenc));   
    lista->ini = NULL;   
    lista->fim = NULL;   
    lista->tam = 0;   
    return lista;
}  


int listadupenc_vazia(listadupenc *lista) {
	if (lista->ini == NULL) return 1;
	return 0;	
}

nohh *aloca_listadupenc() {
	nohh* pt;
	pt = (nohh*) malloc(sizeof(nohh));
	return pt;
}

listadupenc *aloca_listadupenc_sem_ser_no() {
	listadupenc* pt;
	pt = (listadupenc*) malloc(sizeof(listadupenc));
	return pt;
}

int insere_listadupenc_no_fim (listadupenc *lista, oitem e){   
    nohh *novono;   
    novono = aloca_listadupenc();
    if (!novono) return 0;
    novono->info = e;  

    if (listadupenc_vazia(lista)){
        novono->prox = NULL;   
        novono->antatual = NULL; 
        lista->ini = lista->fim = novono;
    }  

    else{
        novono->prox = NULL;   
        novono->antatual = lista->fim; 
        lista->fim->prox = novono;
        lista->fim = novono;
    }  
    
    lista->tam++; 

    return 1;   
}        

void imprime_listadupenc(listadupenc *lista, int ordem){

	if(lista==NULL) printf("Lista não inicializada");
	else{

        nohh *atual; 

        switch (ordem){
            case 1: 
                atual = lista->ini;
                while (atual != NULL){
                   printf("%c ", atual->info);
                   atual = atual->prox;           
                }
                break; 
                  
            case 2: 
                atual = lista->fim;
                while (atual != NULL){
                   printf("%c ", atual->info);
                   atual = atual->antatual;           
                   }
                break; 

            default: printf("codigo invalido");        
        }
	}
    printf("\n");
}


int remove_listadupenc(listadupenc *lista, oitem e){   

    nohh *atual;
    atual = lista->ini;

    while ((atual != NULL) && (atual->info != e)) atual = atual->prox;

    if (atual == NULL) return 0;  

    if (lista->ini == lista->fim) lista->ini = lista->fim = NULL;
   
    else if (lista->ini == atual){
        lista->ini = atual->prox;
        atual->prox->antatual = NULL;
    }
    
    else if (lista->fim == atual){ 
        lista->fim = atual->antatual;
        atual->antatual->prox = NULL;              
    }  

    else{
        atual->prox->antatual = atual->antatual;   
        atual->antatual->prox = atual->prox;
    } 

   lista->tam--; 


   return 1;   
}        

nohh* busca_listadupenc (listadupenc *lista, oitem e){   
    nohh *atual;
    atual = lista->ini;
    while ((atual != NULL) && (atual->info != e)) atual = atual->prox;
    return atual;
}     

int tamanho_listadupenc(listadupenc *lista){
    return lista->tam;
}

listadupenc * destroi_listadupenc (listadupenc *lista){   
    nohh *atual;
    atual = lista->ini;
    while (atual != NULL){ 
        lista->ini = atual->prox;
        free(atual);
        atual=lista->ini;
	}

    lista->tam = 0;

    free(lista);
    return NULL;
}  


int jogo(listadupenc *lista){

    int contadado = 0;
    char player = 'a';

    insere_listadupenc_no_fim(lista, player);
    insere_listadupenc_no_fim(lista,'b');
    insere_listadupenc_no_fim(lista,'1');
    insere_listadupenc_no_fim(lista,'0');
    insere_listadupenc_no_fim(lista,'e');
    insere_listadupenc_no_fim(lista,'f');
    insere_listadupenc_no_fim(lista,'2');
    insere_listadupenc_no_fim(lista,'w');
    insere_listadupenc_no_fim(lista,'1');
    insere_listadupenc_no_fim(lista,'i');

    nohh *atu;
    atu = aloca_listadupenc();
    //atu = busca_listadupenc(lista, player);
    atu = lista->ini;
    
    srand(time(NULL));

    while(player != 'i'){
        
        int dado, i = 1, j = 0;
        
        dado = (rand() % 6) + 1;
        
        
        while((i <= dado) && (atu->prox != NULL)){
        	atu = atu->prox;
        	i++;
		}

        if(isdigit(atu->info)){
            if(atu->info == '0'){
                nohh *atuaux;
                atuaux = aloca_listadupenc();
                atuaux = atu->prox;
                remove_listadupenc(lista, atu->info);
                player = atuaux->info;
                atu = atuaux;
            }
        
            else{
                int volta = atu->info - 48;
                while(j < volta){
                	atu = atu->antatual;
                	j++;
				}
                player = atu->info;
            }
        }

        else player = atu->info;
        
        //player = atu->info
        contadado++;
    }
    
    return contadado;
}

int main(){

    listadupenc *caminho;
    caminho = inicializa_listadupenc();

    printf("O dado foi lancado %d vezes.\n", jogo(caminho));
    
    printf("\n");
    
    return 0;
}

