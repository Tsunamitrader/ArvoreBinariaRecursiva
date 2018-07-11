#include<stdio.h>
#include<stdlib.h>

typedef struct Arvore {
    int num, altd, alte;
    Arvore *esq, *dir;
}Arvore;

Arvore *rotacaoEsq(Arvore *aux){
    Arvore *aux1, *aux2;

    aux1 = aux->dir;
    aux2 = aux1->esq;
    aux->dir = aux2;
    aux1->esq = aux;

    if(aux->dir == NULL)
        aux->altd = 0;
    else if (aux->dir->alte > aux->dir->altd)
        aux->altd = aux->dir->alte+1;
    else
        aux->altd = aux->dir->altd+1;

    if(aux1->esq->alte > aux1->esq->altd)
        aux1->alte = aux1->esq->alte +1;
    else
        aux1->alte = aux1->esq->altd +1;

    return aux1;

}

Arvore *rotacaoDir(Arvore *aux){
    Arvore *aux1, *aux2;

    aux1 = aux->esq;
    aux2 = aux1->dir;
    aux->esq = aux2;
    aux1->dir = aux;

    if(aux->esq == NULL)
        aux->alte = 0;
    else if (aux->esq->alte > aux->esq->altd)
        aux->alte = aux->esq->alte+1;
    else
        aux->alte = aux->esq->altd+1;

    if(aux1->dir->alte > aux1->dir->altd)
        aux1->altd = aux1->dir->alte +1;
    else
        aux1->altd = aux1->dir->altd +1;

    return aux1;
}

Arvore *balanceamento(Arvore *aux){
    int d,df;

    d = aux->altd - aux->alte;

    if(d == 2){
        df = aux->dir->altd - aux->dir->alte;
        if(df >=0)
            aux = rotacaoEsq(aux);
        else{
            aux->dir = rotacaoDir(aux->dir);
            aux = rotacaoEsq(aux);
        }
    }
    else if (d == -2){
        df = aux->esq->altd - aux->esq->alte;
        if(df <= 0 )
            aux = rotacaoDir(aux);
        else{
            aux->esq = rotacaoEsq(aux->esq);
            aux = rotacaoDir(aux);
        }
    }

    return aux;
}

Arvore *inserir (Arvore *aux, int num){

    if (aux==NULL){

        aux=(Arvore*)malloc(sizeof(Arvore));

        if (aux==NULL){
            printf("sem memoria");
            exit(1);
        }

        aux->num=num;
        aux->altd = 0;
        aux->alte = 0;
        aux->esq=NULL;
        aux->dir=NULL;
    }

    else if(num < aux->num){
        aux->esq=inserir(aux->esq, num);

        if(aux->esq->altd > aux->esq->alte)
            aux->alte = aux->esq->altd +1;
        else
            aux->alte = aux->esq->alte +1;

        // balanceando...
        aux = balanceamento(aux);
    }

    else{
        aux->dir=inserir(aux->dir, num);

        if(aux->dir->altd > aux->dir->alte)
            aux->altd = aux->dir->alte + 1;
        else
            aux->altd = aux->dir->alte + 1;

        aux = balanceamento(aux);
    }

    return aux;
}

int consultar (Arvore *aux, int num, int achou){
    if(aux!=NULL && achou==0){
        if(aux->num==num)
            achou = 1;
        else if(num < aux->num)
            achou=consultar(aux->esq, num, achou);
        else
            achou=consultar(aux->dir, num, achou);
    }
    return achou;
}

void mostraEmOrdem(Arvore *aux){
    if(aux!=NULL){
        mostraEmOrdem(aux->esq);
        printf(" %d ", aux->num);
        mostraEmOrdem(aux->dir);
    }
}

void mostraPreOrdem (Arvore *aux){
    if(aux!=NULL){
        printf(" %d ", aux->num);
        mostraPreOrdem(aux->esq);
        mostraPreOrdem(aux->dir);
    }
}

void mostraPosOrdem (Arvore *aux){
    if(aux!=NULL){
        mostraPosOrdem(aux->esq);
        mostraPosOrdem(aux->dir);
        printf(" %d ", aux->num);
    }
}

