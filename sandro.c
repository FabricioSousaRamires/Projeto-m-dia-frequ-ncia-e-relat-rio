#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LENGTH 50
#define REQUIRED_ATTENDANCE 75
#define PASSING_GRADE 7.0

// Códigos ANSI para cores
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define RESET   "\x1b[0m"

// Estrutura para representar um aluno
typedef struct {
    char name[NAME_LENGTH];
    float grades[3];
    int attendance;
    float finalAverage;
    char status[20];
} Student;

// Função para calcular a média final (considerando as 2 maiores notas)
float calculateFinalAverage(float grades[]) {
    float max1 = grades[0], max2 = grades[1];

    // Identifica as duas maiores notas
    if (grades[1] > grades[0]) {
        max1 = grades[1];
        max2 = grades[0];
    }
    if (grades[2] > max1) {
        max2 = max1;
        max1 = grades[2];
    } else if (grades[2] > max2) {
        max2 = grades[2];
    }

    // Retorna a média das duas maiores notas
    return (max1 + max2) / 2.0;
}

// Função para determinar a situação do aluno (aprovado ou reprovado)
void determineStatus(Student *student) {
    if (student->finalAverage >= PASSING_GRADE && student->attendance >= REQUIRED_ATTENDANCE) {
        strcpy(student->status, "Aprovado");
    } else {
        strcpy(student->status, "Reprovado");
    }
}

// Função para exibir o relatório dos alunos
void printReport(Student students[], int count) {
    printf("\nrelatorio final:\n");
    printf("%-30s %-10s %-15s\n", "nome", "media final", "situacao");
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].status, "Aprovado") == 0) {
            printf("%-30s %-10.2f %-15s\n", students[i].name, students[i].finalAverage, GREEN "Aprovado" RESET);
        } else {
            printf("%-30s %-10.2f %-15s\n", students[i].name, students[i].finalAverage, RED "Reprovado" RESET);
        }
    }
}

// Função principal
int main() {
    Student students[MAX_STUDENTS];
    int studentCount;

    // Pergunta a quantidade de alunos
    printf("\n====================================\n");
    printf("Cadastro de Alunos - Sistema Escolar\n");
    printf("====================================\n");
    printf("Quantos alunos serao cadastrados? ");
    scanf("%d", &studentCount);

    // Limpeza do buffer de entrada após o scanf
    getchar();  // Essa linha garante que a nova linha (\n) seja consumida após o scanf de um inteiro

    // Verifica se o número de alunos está dentro do limite
    if (studentCount <= 0 || studentCount > MAX_STUDENTS) {
        printf(RED "Número inválido de alunos! Encerrando o programa.\n" RESET);
        return 1;
    }

    // Entrada de dados dos alunos
    for (int i = 0; i < studentCount; i++) {
        printf("\nAluno %d:\n", i + 1);

        // Lê o nome do aluno com fgets para permitir espaços
        printf("Nome: ");
        fgets(students[i].name, NAME_LENGTH, stdin);
        students[i].name[strcspn(students[i].name, "\n")] = 0;  // Remove a nova linha do final do nome

        // Lê as notas do aluno
        printf("Nota 1: ");
        scanf("%f", &students[i].grades[0]);
        printf("Nota 2: ");
        scanf("%f", &students[i].grades[1]);
        printf("Nota 3: ");
        scanf("%f", &students[i].grades[2]);

        // Lê a frequência do aluno
        printf("Frequência (em %%): ");
        scanf("%d", &students[i].attendance);

        // Limpeza do buffer de entrada
        getchar();  // Consumir qualquer nova linha extra

        // Calcula a média final e determina a situação
        students[i].finalAverage = calculateFinalAverage(students[i].grades);
        determineStatus(&students[i]);
    }

    // Gera o relatório final
    printReport(students, studentCount);

    // Pausa para o usuário ver a saída
    printf("\nPressione qualquer tecla para sair...");
    getchar();  // Espera o usuário pressionar uma tecla antes de finalizar

    return 0;
}