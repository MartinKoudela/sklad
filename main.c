#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tgmath.h>


struct Decks {
    char name[100];
    char brand[50];
    double price;
    double size;
    char material[50];
    int quantity;
};

struct Decks decks[100] = {
    {"Night Rider", "Jart", 106.50, 8.0, "Maple", 7},
    {"Venom", "Charge", 57.40, 8.25, "Bamboo", 10},
    {"Frostbite", "Polar Skate", 82.00, 8.5, "Maple", 0},
    {"Dark Matter", "Chocolate", 115.80, 8.0, "Maple", 18},
    {"Shadow", "Charge", 55.90, 8.0, "Bamboo", 0},
    {"Inferno", "Baker", 90.65, 8.25, "Epoxy Maple", 5},
};

int deckCount = 6;


int show() {
    printf("\n%-4s %-14s %-12s %8s %6s %-12s %s\n",
           "#", "Name", "Brand", "Price", "Size", "Material", "Quantity");
    printf("--------------------------------------------------------------------------- \n");
    for (int i = 0; i < deckCount; i++) {
        if (decks[i].quantity > 0) {
            printf("%-4d %-14s %-12s %7.2f€ %5.2f %-12s", i + 1, decks[i].name, decks[i].brand, decks[i].price,
                   decks[i].size, decks[i].material);
            (decks[i].quantity == 1) ? printf("%d deck\n", decks[i].quantity) : printf("%d decks\n", decks[i].quantity);
        } else {
            printf("%-4d %-14s %-12s %7.2f€ %5.2f %-12sNo decks in stock \n", i + 1, decks[i].name, decks[i].brand,
                   decks[i].price, decks[i].size, decks[i].material);
        }
    }
    return 0;
}


