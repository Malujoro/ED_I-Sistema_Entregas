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
} Cliente;

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

void *desaloca(void *vetor)
{
    free(vetor);
    return NULL;
}

// ======================================= Cliente ============================================ 

Cliente cliente_cria(char *nome, char *endereco, char *cpf)
{
    Cliente cliente;

    cliente.cpf = cpf;
    cliente.nome = nome;
    cliente.endereco = endereco;

    return cliente;
}

void *cliente_desaloca(Cliente *cliente)
{
    free(cliente);
    return NULL;
}

void cliente_exibir(Cliente cliente)
{
    printf("Nome: %s\n", cliente.nome);
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
    printf("Destinatário: %s", produto.destinatario);
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
            printf("\n");
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
            printf("\n");
            aux = aux->anterior;
        }
    }
}

// ======================================= Entregas ============================================ 

void cadastrar_rota(Fila *fila)
{
    codigo_geral += 1;

    char *destinatario = aloca_str(100);
    char *endereco = aloca_str(100);
    
    printf("\nDestinatário: ");
    scanf("%[^\n]", destinatario);
    limpa_buffer();

    printf("Endereço: ");
    scanf("%[^\n]", endereco);
    limpa_buffer();

    Produto produto = produto_cria(destinatario, endereco, codigo_geral);
    fila_push(fila, produto);
}

void realizar_entrega(Fila *entregas, Fila *devolucoes, int *score)
{
    if(fila_vazia(entregas))
    {
        printf("\nNão há rotas cadastrada\n");
        return;
    }

    printf("\n[INÍCIO DA ROTA DE IDA]");

    Pilha *pilha = pilha_cria();

    int num, entregue;

    Produto produto;

    while(!fila_vazia(entregas))
    {
        num = rand() % 10;
        entregue = num >= 2;
        // entregue = num < 2;

        fila_pop(entregas, &produto);

        printf("\n");
        produto_exibir(produto);
        printf("\n");
        if(entregue)
        {
            printf("[Entregue]");
            *score += 5;
            produto.destinatario = desaloca(produto.destinatario);
            produto.endereco = desaloca(produto.endereco);
        }
        else
        {
            printf("[Não entregue]");
            pilha_push(pilha, produto);
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

        printf("\n");
        produto_exibir(produto);
        printf("\n");
        if(entregue)
        {
            printf("[Entregue]");
            *score += 3;
            produto.destinatario = desaloca(produto.destinatario);
            produto.endereco = desaloca(produto.endereco);
        }
        else
        {
            *score -= 1;
            printf("[Não entregue]");
            fila_push(devolucoes, produto);
        }
    }
    printf("\n[FIM DA ROTA DE VOLTA]\n");
}

void menu_principal()
{
    Fila *entregas = fila_cria();
    Fila *devolucoes = fila_cria();
    int scoreTotal = 0, score;
    char op;

    do
    {
        printf("\nMenu\n");
        printf("[1] - Cadastrar cliente\n");
        printf("[2] - Exibir todos os clientes\n");
        printf("[3] - Cadastrar rota\n");
        printf("[4] - Exibir rota completa\n");
        printf("[5] - Realizar entrega\n");
        printf("[6] - Exibir fila de devoluções\n");
        printf("[0] - Sair\n");
        printf("Opção: ");
        op = getchar();
        limpa_buffer();

        switch(op)
        {
            case '1':
                printf("\nCadastrar cliente\n");
                break;

            case '2':
                printf("\nExibir todos os clientes\n");
                break;

            case '3':
                cadastrar_rota(entregas);
                break;
            
            case '4':
                fila_imprimir(entregas);
                break;
            
            case '5':
                score = 0;
                realizar_entrega(entregas, devolucoes, &score);
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
}

// ======================================= Main ============================================ 

int main()
{
    srand(time(NULL));
    menu_principal();
    return 0;
}