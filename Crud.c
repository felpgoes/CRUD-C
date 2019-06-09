#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct dados {
            char nome [25];
            char endereco [50];
            char niver_dia [20];
            char niver_mes [20];
            char niver_ano [40];
            char cidade [20];
            char estado [20];
            char cep [9];

            };

void inclui();
void lista();
int pesquisa_nome();
int pesquisa_letra();
int pesquisa_niver();
int pesquisa_cep();
void altera();
void exclui();
int z=0;

int main()
{
        struct dados info;
        struct dados *p;
        int op;
        int i;
        int tam;    //n. de bytes da estrutura

        p = & info;
        tam = sizeof(info);

        for(i=0;i<sizeof(info);i++) {   //zera a estrutura de dados
            info.nome[i]=0;
           }
        while(1){
        printf(" 1 - INCLUIR PERFIS\n");
        printf(" 2 - LISTAR PERFIS  \n");
        printf(" 3 - PESQUISAR   \n");
        printf(" 4 - ALTERAR PERFIL    \n");
        printf(" 5 - EXCLUIR PERFIL    \n");
        printf(" 6 - SAIR   \n");
        scanf("%d", &op);
        getchar();


    switch(op)
                {
                case 1 : inclui(p, tam);   //passa como parametro o ponteiro para a estrutura e o n. de bytes da desta
                break;

                case 2: lista(p, tam);
                break;

                case 3:
                    printf("\nPesquisar Por: \n");
                    printf(" 1 - Nome\n");
                    printf(" 2 - Primeira Letra  \n");
                    printf(" 3 - Mes de Aniversario   \n");
                    printf(" 4 - CEP    \n");
                    scanf("%d", &op);
                    switch(op){
                        case 1:
                            {
                                pesquisa_nome(p, tam);
                                break;
                            }
                        case 2:
                            {
                                pesquisa_letra(p, tam);
                                break;
                            }
                        case 3:
                            {
                                pesquisa_niver(p, tam);
                                break;
                            }
                        case 4:
                            {
                                pesquisa_cep(p, tam);
                                break;
                            }
                            }
                break;

                case 4: altera(p, tam);
                break;

                case 5: exclui(p, tam);
                break;

                case 6: exit(0);
                break;

                default: printf("\n opcao invalida\n");
                }
    };

}

void inclui(struct dados *ps, int tam)
{
    FILE *p, *p1;
    int cont = 0;
    int i;

    p1 = fopen("contador.txt", "r");
    fscanf(p1,"%d",&cont);
    printf("contador antes %d\n",cont);
    fclose(p1);

    for(i=0;i<tam;i++){ //zera os dados da estrutura
        ps -> nome[i]=0;
    }

    p = fopen("arquivo.txt", "a");

    if( p == NULL){
        printf("\nARQUIVO NAO EXISTE!");
        exit(1);
    }

    printf("DIGITE O NOME DO PERFIL: ");//aqui os dados sao recebidos via teclado
    gets(ps->nome);// usar gets()

    printf("DIGITE O ENDERECO: ");//aqui os dados sao recebidos via teclado
    gets(ps->endereco);// usar gets()

    printf("DIGITE O DIA DE NASCIMENTO: ");//aqui os dados sao recebidos via teclado
    gets(ps->niver_dia);// usar gets()

    printf("DIGITE O MES DE NASCIMENTO: ");//aqui os dados sao recebidos via teclado
    gets(ps->niver_mes);// usar gets()

    printf("DIGITE O ANO DE NASCIMENTO: ");//aqui os dados sao recebidos via teclado
    gets(ps->niver_ano);// usar gets()

    printf("DIGITE A CIDADE: ");//aqui os dados sao recebidos via teclado
    gets(ps->cidade);// usar gets()

    printf("DIGITE O ESTADO: ");//aqui os dados sao recebidos via teclado
    gets(ps->estado);// usar gets()

    printf("DIGITE O CEP: ");//aqui os dados sao recebidos via teclado
    gets(ps->cep);// usar gets()


    fwrite(ps, tam,1,p);
    fclose(p);


    cont++;

    p1 = fopen("contador.txt", "w");
    fprintf(p1,"%d",cont);
    printf("contador depois %d\n",cont);
    fclose(p1);
}

