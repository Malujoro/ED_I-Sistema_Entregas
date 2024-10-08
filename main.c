#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int codigo_geral = 0;

// ======================================= Structs ============================================ 

typedef struct cliente
{
    char *nome;
    char *endereco;
    char *cpf;
    struct cliente *proximo;
} Cliente;

typedef struct lista
{
    int quant;
    Cliente *primeiro;
} Lista;

typedef struct produto
{
    int codigo;
    char *destinatario;
    char *endereco;
} Produto;

typedef struct fila_no
{
    Produto value;
    struct fila_no *proximo;
} fila_No;

typedef struct fila
{
    int quant;
    fila_No *ultimo;
    fila_No *primeiro;
} Fila;

typedef struct pilha_no
{
    Produto value;
    struct pilha_no *anterior;
} pilha_No;

typedef struct pilha
{
    pilha_No *node;
    int quant;
} Pilha;

// ======================================= Auxiliar ============================================ 

void limpa_buffer()
{
    while(getchar() != '\n');
}

char *aloca_str(int tam)
{
    char *vetor = (char *)malloc(sizeof(char) * tam);

    if(!vetor)
    {
        printf("Erro ao alocar str");
        exit(EXIT_FAILURE);
    }

    return vetor;
}

int *aloca_int(int tam)
{
    int *vetor = (int *)calloc(sizeof(int), tam);

    if(!vetor)
    {
        printf("Erro ao alocar int");
        exit(EXIT_FAILURE);
    }

    return vetor;
}

int *realoca_int(int *vet, int tam)
{
    int *vet2 = realloc(vet, sizeof(int) * tam);

    if(!vet2)
    {
        printf("Erro ao realocar vetor int");
        return vet;
    }

    return vet2;
}

void *desaloca(void *vetor)
{
    free(vetor);
    return NULL;
}

// ======================================= Cliente ============================================ 

Cliente *cliente_cria(char *nome, char *endereco, char *cpf)
{
    Cliente *cliente = (Cliente *) malloc(sizeof(Cliente));

    if(!cliente)
    {
        printf("\nErro ao alocar cliente\n");
        exit(EXIT_SUCCESS);
    }

    cliente->cpf = cpf;
    cliente->nome = nome;
    cliente->endereco = endereco;
    cliente->proximo = NULL;

    return cliente;
}

void *cliente_desaloca(Cliente *cliente)
{
    free(cliente);
    return NULL;
}

void cliente_exibir(Cliente cliente)
{
    printf("\nNome: %s\n", cliente.nome);
    printf("Endereço: %s\n", cliente.endereco);
    printf("CPF: %s\n", cliente.cpf);
}

// ======================================= Produto ============================================ 

Produto produto_cria(char *destinatario, char *endereco, int codigo)
{
    Produto produto;
    
    produto.codigo = codigo;
    produto.destinatario = destinatario;
    produto.endereco = endereco;
    
    return produto;
}

void produto_exibir(Produto produto)
{
    printf("\nCódigo: %d\n", produto.codigo);
    printf("Endereço: %s\n", produto.endereco);
    printf("Destinatário: %s\n", produto.destinatario);
}

// ======================================= Lista Encadeada ============================================ 

Lista *lista_cria(void)
{
    Lista *lista = (Lista *) malloc(sizeof(Lista));

    if(!lista)
    {
        printf("\nErro ao alocar lista\n");
        exit(EXIT_FAILURE);
    }
    
    lista->primeiro = NULL;
    lista->quant = 0;
    return lista;
}

void lista_add(Lista *lista, Cliente *cliente)
{
    lista->quant += 1;
    if(lista->primeiro == NULL)
    {
        lista->primeiro = cliente;
        return;
    }

    Cliente *aux = lista->primeiro;


    while(aux->proximo != NULL)
        aux = aux->proximo;

    aux->proximo = cliente;
}

