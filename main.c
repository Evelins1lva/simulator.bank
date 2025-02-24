#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h> // Biblioteca para configurar o idioma

#define MAX_CONTAS 10

typedef struct {
    int numero;
    char titular[50];
    float saldo;
} Conta;

Conta contas[MAX_CONTAS];
int totalContas = 0;

void criarConta() {
    if (totalContas >= MAX_CONTAS) {
        printf("Número máximo de contas atingido.\n");
        return;
    }
    
    Conta novaConta;
    novaConta.numero = totalContas + 1;
    printf("Nome do titular: ");
    scanf(" %[^\n]", novaConta.titular);
    novaConta.saldo = 0.0;

    contas[totalContas] = novaConta;
    totalContas++;
    
    printf("Conta criada com sucesso! Número da conta: %d\n", novaConta.numero);
}

void consultarSaldo() {
    int numero;
    printf("Número da conta: ");
    scanf("%d", &numero);

    for (int i = 0; i < totalContas; i++) {
        if (contas[i].numero == numero) {
            printf("Titular: %s\nSaldo: R$%.2f\n", contas[i].titular, contas[i].saldo);
            return;
        }
    }
    printf("Conta não encontrada!\n");
}

void depositar() {
    int numero;
    float valor;
    printf("Número da conta: ");
    scanf("%d", &numero);
    printf("Valor do depósito: R$");
    scanf("%f", &valor);

    for (int i = 0; i < totalContas; i++) {
        if (contas[i].numero == numero) {
            contas[i].saldo += valor;
            printf("Depósito realizado! Novo saldo: R$%.2f\n", contas[i].saldo);
            return;
        }
    }
    printf("Conta não encontrada!\n");
}

void sacar() {
    int numero;
    float valor;
    printf("Número da conta: ");
    scanf("%d", &numero);
    printf("Valor do saque: R$");
    scanf("%f", &valor);

    for (int i = 0; i < totalContas; i++) {
        if (contas[i].numero == numero) {
            if (contas[i].saldo >= valor) {
                contas[i].saldo -= valor;
                printf("Saque realizado! Novo saldo: R$%.2f\n", contas[i].saldo);
            } else {
                printf("Saldo insuficiente!\n");
            }
            return;
        }
    }
    printf("Conta não encontrada!\n");
}

void transferir() {
    int origem, destino;
    float valor;
    printf("Número da conta de origem: ");
    scanf("%d", &origem);
    printf("Número da conta de destino: ");
    scanf("%d", &destino);
    printf("Valor da transferência: R$");
    scanf("%f", &valor);

    Conta *contaOrigem = NULL, *contaDestino = NULL;

    for (int i = 0; i < totalContas; i++) {
        if (contas[i].numero == origem) contaOrigem = &contas[i];
        if (contas[i].numero == destino) contaDestino = &contas[i];
    }

    if (contaOrigem == NULL || contaDestino == NULL) {
        printf("Conta(s) não encontrada(s)!\n");
        return;
    }

    if (contaOrigem->saldo >= valor) {
        contaOrigem->saldo -= valor;
        contaDestino->saldo += valor;
        printf("Transferência realizada com sucesso!\n");
    } else {
        printf("Saldo insuficiente para transferência!\n");
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese_Brazil"); // Configura o idioma para exibição correta

    int opcao;

    do {
        printf("\n=== Simulador de Banco ===\n");
        printf("1. Criar conta\n");
        printf("2. Consultar saldo\n");
        printf("3. Depositar\n");
        printf("4. Sacar\n");
        printf("5. Transferir\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: criarConta(); break;
            case 2: consultarSaldo(); break;
            case 3: depositar(); break;
            case 4: sacar(); break;
            case 5: transferir(); break;
            case 6: printf("Encerrando o programa...\n"); break;
            default: printf("Opção inválida!\n");
        }
    } while (opcao != 6);

    return 0;
}