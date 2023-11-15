#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_USERS 1000

struct Usuario {
    int id;
    char nome[50];
    char email[50];
    char sexo[15];
    char endereco[100];
    double altura;
    int vacina;
};

int gerarId() {
    return rand() % 100000 + 1;
}

int validarEmail(const char *email) {
    const char *at = strchr(email, '@');
    return at && strchr(at, '.');
}

int validarSexo(const char *sexo) {
    return strcmp(sexo, "Feminino") == 0 || strcmp(sexo, "Masculino") == 0 || strcmp(sexo, "Indiferente") == 0;
}

int validarAltura(double altura) {
    return altura >= 1.0 && altura <= 2.0;
}

void adicionarUsuario(struct Usuario usuarios[], int *numUsuarios) {
    if (*numUsuarios < MAX_USERS) {
        struct Usuario novoUsuario;
        novoUsuario.id = gerarId();

        printf("Nome completo: ");
        scanf(" %[^\n]s", novoUsuario.nome);

        printf("Email: ");
        scanf("%s", novoUsuario.email);
        while (!validarEmail(novoUsuario.email)) {
            printf("Email inválido. Digite novamente: ");
            scanf("%s", novoUsuario.email);
        }

        printf("Sexo (Feminino/Masculino/Indiferente): ");
        scanf("%s", novoUsuario.sexo);
        while (!validarSexo(novoUsuario.sexo)) {
            printf("Sexo inválido. Digite novamente: ");
            scanf("%s", novoUsuario.sexo);
        }

        printf("Endereço: ");
        scanf(" %[^\n]s", novoUsuario.endereco);

        printf("Altura (entre 1.0 e 2.0): ");
        scanf("%lf", &novoUsuario.altura);
        while (!validarAltura(novoUsuario.altura)) {
            printf("Altura inválida. Digite novamente: ");
            scanf("%lf", &novoUsuario.altura);
        }

        printf("Vacina (1 para sim, 0 para não): ");
        scanf("%d", &novoUsuario.vacina);

        usuarios[*numUsuarios] = novoUsuario;
        (*numUsuarios)++;
        printf("Usuário adicionado com sucesso!\n");
    } else {
        printf("Limite de usuários atingido.\n");
    }
}

void editarUsuario(struct Usuario usuarios[], int numUsuarios) {
    int id;
    printf("Digite o ID do usuário a ser editado: ");
    scanf("%d", &id);

    int encontrado = 0;
    for (int i = 0; i < numUsuarios; i++) {
        if (usuarios[i].id == id) {
            printf("Novo nome completo: ");
            scanf(" %[^\n]s", usuarios[i].nome);

            printf("Novo email: ");
            scanf("%s", usuarios[i].email);
            while (!validarEmail(usuarios[i].email)) {
                printf("Email inválido. Digite novamente: ");
                scanf("%s", usuarios[i].email);
            }

            printf("Novo sexo (Feminino/Masculino/Indiferente): ");
            scanf("%s", usuarios[i].sexo);
            while (!validarSexo(usuarios[i].sexo)) {
                printf("Sexo inválido. Digite novamente: ");
                scanf("%s", usuarios[i].sexo);
            }

            printf("Novo endereço: ");
            scanf(" %[^\n]s", usuarios[i].endereco);

            printf("Nova altura (entre 1.0 e 2.0): ");
            scanf("%lf", &usuarios[i].altura);
            while (!validarAltura(usuarios[i].altura)) {
                printf("Altura inválida. Digite novamente: ");
                scanf("%lf", &usuarios[i].altura);
            }

            printf("Nova vacina (1 para sim, 0 para não): ");
            scanf("%d", &usuarios[i].vacina);

            printf("Usuário editado com sucesso!\n");
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Usuário não encontrado.\n");
    }
}

void excluirUsuario(struct Usuario usuarios[], int *numUsuarios) {
    int id;
    printf("Digite o ID do usuário a ser excluído: ");
    scanf("%d", &id);

    int encontrado = 0;
    for (int i = 0; i < *numUsuarios; i++) {
        if (usuarios[i].id == id) {
            for (int j = i; j < *numUsuarios - 1; j++) {
                usuarios[j] = usuarios[j + 1];
            }
            (*numUsuarios)--;
            printf("Usuário excluído com sucesso!\n");
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Usuário não encontrado.\n");
    }
}

void buscarUsuarioPorEmail(struct Usuario usuarios[], int numUsuarios) {
    char email[50];
    printf("Digite o email do usuário a ser buscado: ");
    scanf("%s", email);

    int encontrado = 0;
    for (int i = 0; i < numUsuarios; i++) {
        if (strcmp(usuarios[i].email, email) == 0) {
            printf("ID: %d\n", usuarios[i].id);
            printf("Nome: %s\n", usuarios[i].nome);
            printf("Email: %s\n", usuarios[i].email);
            printf("Sexo: %s\n", usuarios[i].sexo);
            printf("Endereço: %s\n", usuarios[i].endereco);
            printf("Altura: %.2lf\n", usuarios[i].altura);
            printf("Vacina: %s\n", usuarios[i].vacina ? "Sim" : "Não");
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Usuário não encontrado.\n");
    }
}

void imprimirUsuarios(struct Usuario usuarios[], int numUsuarios) {
    if (numUsuarios == 0) {
        printf("Nenhum usuário cadastrado.\n");
    } else {
        printf("Lista de usuários:\n");
        for (int i = 0; i < numUsuarios; i++) {
            printf("ID: %d\n", usuarios[i].id);
            printf("Nome: %s\n", usuarios[i].nome);
            printf("Email: %s\n", usuarios[i].email);
            printf("Sexo: %s\n", usuarios[i].sexo);
            printf("Endereço: %s\n", usuarios[i].endereco);
            printf("Altura: %.2lf\n", usuarios[i].altura);
            printf("Vacina: %s\n", usuarios[i].vacina ? "Sim" : "Não");
        }
    }
}

int main() {
    srand(time(NULL)); // Inicializa a semente para a função rand()

    struct Usuario usuarios[MAX_USERS];
    int numUsuarios = 0;
    char opcao;

    do {
        printf("\nOpções:\n");
        printf("1. Adicionar usuário\n");
        printf("2. Editar usuário\n");
        printf("3. Excluir usuário\n");
        printf("4. Buscar usuário por email\n");
        printf("5. Imprimir todos os usuários\n");
        printf("0. Sair\n");

        printf("Escolha uma opção: ");
        scanf(" %c", &opcao);

        switch (opcao) {
            case '1':
                adicionarUsuario(usuarios, &numUsuarios);
                break;
            case '2':
                editarUsuario(usuarios, numUsuarios);
                break;
            case '3':
                excluirUsuario(usuarios, &numUsuarios);
                break;
            case '4':
                buscarUsuarioPorEmail(usuarios, numUsuarios);
                break;
            case '5':
                imprimirUsuarios(usuarios, numUsuarios);
                break;
            case '0':
                printf("Saindo do programa.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != '0');

    return 0;
}
