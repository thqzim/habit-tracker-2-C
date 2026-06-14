#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char name[100];
    int streak;
    char complete;
} Habit;


int getIntInput() {
    char input[100];
    char *end;

while (1) {
    printf("Enter your choice");
     if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Input error;\n");
        continue;
     }

    long value = strtol(input, &end, 10);

    if (input == end) {
        printf("Input is invalid/enter numbers\n");
        continue;
    }

    if (*end != '\n' && *end != '\0') {
        printf("Invalid input/too many characters\n");
        continue;
    }

    return (int)value;
    }
}

void loadHabit(Habit habits[], int *habitCount) {

    FILE *file = fopen("habits1.txt", "r");
    if (file == NULL) return;

    char lineStart[200];

    while (fgets(lineStart, sizeof(lineStart), file) !=NULL) {
        char *name = strtok(lineStart, "|");
        char *streakText = strtok(NULL, "|");
        char *completeText = strtok(NULL, "|");

        strcpy(habits[*habitCount].name, name);
        habits[*habitCount].streak = atoi(streakText);
        habits[*habitCount].complete = atoi(completeText);

        (*habitCount)++;
    }
    fclose(file);

}

void saveHabit(Habit habits[], int habitCount) {
    FILE *file = fopen("habits1.txt", "w");

    for (int i = 0; i < habitCount; i++) {
        fprintf(file, "%s|%d|%d\n", habits[i].name, habits[i].streak, habits[i].complete);
    }
    fclose(file);
}

void viewHabit(Habit habits[], int habitCount) {
    for (int i = 0; i < habitCount; i++) {
        printf("%d. %s|Streak: %d|Status: %s\n", i+1, habits[i].name, habits[i].streak, habits[i].complete ? "Complete" : "Not Complete");
    }
}

void addHabit(Habit habits[], int *habitCount) {
    char newHabit[100];

            printf("Enter new habit:");

            fgets(newHabit, sizeof(newHabit), stdin);
            newHabit[strcspn(newHabit, "\n")] = '\0';
            strcpy(habits[*habitCount].name, newHabit);
            habits[*habitCount].streak = 0;
            habits[*habitCount].complete = 0;
            (*habitCount)++;
}

void deleteHabit(Habit habits[], int *habitCount) {
    int deleteCount;

            for (int i = 0; i < *habitCount; i++) {
                printf("%d. %s\n", i+1, habits[i].name);
            }
            printf("Which habit would you like to delete");
            deleteCount = getIntInput();
            deleteCount--;

            for (int i = deleteCount; i < *habitCount - 1; i++) {
                habits[i] = habits[i+1];
            }
            (*habitCount)--;
}

void toggleHabit(Habit habits[], int habitCount) {
     int index;

            printf("Pick which habit whose streak you want to add to:");
            index = getIntInput();
            index--;

            if (habits[index].complete == 0) {
                habits[index].complete = 1;
                habits[index].streak++;
            } else {
                habits[index].complete = 0;
            }
}

int main() {

    Habit habits[10];
    int menu = 0;
    int habitCount = 0;

    loadHabit(habits, &habitCount);

    while (menu !=5) {
        printf("\n1. View\n2. Add\n3. Delete\n4. Toggle\n5. Exit\n");  
        menu = getIntInput();

        if (menu == 1) {
            viewHabit(habits, habitCount);
        }
        
        else if (menu == 2) {
            addHabit(habits, &habitCount);
            saveHabit(habits, habitCount);
        }

        else if (menu == 3) {
            deleteHabit(habits, &habitCount);
            saveHabit(habits, habitCount);
        }

        else if (menu == 4) {
            toggleHabit(habits, habitCount);
            saveHabit(habits, habitCount);

        }
        
    }
    return 0;
}