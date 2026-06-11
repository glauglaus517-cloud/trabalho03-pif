#include <stdio.h>
#include <string.h>

#define MAX_NOME 50
#define ARQUIVO "clientes.dat"

struct Cliente {
    int conta;
    char nome[MAX_NOME];
    float saldo;
};

void cadastrar() {
    struct Cliente c;
    int posicao;
    FILE *arq;

    printf("Posicao (0, 1, 2, ...): ");
    scanf("%d", &posicao);
    printf("Numero da conta: ");
    scanf("%d", &c.conta);
    printf("Nome: ");
    scanf(" %[^\n]", c.nome);
    printf("Saldo inicial: ");
    scanf("%f", &c.saldo);

    arq = fopen(ARQUIVO, "r+b");
    if (arq == NULL) {
        arq = fopen(ARQUIVO, "w+b");
    }

    fseek(arq, posicao * sizeof(struct Cliente), SEEK_SET);
    fwrite(&c, sizeof(struct Cliente), 1, arq);
    fclose(arq);

    printf("Cliente cadastrado com sucesso!\n");
}

void consultar() {
    struct Cliente c;
    int conta;
    FILE *arq;

    printf("Numero da conta: ");
    scanf("%d", &conta);

    arq = fopen(ARQUIVO, "rb");
    if (arq == NULL) {
        printf("Arquivo nao encontrado.\n");
        return;
    }

    while (fread(&c, sizeof(struct Cliente), 1, arq) == 1) {
        if (c.conta == conta) {
            printf("Conta: %d\n", c.conta);
            printf("Nome: %s\n", c.nome);
            printf("Saldo: R$ %.2f\n", c.saldo);
            fclose(arq);
            return;
        }
    }

    printf("Cliente nao encontrado.\n");
    fclose(arq);
}

void atualizar() {
    struct Cliente c;
    int conta;
    int posicao = 0;
    FILE *arq;

    printf("Numero da conta para atualizar: ");
    scanf("%d", &conta);

    arq = fopen(ARQUIVO, "r+b");
    if (arq == NULL) {
        printf("Arquivo nao encontrado.\n");
        return;
    }

    while (fread(&c, sizeof(struct Cliente), 1, arq) == 1) {
        if (c.conta == conta) {
            printf("Saldo atual: R$ %.2f\n", c.saldo);
            printf("Novo saldo: ");
            scanf("%f", &c.saldo);

            fseek(arq, posicao * sizeof(struct Cliente), SEEK_SET);
            fwrite(&c, sizeof(struct Cliente), 1, arq);
            fclose(arq);

            printf("Saldo atualizado!\n");
            return;
        }
        posicao++;
    }

    printf("Cliente nao encontrado.\n");
    fclose(arq);
}

void encerrar() {
    struct Cliente c;
    int conta;
    int posicao = 0;
    FILE *arq;

    printf("Numero da conta para encerrar: ");
    scanf("%d", &conta);

    arq = fopen(ARQUIVO, "r+b");
    if (arq == NULL) {
        printf("Arquivo nao encontrado.\n");
        return;
    }

    while (fread(&c, sizeof(struct Cliente), 1, arq) == 1) {
        if (c.conta == conta) {
            struct Cliente vazio;
            vazio.conta = -1;
            strcpy(vazio.nome, "--- ENCERRADO ---");
            vazio.saldo = 0;

            fseek(arq, posicao * sizeof(struct Cliente), SEEK_SET);
            fwrite(&vazio, sizeof(struct Cliente), 1, arq);
            fclose(arq);

            printf("Conta encerrada!\n");
            return;
        }
        posicao++;
    }

    printf("Cliente nao encontrado.\n");
    fclose(arq);
}

void listar() {
    struct Cliente c;
    FILE *arq;
    int posicao = 0;

    arq = fopen(ARQUIVO, "rb");
    if (arq == NULL) {
        printf("Arquivo vazio ou nao encontrado.\n");
        return;
    }

    printf("\n--- LISTA DE CLIENTES ---\n");
    while (fread(&c, sizeof(struct Cliente), 1, arq) == 1) {
        if (c.conta != -1) {
            printf("Posicao %d | Conta: %d | Nome: %s | Saldo: R$ %.2f\n",
                posicao, c.conta, c.nome, c.saldo);
        }
        posicao++;
    }

    fclose(arq);
}

void restaurar() {
    struct Cliente c;
    FILE *arq;

    arq = fopen(ARQUIVO, "rb");
    if (arq == NULL) {
        printf("Arquivo nao encontrado.\n");
        return;
    }

    printf("Lendo arquivo do inicio com rewind()...\n");
    rewind(arq);

    printf("\n--- REGISTROS APOS REWIND ---\n");
    while (fread(&c, sizeof(struct Cliente), 1, arq) == 1) {
        if (c.conta != -1) {
            printf("Conta: %d | Nome: %s | Saldo: R$ %.2f\n",
                c.conta, c.nome, c.saldo);
        }
    }

    fclose(arq);
}

int main() {
    int opcao;

    do {
        printf("\n===== BANCO DE DADOS =====\n");
        printf("1. Cadastrar cliente\n");
        printf("2. Consultar cliente\n");
        printf("3. Atualizar saldo\n");
        printf("4. Encerrar conta\n");
        printf("5. Listar clientes\n");
        printf("6. Restaurar leitura (rewind)\n");
        printf("7. Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: cadastrar();  break;
            case 2: consultar();  break;
            case 3: atualizar();  break;
            case 4: encerrar();   break;
            case 5: listar();     break;
            case 6: restaurar();  break;
            case 7: printf("Encerrando...\n"); break;
            default: printf("Opcao invalida!\n");
        }

    } while (opcao != 7);

    return 0;
}
