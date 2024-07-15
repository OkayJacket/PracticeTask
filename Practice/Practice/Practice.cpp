#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Структура для зберігання даних про метод управління
typedef struct {
    char name[50];
    double initialEfficiency;
    double currentEfficiency;
} ManagementMethod;

// Структура для зберігання даних про технічну систему
typedef struct {
    char name[50];
    ManagementMethod methods[10];
    int methodCount;
    int yearsInUse;
} TechnicalSystem;

// Функція для збору даних про метод управління
void collectManagementMethod(ManagementMethod* method) {
    printf("Enter management method name: ");
    scanf("%s", method->name);
    printf("Enter initial efficiency: ");
    scanf("%lf", &method->initialEfficiency);
    printf("Enter current efficiency: ");
    scanf("%lf", &method->currentEfficiency);
}

// Функція для збору даних про технічну систему
void collectTechnicalSystem(TechnicalSystem* system) {
    printf("Enter system name: ");
    scanf("%s", system->name);
    printf("Enter number of management methods: ");
    scanf("%d", &system->methodCount);

    for (int i = 0; i < system->methodCount; i++) {
        printf("\nCollecting data for method %d:\n", i + 1);
        collectManagementMethod(&system->methods[i]);
    }

    printf("Enter years in use: ");
    scanf("%d", &system->yearsInUse);
}

// Функція для аналізу даних про технічну систему
void analyzeSystem(TechnicalSystem* system) {
    double totalInitialEfficiency = 0;
    double totalCurrentEfficiency = 0;

    for (int i = 0; i < system->methodCount; i++) {
        totalInitialEfficiency += system->methods[i].initialEfficiency;
        totalCurrentEfficiency += system->methods[i].currentEfficiency;
    }

    double averageInitialEfficiency = totalInitialEfficiency / system->methodCount;
    double averageCurrentEfficiency = totalCurrentEfficiency / system->methodCount;
    double efficiencyImprovement = ((averageCurrentEfficiency - averageInitialEfficiency) / averageInitialEfficiency) * 100;

    printf("\n--- Analysis for %s ---\n", system->name);
    printf("Average initial efficiency: %.2f\n", averageInitialEfficiency);
    printf("Average current efficiency: %.2f\n", averageCurrentEfficiency);
    printf("Efficiency improvement: %.2f%%\n", efficiencyImprovement);
    printf("Years in use: %d\n", system->yearsInUse);

    // Рекомендації на основі аналізу
    if (efficiencyImprovement < 20.0) {
        printf("Recommendation: Consider adopting newer management methods.\n");
    }
    else {
        printf("Recommendation: Current management methods are effective.\n");
    }
}

// Функція для аналізу всіх технічних систем
void analyzeAllSystems(TechnicalSystem* systems, int size) {
    for (int i = 0; i < size; i++) {
        analyzeSystem(&systems[i]);
    }
}

// Функція для візуалізації даних про технічні системи
void visualizeData(TechnicalSystem* systems, int size) {
    for (int i = 0; i < size; i++) {
        printf("\nVisualization for %s:\n", systems[i].name);
        for (int j = 0; j < systems[i].methodCount; j++) {
            int initialStars = (int)(systems[i].methods[j].initialEfficiency / 10);
            int currentStars = (int)(systems[i].methods[j].currentEfficiency / 10);
            printf("%s: Initial [", systems[i].methods[j].name);
            for (int k = 0; k < initialStars; k++) printf("*");
            for (int k = initialStars; k < 10; k++) printf(" ");
            printf("] Current [");
            for (int k = 0; k < currentStars; k++) printf("*");
            for (int k = currentStars; k < 10; k++) printf(" ");
            printf("]\n");
        }
    }
}

// Функція для генерації звіту
void generateReport(TechnicalSystem* systems, int size) {
    FILE* report = fopen("report.txt", "w");
    if (report == NULL) {
        printf("Error creating report file!\n");
        return;
    }

    fprintf(report, "Technical Systems Evolution Report\n");
    fprintf(report, "=================================\n");

    for (int i = 0; i < size; i++) {
        fprintf(report, "\n--- %s ---\n", systems[i].name);
        for (int j = 0; j < systems[i].methodCount; j++) {
            fprintf(report, "%s: Initial Efficiency = %.2f, Current Efficiency = %.2f\n",
                systems[i].methods[j].name,
                systems[i].methods[j].initialEfficiency,
                systems[i].methods[j].currentEfficiency);
        }

        double totalInitialEfficiency = 0;
        double totalCurrentEfficiency = 0;
        for (int j = 0; j < systems[i].methodCount; j++) {
            totalInitialEfficiency += systems[i].methods[j].initialEfficiency;
            totalCurrentEfficiency += systems[i].methods[j].currentEfficiency;
        }

        double averageInitialEfficiency = totalInitialEfficiency / systems[i].methodCount;
        double averageCurrentEfficiency = totalCurrentEfficiency / systems[i].methodCount;
        double efficiencyImprovement = ((averageCurrentEfficiency - averageInitialEfficiency) / averageInitialEfficiency) * 100;

        fprintf(report, "Average Initial Efficiency: %.2f\n", averageInitialEfficiency);
        fprintf(report, "Average Current Efficiency: %.2f\n", averageCurrentEfficiency);
        fprintf(report, "Efficiency Improvement: %.2f%%\n", efficiencyImprovement);
        fprintf(report, "Years in Use: %d\n", systems[i].yearsInUse);
        if (efficiencyImprovement < 20.0) {
            fprintf(report, "Recommendation: Consider adopting newer management methods.\n");
        }
        else {
            fprintf(report, "Recommendation: Current management methods are effective.\n");
        }
    }

    fclose(report);
    printf("Report generated successfully!\n");
}

// Основна функція програми
int main() {
    int numSystems;

    printf("Enter the number of technical systems to analyze: ");
    scanf("%d", &numSystems);

    TechnicalSystem systems[numSystems];

    // Збір даних про кожну технічну систему
    for (int i = 0; i < numSystems; i++) {
        printf("\nCollecting data for system %d:\n", i + 1);
        collectTechnicalSystem(&systems[i]);
    }

    // Аналіз зібраних даних
    analyzeAllSystems(systems, numSystems);

    // Візуалізація даних
    visualizeData(systems, numSystems);

    // Генерація звіту
    generateReport(systems, numSystems);

    return 0;
}