void lista(struct dados *ps, int tam)
{
    FILE *p, *p1;
    FILE *a;
    struct dados info;
    int i;
    int cont,comp;

    p1 = fopen("contador.txt", "r");
    fscanf(p1,"%d",&cont);
    printf("%d\n",cont);
    fclose(p1);

    p = fopen("arquivo.txt", "r"); /*r" --> Abre o arquivo apenas para leitura.*/

    if( p== NULL)
        {
        puts("\nARQUIVO NAO EXISTE!\n");
        exit(1);
    }

    a = fopen("contador.txt", "r");
    fscanf(a,"%d",&cont);
    fclose(a);

    for(i=0;i<cont; i++){
        comp = i*tam;   //calcula o n. de bytes para posicionar o ponteiro do arquivo

    fseek(p,comp,0);    //posiciona o ponteiro no inicio do registro dentro do arquivo
    fread(ps,sizeof(info),1,p);   //le o registro
    if(ps -> nome[0] != '*'){     //verifica se esta apagado
    printf("\tNOME: ");
    puts(ps->nome);
    printf("\tENDERECO: ");
    puts(ps->endereco);
    printf("\tDATA DE NASCIMENTO: %s/%s/%s\n",ps->niver_dia,ps->niver_mes,ps->niver_ano);
    printf("\tCIDADE: ");
    puts(ps->cidade);
    printf("\tESTADO: ");
    puts(ps->estado);
    printf("\tCEP: ");
    puts(ps->cep);//imprimi registro na tela
    printf("\n");

        }
    }
        fclose(p);
}

int pesquisa_nome(struct dados *ps, int tam)
{
    FILE *p;
    FILE *a;

    char nome1[25];
    int i=0,y, x;
    int cont;

    printf("DIGITE UM NOME PARA PESQUISAR: ");
    gets(nome1);

    p = fopen("arquivo.txt", "r");
    a = fopen("contador.txt", "r");
    fscanf(a,"%d",&cont);
    fclose(a);
    printf("%d\n",cont);

     if( p == NULL){
        printf("\nARQUIVO NAO EXISTE!");
        exit(1);
    }

    for(y=0;y<cont;y++)
    {
        fread(ps,tam,1,p);
        for(x = 0; nome1[x] != '\0';x++){
            if(nome1[x] != ps -> nome[x]){
                break;
            }
        }

    if(nome1[x] == '\0' && ps -> nome[x] == '\0')
    {
        printf("\tPERFIL NUMERO: %d\n",y);
        printf("\tNOME: ");
        puts(ps->nome);
        printf("\tENDERECO: ");
        puts(ps->endereco);
        printf("\tDATA DE NASCIMENTO: %s/%s/%s\n",ps->niver_dia,ps->niver_mes,ps->niver_ano);
        printf("\tCIDADE: ");
        puts(ps->cidade);
        printf("\tESTADO: ");
        puts(ps->estado);
        printf("\tCEP: ");
        puts(ps->cep);
        printf("\n");
        return y;
    }
    }
    printf("ESSE PERFIL NAO EXISTE!\n");
    return -1;
}

int pesquisa_letra(struct dados *ps, int tam)
{
    FILE *p;
    FILE *a;

    char inicial;
    int i=0,y, x;
    int cont;

    printf("DIGITE UMA LETRA PARA PESQUISAR: ");
    scanf("%s",&inicial);

    p = fopen("arquivo.txt", "r");
    a = fopen("contador.txt", "r");
    fscanf(a,"%d",&cont);
    fclose(a);
    printf("%d\n",cont);

     if( p == NULL){
        printf("\nARQUIVO NAO EXISTE!");
        exit(1);
     }

 for(y=0;y<cont;y++)
    {
    fread(ps,tam,1,p);
    if(inicial == ps -> nome[0])
    {
        printf("\tPERFIL NUMERO: %d\n",y);
        printf("\tNOME: ");
        puts(ps->nome);
        printf("\tENDERECO: ");
        puts(ps->endereco);
        printf("\tDATA DE NASCIMENTO: %s/%s/%s\n",ps->niver_dia,ps->niver_mes,ps->niver_ano);
        printf("\tCIDADE: ");
        puts(ps->cidade);
        printf("\tESTADO: ");
        puts(ps->estado);
        printf("\tCEP: ");
        puts(ps->cep);//imprimi registro na tela
        printf("\n");
        //return y;
    }
    }
    if(inicial != ps -> nome[0]){
    printf("NAO EXISTEM PERFIS COM ESSA INICIAL!\n");
    return -1;
    }
}