void lista_exibir(Lista *lista)
{
    if (lista->primeiro == NULL)
        printf("\nLista vazia\n");
    else
    {
        Cliente *aux = lista->primeiro;
        while (aux != NULL)
        {
            cliente_exibir(*aux);
            aux = aux->proximo;
        }
    }
}

void lista_libera(Lista *lista)
{
    if (lista == NULL)
        printf("Lista vazia ");
    else
    {
        Cliente *aux = lista->primeiro;
        Cliente *aux2;
        while (aux != NULL)
        {
            aux->nome = desaloca(aux->nome);
            aux->endereco = desaloca(aux->endereco);
            aux->cpf = desaloca(aux->cpf);

            aux2 = aux->proximo;
            aux = desaloca(aux);
            aux = aux2;
        }
    }
}

// ======================================= Fila ============================================ 

int fila_vazia(Fila *f)
{
    return f->quant == 0;
}

fila_No *fila_no_cria(Produto v)
{
    fila_No *node = (fila_No *) malloc(sizeof(fila_No));

    if(!node)
    {
        printf("\nErro ao alocar no\n");
        exit(EXIT_FAILURE);
    }

    node->value = v;
    node->proximo = NULL;
    return node;
}

Fila *fila_cria(void)
{
    Fila *fila = (Fila *) malloc(sizeof(Fila));

    if(!fila)
    {
        printf("\nErro ao alocar fila\n");
        exit(EXIT_FAILURE);
    }
    
    fila->primeiro = NULL;
    fila->ultimo = NULL;
    fila->quant = 0;
    return fila;
}

void fila_push(Fila *f, Produto v)
{
    fila_No *novo = fila_no_cria(v);

    if(f->quant == 0) 
        f->primeiro = novo;
    else 
        f->ultimo->proximo = novo;
    
    f->ultimo = novo;
    f->quant++;
}

int fila_pop(Fila *f, Produto *v)
{
    if(fila_vazia(f))
        return 0;

    if(f->quant == 1) 
        f->ultimo = NULL;

    fila_No *aux = f->primeiro;
    *v = aux->value;
    f->primeiro = aux->proximo;
    aux = desaloca(aux);
    f->quant--;
    return 1;
}

void fila_libera(Fila *f)
{
    fila_No *aux1 = f->primeiro;
    fila_No *aux2;

    while(aux1 != NULL)
    {
        aux2 = aux1->proximo;
        aux1 = desaloca(aux1);
        aux1 = aux2;
    }

    f = desaloca(f);
}

void fila_imprimir(Fila *fila)
{
    fila_No *aux = fila->primeiro;

    if(fila_vazia(fila))
        printf("\nA fila está vazia\n");
    else
    {
        while(aux != NULL)
        {
            produto_exibir(aux->value);
            aux = aux->proximo;
        }
    }
}

// ======================================= Pilha ============================================ 

int pilha_vazia(Pilha *p)
{
    return p->quant == 0;
}

pilha_No *pilha_no_cria(Produto v)
{
    pilha_No *node = (pilha_No *) malloc(sizeof(pilha_No));

    if(!node)
    {
        printf("\nErro ao alocar no\n");
        exit(EXIT_FAILURE);
    }

    node->value = v;
    node->anterior = NULL;
    return node;
}

Pilha *pilha_cria(void)
{
    Pilha *pilha = (Pilha *) malloc(sizeof(Pilha));

    if(!pilha)
    {
        printf("\nErro ao alocar pilha\n");
        exit(EXIT_FAILURE);
    }
    
    pilha->node = NULL;
    pilha->quant = 0;
    return pilha;
}

void pilha_push(Pilha *p, Produto v)
{
    pilha_No *node = pilha_no_cria(v);
    node->anterior = p->node;
    p->node = node;
    p->quant++;
}

int pilha_pop(Pilha *p, Produto *v)
{
    if(pilha_vazia(p))
        return 0;

    pilha_No *newFinal = p->node->anterior;
    *v = p->node->value;
    free(p->node);
    p->node = newFinal;
    p->quant--;

    return 1;
}

