#include <stdio.h>
#include <stdlib.h>

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
    printf("Código: %d\n", produto.codigo);
    printf("Endereço: %s\n", produto.endereco);
    printf("Destinatário: %s\n", produto.destinatario);
}

// ======================================= Fila ============================================ 

void *fila_desaloca(void *vetor)
{
    free(vetor);
    return NULL;
}

int fila_vazia(Fila *f)
{
    return f->quant == 0;
}

fila_No *fila_no_cria(Produto v)
{
    fila_No *node = (fila_No *) malloc(sizeof(fila_No));

    if(!node)
    {
        printf("Erro ao alocar no");
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
        printf("Erro ao alocar fila");
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
    {
        printf("Erro! A fila está vazia");
        return 0;
    }

    if(f->quant == 1) 
        f->ultimo = NULL;

    fila_No *aux = f->primeiro;
    *v = aux->value;
    f->primeiro = aux->proximo;
    aux = fila_desaloca(aux);
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
        aux1 = fila_desaloca(aux1);
        aux1 = aux2;
    }

    f = fila_desaloca(f);
}

void fila_imprimir(Fila *fila)
{
    fila_No *aux = fila->primeiro;

    while(aux != NULL)
    {
        produto_exibir(aux->value);
        printf("\n");
        aux = aux->proximo;
    }
}

// ======================================= Pilha ============================================ 

void *pilha_desaloca(void *vetor)
{
    free(vetor);
    return NULL;
}

int pilha_vazia(Pilha *p)
{
    return p->quant == 0;
}

pilha_No *pilha_no_cria(Produto v)
{
    pilha_No *node = (pilha_No *) malloc(sizeof(pilha_No));

    if(!node)
    {
        printf("Erro ao alocar no");
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
        printf("Erro ao alocar pilha");
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
    {
        printf("Erro! A pilha está vazia");
        return 0;
    }

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
        aux1 = pilha_desaloca(aux1);
        aux1 = aux2;
    }

    p = pilha_desaloca(p);
}

void pilha_imprimir(Pilha *pilha)
{
    pilha_No *aux = pilha->node;

    while(aux != NULL)
    {
        produto_exibir(aux->value);
        printf("\n");
        aux = aux->anterior;
    }
}

// ======================================= Main ============================================ 

int main()
{
    printf("\n[Início da Fila]\n");
    Fila *fila = fila_cria();
    fila_push(fila, produto_cria("Mateus da rocha sousa", "Av. 123", 1));
    fila_push(fila, produto_cria("Mateus2", "Av. 222", 2));
    fila_push(fila, produto_cria("Mateus3", "Av. 333", 3));

    printf("\n[Fim da inserção]\n");

    fila_imprimir(fila);

    printf("\n[Elemento removido]\n");
    Produto prod;
    fila_pop(fila, &prod);
    produto_exibir(prod);

    printf("\n[Fila após remoção]\n");
    fila_imprimir(fila);

    printf("\n[Início da Pilha]\n");
    
    Pilha *pilha = pilha_cria();
    pilha_push(pilha, produto_cria("Mateus da rocha sousa", "Av. 123", 1));
    pilha_push(pilha, produto_cria("Mateus2", "Av. 222", 2));
    pilha_push(pilha, produto_cria("Mateus3", "Av. 333", 3));

    printf("\n[Fim da inserção]\n");
    
    pilha_imprimir(pilha);

    printf("\n[Elemento removido]\n");
    
    pilha_pop(pilha, &prod);
    produto_exibir(prod);

    printf("\n[Pilha após remoção]\n");
    pilha_imprimir(pilha);

    // Pilha *pilha = pilha_cria();
    // pilha_push(pilha, )
    // Cliente teste2 = cliente_cria("Mateus da rocha sousa", "Av. 123", "123.123.123-12");
    // cliente_exibir(teste2);
    return 0;
}