int pesquisa_niver(struct dados *ps, int tam)
{
    FILE *p;
    FILE *a;

    char mes[20];
    int i=0,y, x;
    int cont;

    printf("DIGITE UM MES DE ANIVERSARIO PARA PESQUISAR: ");
    scanf("%s",&mes);

    p = fopen("arquivo.txt", "r");
    a = fopen("contador.txt", "r");
    fscanf(a,"%d",&cont);
    fclose(a);
    printf("%d\n",cont);

     if( p == NULL){
        printf("\nARQUIVO NAO EXISTE!");
        exit(1);
     }

    for(y=0;y<cont;y++){
    fread(ps,tam,1,p);
     if(mes[0] == ps -> niver_mes[0]){
         if(mes[1] == ps -> niver_mes[1]){
            printf("\tPERFIL NUMERO: %d\n",y);
            printf("\tNOME: ");
            puts(ps->nome);
            printf("\tENDERECO: ");
            puts(ps->endereco);
            printf("\tDATA DE NASCIMENTO: %s/%s/%s\n",ps->niver_dia,ps->niver_mes,ps->niver_ano);
            printf("\tCIDADE: ");
            puts(ps->cidade);
            printf("\tESTADO: ");
            puts(ps->estado);
            printf("\tCEP: ");
            puts(ps->cep);//imprimi registro na tela
            printf("\n");
        }
    }
    if(mes[0] != ps -> niver_mes[0]){
         if(mes[1] != ps -> niver_mes[1]){
            printf("NAO EXISTEM PERFIS COM ANIVERSARIO NESSE MES!\n");
        }
    }
}
}

int pesquisa_cep(struct dados *ps, int tam)
{
    FILE *p;
    FILE *a;

    char cep1[9];
    int i=0,y, x;
    int cont;

    printf("DIGITE UM CEP PARA PESQUISAR: ");
    scanf("%s",&cep1);

    p = fopen("arquivo.txt", "r");
    a = fopen("contador.txt", "r");
    fscanf(a,"%d",&cont);
    fclose(a);
    printf("%d\n",cont);

     if( p == NULL){
        printf("\nARQUIVO NAO EXISTE!");
        exit(1);
    }

    for(y=0;y<cont;y++)
    {
        fread(ps,tam,1,p);
        for(x = 0; cep1[x] != '\0';x++){
            if(cep1[x] != ps -> cep[x]){
                break;
            }
        }

    if(cep1[x] == '\0' && ps -> cep[x] == '\0')
    {
        printf("\tPERFIL NUMERO: %d\n",y);
        printf("\tNOME: ");
        puts(ps->nome);
        printf("\tENDERECO: ");
        puts(ps->endereco);
        printf("\tDATA DE NASCIMENTO: %s/%s/%s\n",ps->niver_dia,ps->niver_mes,ps->niver_ano);
        printf("\tCIDADE: ");
        puts(ps->cidade);
        printf("\tESTADO: ");
        puts(ps->estado);
        printf("\tCEP: ");
        puts(ps->cep);//imprimi registro na tela
        printf("\n");
        return y;
    }
    }
    printf("NAO EXISTEM PERFIS COM ESSE CEP!\n");
}



void altera(struct dados *ps, int tam)
{
    FILE *p;
    int n_reg;;
    int n_bytes;

    n_reg = pesquisa_nome(ps, tam);     //pesquisa o registro no arquivo
    printf("ALTERAR O REGISTRO  NUMERO: %d\n",n_reg);
    if(n_reg == -1){
 	     return;
    }
    n_bytes = tam * n_reg;

    p = fopen("arquivo.txt", "r+");

    fseek(p,n_bytes,0);       //posioiona o ponteiro do arquivo no registro a ser alterado
    fread(ps, tam, 1, p );  //le registro do arquivo

    printf("INSIRA UM NOVO PERFIL!\n");

    inclui(ps, tam);

    fseek(p,n_bytes,0);    //posiciona o ponteiro do arquivo no inicio do regisro a ser alterado
    fwrite(ps, tam,1,p);  //escreve o registro no arquivo

    fclose(p);
}

void exclui(struct dados *ps, int tam)
{
    FILE *p;
    int n_reg;
    int n_bytes;
    n_reg = pesquisa_nome(ps, tam);  //pesquisa o registro no arquivo
    if(n_reg == -1){
 	     return;
    }
    p = fopen("arquivo.txt", "r+");
    n_bytes = tam * n_reg;

    fseek(p,n_bytes,0);       //posioiona o ponteiro do arquivo no registro a ser apagado
    fread(ps, tam, 1, p );   //le o registro do arquivo
    printf("NOME QUE SERA EXCLUIDO: %s\n",ps -> nome);
    ps->nome[0]='*';//apaga o registro do arquivo

    fseek(p,n_bytes,0);  //posiciona o ponteiro do arquivo no inicio do regisro a ser apagado
    fwrite(ps,tam,1,p);  //escreve o registro

    fclose(p);

}