void pilha_libera(Pilha *p)
{
    pilha_No *aux1 = p->node;
    pilha_No *aux2;

    while(aux1 != NULL)
    {
        aux2 = aux1->anterior;
        aux1 = desaloca(aux1);
        aux1 = aux2;
    }

    p = desaloca(p);
}

void pilha_imprimir(Pilha *pilha)
{
    pilha_No *aux = pilha->node;
    
    if(pilha_vazia(pilha))
        printf("\nA pilha está vazia\n");
    else
    {
        while(aux != NULL)
        {
            produto_exibir(aux->value);
            aux = aux->anterior;
        }
    }
}

// ======================================= Entregas ============================================ 

void cadastrar_cliente(Lista *clientes)
{
    char *nome = aloca_str(100);
    char *endereco = aloca_str(100);
    char *cpf = aloca_str(100);
    
    printf("\nNome: ");
    scanf("%[^\n]", nome);
    limpa_buffer();

    printf("Endereço: ");
    scanf("%[^\n]", endereco);
    limpa_buffer();

    printf("CPF: ");
    scanf("%[^\n]", cpf);
    limpa_buffer();

    Cliente *cliente = cliente_cria(nome, endereco, cpf);
    lista_add(clientes, cliente);
}

void cadastrar_rota(Fila *fila, Lista *clientes, int *vet_enderecos)
{
    codigo_geral += 1;
    char *destinatario;
    char *endereco;
    int i, opcao;
    Cliente *aux;

    do
    {
        aux = clientes->primeiro;

        printf("\nLista de clientes:\n");

        for(i = 0; i < clientes->quant; i++)
        {
            printf("\n%dº cliente\n", i+1);
            printf("%s\n", aux->nome);
            printf("%s\n", aux->endereco);
            aux = aux->proximo;
        }

        printf("\nDigite número do cliente: ");
        scanf("%d", &opcao);

        limpa_buffer();

        if(opcao <= 0 || opcao > clientes->quant)
            printf("\nOpção inválida\n");
    }while(opcao <= 0 || opcao > clientes->quant);

    opcao--;
    aux = clientes->primeiro;
    i = 0;
    
    while(i < opcao)
    {
        aux = aux->proximo;
        i++;
    }

    vet_enderecos[i]++;

    destinatario = aux->nome;
    endereco = aux->endereco;

    Produto produto = produto_cria(destinatario, endereco, codigo_geral);
    fila_push(fila, produto);
}

int busca_endereco(Lista *clientes, char *endereco)
{
    Cliente *aux = clientes->primeiro;
    int cont = 0;

    while(aux != NULL)
    {
        if(aux->endereco == endereco)
            return cont;
        aux = aux->proximo;
        cont += 1;
    }
    return -1;
}

