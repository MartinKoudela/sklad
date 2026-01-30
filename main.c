#include <stdio.h>
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

struct Decks decks[] = {
    {"Night Rider", "Jart", 106.50, 8.0, "Maple", 7},
    {"Venom", "Charge", 57.40, 8.25, "Bamboo", 10},
    {"Frostbite", "Polar Skate", 82.00, 8.5, "Maple", 0},
    {"Dark Matter", "Chocolate", 115.80, 8.0, "Maple", 18},
    {"Shadow", "Charge", 55.90, 8.0, "Bamboo", 0},
    {"Inferno", "Baker", 90.65, 8.25, "Epoxy Maple", 5},
};

int show() {
    printf("\n%-4s %-14s %-12s %8s %6s %-12s %s\n",
           "#", "Name", "Brand", "Price", "Size", "Material", "Quantity");
    printf("--------------------------------------------------------------------------- \n");
    const int count = sizeof(decks) / sizeof(decks[0]);
    for (int i = 0; i < count; i++) {
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


// TODO: fix return printf message for searchDeck
// TODO: next functions

int searchDeck() {
    char input[100];
    int found = 0;

    printf("\nSearch deck: ");
    scanf("%s", input);

    double price;
    int isPrice = sscanf(input, "%lf", &price);

    const int count = sizeof(decks) / sizeof(decks[0]);

    for (int i = 0; i < count; i++) {
        if (isPrice == 1 && fabs(decks[i].price - price) < 0.01) {
            printf("Found: %s - %s - %.2f€ - %.2f - %s\n", decks[i].name, decks[i].brand, decks[i].price, decks[i].size, decks[i].material);
            found = 1;
        } else if (isPrice != 1 && (strcasecmp(decks[i].brand, input) == 0 || strcasecmp(decks[i].name, input) == 0 || strcasecmp(decks[i].material, input) == 0)) {
            printf("Found: %s - %s - %.2f€ - %.2f - %s\n ", decks[i].name, decks[i].brand, decks[i].price, decks[i].size, decks[i].material);
            found = 1;
        }
    }
    (!found) ? printf("Not any decks found\n") : printf("\n");
    return 0;
}

int showDetails() {
    searchDeck();
    return 0;
}

int addDeck() {
    return 0;
}

int destroyDeck() {
    return 0;
}

int updateDeck() {
    return 0;
}

int main(void) {
    int choice;

    while (1) {
        printf("\n####################################");
        printf("\n Welcome to DeckShops storage menu");
        printf("\n####################################");
        printf("\n 1. Show all decks");
        printf("\n 2. Search deck");
        printf("\n 3. Show details of deck");
        printf("\n 4. Add new deck ");
        printf("\n 5. Delete a deck");
        printf("\n 6. Update decks info");
        printf("\n 0. Exit");
        printf("\n");

        printf("\nChoose an action: ");
        scanf("%d", &choice);

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