int searchDeck() {
    char input[100];
    int found = 0;

    printf("\nSearch deck: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';
    double price;
    int isPrice = sscanf(input, "%lf", &price);


    for (int i = 0; i < deckCount; i++) {
        if (isPrice == 1 && fabs(decks[i].price - price) < 0.01) {
            printf("Found: %s - %s\n", decks[i].name, decks[i].brand);
            found = 1;
        } else if (isPrice != 1 && (strcasecmp(decks[i].brand, input) == 0 || strcasecmp(decks[i].name, input) == 0 ||
                                    strcasecmp(decks[i].material, input) == 0)) {
            printf("Found: %s - %s\n", decks[i].name, decks[i].brand);
            found = 1;
        }
    }
    (!found) ? printf("Not any decks found\n") : printf("\n");
    return 0;
}

int showDetails() {
    char input[100];
    int found = 0;

    printf("\nSearch deck: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';
    double price;
    int isPrice = sscanf(input, "%lf", &price);

    for (int i = 0; i < deckCount; i++) {
        if (isPrice == 1 && fabs(decks[i].price - price) < 0.01) {
            printf("Found: %s - %s - %.2f€ - %.2f - %s\n", decks[i].name, decks[i].brand, decks[i].price, decks[i].size,
                   decks[i].material);
            found = 1;
        } else if (isPrice != 1 && (strcasecmp(decks[i].brand, input) == 0 || strcasecmp(decks[i].name, input) == 0 ||
                                    strcasecmp(decks[i].material, input) == 0)) {
            printf("Found: %s - %s - %.2f€ - %.2f - %s\n", decks[i].name, decks[i].brand, decks[i].price, decks[i].size,
                   decks[i].material);
            found = 1;
        }
    }
    (!found) ? printf("Not any decks found\n") : printf("\n");
    return 0;
}

// TODO: opravit
int addDeck() {
    printf("\nEnter new decks information ");
    printf("\n--------------------------- ");

    printf("\nEnter decks name:");
    scanf(" %[^\n]", decks[deckCount].name);

    printf("\nEnter decks brand:");
    scanf(" %[^\n]", decks[deckCount].brand);

    printf("\nEnter decks price:");
    scanf("%lf", &decks[deckCount].price);

    printf("\nEnter decks size (8.5, 8.0 format):");
    scanf("%lf", &decks[deckCount].size);

    printf("\nEnter decks material:");
    scanf(" %[^\n]", decks[deckCount].material);

    printf("\nEnter decks quantity:");
    scanf("%d", &decks[deckCount].quantity);

    deckCount++;
    printf("\nDeck added successfully\n");
    return 0;
}

int destroyDeck() {
    char input[100];
    int found = 0;

    printf("\nSearch the deck you want to delete: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';
    double price;
    int isPrice = sscanf(input, "%lf", &price);


    for (int i = 0; i < deckCount; i++) {
        int match = 0;
        if (isPrice == 1 && fabs(decks[i].price - price) < 0.01) {
            match = 1;
        } else if (isPrice != 1 && (strcasecmp(decks[i].brand, input) == 0 || strcasecmp(decks[i].name, input) == 0 ||
                                    strcasecmp(decks[i].material, input) == 0)) {
            match = 1;
        }
        if (match) {
            printf("\nDeleted: %s - %s\n", decks[i].name, decks[i].brand);
            for (int j = i; j < deckCount - 1; j++) {
                decks[j] = decks[j + 1];
            }
            deckCount--;
            i--;
            found = 1;
        }
    }
    (!found) ? printf("Not any decks found\n") : printf("\n");
    return 0;
}

int updateForm(int index) {
    int choice;
    printf("\n--------------------------------------");
    printf("\n Update decks details");
    printf("\n--------------------------------------");
    printf("\n 1. Update name");
    printf("\n 2. Update brand");
    printf("\n 3. Update price");
    printf("\n 4. Update size");
    printf("\n 5. Update material");
    printf("\n 0. Exit");
    printf("\n");

    printf("\nChoose an action: ");
    char buf[100];
    fgets(buf, sizeof(buf), stdin);
    choice = atoi(buf);


    switch (choice) {
        case 0:
            printf("Bye");
            return 0;
        case 1:
            printf("Set a new name:");
            scanf(" %[^\n]", decks[index].name);
            break;
        case 2:
            printf("Set a new brand:");
            scanf(" %[^\n]", decks[index].brand);
            break;
        case 3:
            printf("Set a new price:");
            scanf("%lf", &decks[index].price);
            break;
        case 4:
            printf("Set a new size:");
            scanf("%lf", &decks[index].size);
            break;
        case 5:
            printf("Set a new material:");
            scanf(" %[^\n]", decks[index].material);
            break;
        default:
            printf("Invalid action");
    }
}


int updateDeck() {
    char input[100];
    int found = 0;

    printf("\nSearch deck: ");
    getchar();
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';
    double price;
    int isPrice = sscanf(input, "%lf", &price);


    for (int i = 0; i < deckCount; i++) {
        if (isPrice == 1 && fabs(decks[i].price - price) < 0.01) {
            printf("Found: %s - %s - %.2f€ - %.2f - %s\n", decks[i].name, decks[i].brand, decks[i].price, decks[i].size,
                   decks[i].material);
            found = 1;
            updateForm(i);
        } else if (isPrice != 1 && (strcasecmp(decks[i].brand, input) == 0 || strcasecmp(decks[i].name, input) == 0 ||
                                    strcasecmp(decks[i].material, input) == 0)) {
            printf("Found: %s - %s - %.2f€ - %.2f - %s\n", decks[i].name, decks[i].brand, decks[i].price, decks[i].size,
                   decks[i].material);
            found = 1;
            updateForm(i);
        }
    }
    (!found) ? printf("Not any decks found\n") : printf("\n");
    return 0;
}

int main(void) {
    int choice;

    while (1) {
        printf("\n--------------------------------------");
        printf("\n Welcome to DeckShops storage menu");
        printf("\n--------------------------------------");
        printf("\n 1. Show all decks");
        printf("\n 2. Search deck");
        printf("\n 3. Search deck with details");
        printf("\n 4. Add new deck ");
        printf("\n 5. Delete a deck");
        printf("\n 6. Update decks info");
        printf("\n 0. Exit");
        printf("\n");

        printf("\nChoose an action: ");
        char buf[100];
        fgets(buf, sizeof(buf), stdin);
        choice = atoi(buf);

        switch (choice) {
            case 0:
                printf("Bye");
                return 0;
            case 1:
                show();
                break;
            case 2:
                searchDeck();
                break;
            case 3:
                showDetails();
                break;
            case 4:
                addDeck();
                break;
            case 5:
                destroyDeck();
                break;
            case 6:
                updateDeck();
                break;
            default:
                printf("Invalid action");
        }
    }
    return 0;
}