void realizar_entrega(Fila *entregas, Fila *devolucoes, Lista *clientes, int *vet_enderecos, int *score)
{
    if(fila_vazia(entregas))
    {
        printf("\nNão há rotas cadastrada\n");
        return;
    }

    printf("\n[INÍCIO DA ROTA DE IDA]");

    Pilha *pilha = pilha_cria();
    Fila *fila_auxiliar = fila_cria();

    int num, entregue, pos = 0, aux, quant;
    char *endereco;

    Produto produto;

    while(!fila_vazia(entregas))
    {
        num = rand() % 10;
        entregue = num >= 2;
        // entregue = num < 5;

        fila_pop(entregas, &produto);

        printf("\n");

        endereco = produto.endereco;
        pos = busca_endereco(clientes, endereco);
        aux = vet_enderecos[pos];
        quant = vet_enderecos[pos];
        
        while(aux > 0)
        {
            if(produto.endereco == endereco)
            {
                aux--;
                produto_exibir(produto);
                if(entregue)
                {
                    vet_enderecos[pos]--;
                    printf("[Entregue]\n");
                    *score += 5;
                }
                else
                {
                    printf("[Não entregue]\n");
                    pilha_push(pilha, produto);
                }
            }
            else
                fila_push(fila_auxiliar, produto);

            if(aux > 0)
                fila_pop(entregas, &produto);
            else if(aux == 0 && quant != 1)
            {
                while(!fila_vazia(entregas))
                {
                    fila_pop(entregas, &produto);
                    fila_push(fila_auxiliar, produto);
                }
                while(!fila_vazia(fila_auxiliar))
                {
                    fila_pop(fila_auxiliar, &produto);
                    fila_push(entregas, produto);
                }
            }
        }

    }
    
    printf("\n\n[FIM DA ROTA DE IDA]\n");

    if(pilha_vazia(pilha))
    {
        printf("\nTodos os produtos foram entregues na ida\n");
        return;
    }

    printf("\n\n[INÍCIO DA ROTA DE VOLTA]");

    while(!pilha_vazia(pilha))
    {
        num = rand() % 10;
        entregue = num >= 2;

        pilha_pop(pilha, &produto);
        endereco = produto.endereco;
        pos = busca_endereco(clientes, endereco);
        aux = vet_enderecos[pos];

        for(int i = aux; i > 0; i--)        
        {
            printf("\n");
            produto_exibir(produto);
            if(entregue)
            {
                printf("[Entregue]");
                *score += 3;
            }
            else
            {
                *score -= 1;
                printf("[Não entregue]");
                fila_push(devolucoes, produto);
            }
            if(i != 0)
                pilha_pop(pilha, &produto);
        }
    }
    printf("\n\n[FIM DA ROTA DE VOLTA]\n");

    pilha_libera(pilha);
    fila_libera(fila_auxiliar);
}

void menu_principal()
{
    Fila *entregas = fila_cria();
    Fila *devolucoes = fila_cria();
    Lista *clientes = lista_cria();
    int scoreTotal = 0, score, tam = 25;
    char op;
    int *vet_enderecos = aloca_int(25);

    do
    {
        printf("\nMenu\n");
        printf("[1] - Cadastrar cliente\n");
        printf("[2] - Exibir todos os clientes\n");
        printf("[3] - Cadastrar rota\n");
        printf("[4] - Exibir produtos da rota\n");
        printf("[5] - Realizar entrega\n");
        printf("[6] - Exibir fila de devoluções\n");
        printf("[0] - Sair\n");
        printf("Pontuação da transportadora: %d\n", scoreTotal);
        printf("Opção: ");
        op = getchar();
        limpa_buffer();

        switch(op)
        {
            case '1':
                cadastrar_cliente(clientes);
                if(clientes->quant > tam)
                {
                    int *vet_aux = realoca_int(vet_enderecos, tam+25);

                    if(vet_aux == vet_enderecos)
                        tam -= 25;
                    else
                    {
                        vet_enderecos = vet_aux;
                        tam += 25;
                    }
                }
                break;

            case '2':
                lista_exibir(clientes);
                break;

            case '3':
                if(clientes->quant > 0)
                    cadastrar_rota(entregas, clientes, vet_enderecos);
                else
                    printf("\nCadastre algum cliente antes de cadastrar as rotas\n");
                break;
            
            case '4':
                fila_imprimir(entregas);
                break;
            
            case '5':
                score = 0;
                realizar_entrega(entregas, devolucoes, clientes, vet_enderecos, &score);
                if(score)
                    printf("\n[Pontuação da rota: %d]\n", score);
                scoreTotal += score;
                break;

            case '6':
                printf("\n[Fila de devoluções]\n");
                fila_imprimir(devolucoes);
                break;

            case '0':
                printf("\nSaindo...\n");
                break;
            
            default:
                printf("\nOpção inválida!\n");
        }
    }while(op != '0');
    fila_libera(entregas);
    fila_libera(devolucoes);
    lista_libera(clientes);
}

// ======================================= Main ============================================ 

int main()
{
    srand(time(NULL));
    menu_principal();
    return 0;
}