Arvore* remover(Arvore *aux, int num){
    Arvore *p, *p2;

    if(aux->num==num){
        if(aux->esq==aux->dir){
            free(aux);
            return NULL;
        }
        else if(aux->esq==NULL){
            p=aux->dir;
            free(aux);
            return p;
        }
        else if(aux->dir==NULL){
            p=aux->esq;
            free(aux);
            return p;
        }
        else{
            p2=aux->dir;
            free(aux);
            return p2;
        }
    }
    else if(aux->num<num)
        aux->dir=remover(aux->dir,num);
    else
        aux->esq=remover(aux->esq,num);

    return aux;
}

Arvore *atualiza(Arvore *aux){
    if(aux != NULL){

        aux->esq = atualiza(aux->esq);

        if(aux->esq == NULL)
            aux->alte = 0;
        else if (aux->esq->alte > aux->esq->altd)
            aux->alte = aux->esq->alte +1;
        else
            aux->alte = aux->esq->altd +1;

        aux->dir = atualiza(aux->dir);

        if(aux->dir == NULL)
            aux->altd = 0;
        else if(aux->dir->alte > aux->dir->altd)
            aux->altd = aux->dir->alte +1;
        else
            aux->altd = aux->dir->altd + 1;

        aux = balanceamento(aux);
    }
    return aux;
}


Arvore *desalocar(Arvore *aux){
    if(aux!=NULL){
        aux->esq=desalocar(aux->esq);
        aux->dir=desalocar(aux->dir);
        printf(" \nRemovendo %d ",aux->num);
        free(aux);
    }
    return NULL;
}

int main(){

    Arvore *raiz=NULL;
    Arvore *aux;
    int op, achou, numero;

    do{
        system("CLS");
        if(raiz != NULL)
            printf("O valor da raiz %d", raiz->num);

        printf("\nMenu de Opcao\n1-Inserir\n2-Consultar NO da Arvore\n3-Consultar em Ordem\n4-Consulta Em Pre-Ordem\n5-Consulta em Pos-Ordem\n6-Excluir\n7-Esvaziar Arvore\n8-Sair\nEscolha Opcao:\n");
        scanf("%d",&op);

        switch(op){

            case 1:
                printf("Digite o Elemento:\n ");
                scanf("%d", &numero);
                raiz=inserir(raiz, numero);
                printf("Valor inserido\n");
                break;

            case 2:
                if(raiz==NULL)
                    printf("Lista Vazia\n");
                else{
                    printf("Digite o elemento a ser consultado\n");
                    scanf("%d", &numero);
                    achou=0;
                    if(consultar(raiz, numero, achou)==0)
                        printf("Valor nao Encontrado\n");
                    else
                        printf("Valor Encontrado\n");
                }
                break;

            case 3:
                if(raiz==NULL)
                    printf("Arvore vazia\n");
                else{
                    printf("\n Listando em Ordem \n");
                    mostraEmOrdem(raiz);
                }
                break;

            case 4:
                if(raiz==NULL)
                    printf("Arvore Vazia\n");
                else{
                    printf("\n Listando Pre-Ordem\n");
                    mostraPreOrdem(raiz);
                }
                break;

            case 5:
                if(raiz==NULL)
                    printf("Arvore vazia\n");
                else{
                    printf("\n Listando em Pos-Ordem\n");
                    mostraPosOrdem(raiz);
                }
                break;

            case 6:
                if(raiz==NULL)
                    printf("Arvore Vazia\n");
                else{
                    printf("Digite o Elemento\n");
                    scanf("%d",&numero);
                    achou=0;
                    if (consultar(raiz, numero, achou)==0)
                        printf("Valor Nao Encontrado\n");
                    else{
                        raiz=remover(raiz, numero);
                        raiz = atualiza(raiz);
                        printf("Valor Removido\n");
                    }
                }
                break;

            case 7:
                if(raiz==NULL)
                    printf("Arvore Vazia\n");
                else{
                    raiz=desalocar (raiz);
                    printf("\nArvore Removida\n");
                }
                break;

            case 8:
                if(raiz!=NULL){
                    printf("\nFazendo a Faxina\n");
                    raiz=desalocar(raiz);
                }
                 break;

            default:
                printf("OP Invalida\n");
                break;

        }
        printf("\n\n");
        system("Pause");
    }while (op!=8);

return 0;
}


