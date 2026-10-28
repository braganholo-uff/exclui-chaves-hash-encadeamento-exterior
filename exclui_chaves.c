#include <stdio.h>
#include <stdlib.h>

typedef struct aluno {
    int matricula;
    float cr;
    struct aluno *prox;
} TAluno;

typedef TAluno *Hash;

/*
 * Função de hash: h(x) = x mod m
 */
int hash(int mat, int m) {
    return mat % m;
}

void inicializa(Hash *tab, int m) {
    int i;
    for (i = 0; i < m; i++) {
        tab[i] = NULL;
    }
}

TAluno *busca(Hash *tab, int m, int mat) {
    int h = hash(mat, m);
    TAluno *p = tab[h];
    while ((p != NULL) && (p->matricula != mat)) {
        p = p->prox;
    }
    return p;
}

TAluno *aloca(int mat, float cr) {
    TAluno *novo = (TAluno *) malloc(sizeof(TAluno));
    novo->matricula = mat;
    novo->cr = cr;
    novo->prox = NULL;
    return novo;
}

/*
 * Insere o registro no fim da lista do compartimento hash(mat, m)
 * Se a matrícula já existir na tabela, apenas atualiza o cr
 */
void insere(Hash *tab, int m, int mat, float cr) {
    int h = hash(mat, m);
    TAluno *p = tab[h];
    TAluno *ant = NULL;
    while ((p != NULL) && (p->matricula != mat)) {
        ant = p;
        p = p->prox;
    }
    //Se encontrou matrícula na lista, atualiza cr
    if (p != NULL) {
        p->cr = cr;
    } else {
        TAluno *novo = aloca(mat, cr);
        if (!ant) {
            tab[h] = novo;
        } else {
            ant->prox = novo;
        }
    }
}

void libera(Hash *tab, int m) {
    int i;
    for (i = 0; i < m; i++)
        if (tab[i]) {
            TAluno *p = tab[i];
            TAluno *q;
            while (p) {
                q = p;
                p = p->prox;
                free(q);
            }
        }
}

/*
 * Imprime a tabela hash: uma linha por compartimento, com a lista de registros (matrícula e cr)
 */
void imprime(Hash *tab, int m) {
    for (int i = 0; i < m; i++) {
        printf("%d: ", i);
        TAluno *p = tab[i];
        while (p != NULL) {
            printf("%d (%.2f) -> ", p->matricula, p->cr);
            p = p->prox;
        }
        printf("NULL\n");
    }
}

/*
 * Imprime a matrícula de um registro examinado durante a exclusão
 * Deve ser chamada uma vez para cada registro examinado, na ordem em que eles são examinados
 */
void imprime_chave(int mat) {
    printf("%d\n", mat);
}

/*
 * Exclui da tabela hash os registros cujas matrículas estão no vetor chaves (que tem qtd_chaves posições)
 * m é o tamanho da tabela
 * As chaves devem ser excluídas na ordem em que aparecem no vetor
 * Chaves que não existem na tabela são ignoradas
 * Cada registro examinado (cuja matrícula é comparada com a chave procurada) deve ser impresso com a função imprime_chave
 * Apenas os registros necessários devem ser examinados: a tabela não deve ser percorrida inteira
 * O espaço de cada registro excluído deve ser liberado com free
 */
void exclui_chaves(Hash *tab, int m, int *chaves, int qtd_chaves) {
    //TODO: Implementar essa funcao
}

int main(void) {
    /* Essa função gera a saída que é usada nos testes. Ela NÃO DEVE SER MODIFICADA */
    int m, n, k, i, mat;
    float cr;

    //Le o tamanho m da tabela hash
    scanf("%d", &m);
    Hash *tab = (Hash *) malloc(m * sizeof(Hash));
    inicializa(tab, m);

    //Le os n registros (matrícula e cr) e os insere na tabela
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d %f", &mat, &cr);
        insere(tab, m, mat, cr);
    }

    //Le as k chaves (matrículas) a serem excluídas
    scanf("%d", &k);
    int *chaves = (int *) malloc((k > 0 ? k : 1) * sizeof(int));
    for (i = 0; i < k; i++) {
        scanf("%d", &chaves[i]);
    }

    printf("TABELA INICIAL:\n");
    imprime(tab, m);

    //Chama função a ser testada
    printf("CHAVES EXAMINADAS:\n");
    exclui_chaves(tab, m, chaves, k);

    printf("TABELA FINAL:\n");
    imprime(tab, m);

    free(chaves);
    libera(tab, m);
    free(tab);
    return 0;
}
