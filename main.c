#include <stdio.h>
#include <string.h>
#include <tgmath.h>


struct Decks {
    char name[100];
    double price;
    int quantity;
};

struct Decks decks[] = {
    {"Jart", 106.5, 7},
    {"Charge", 57.4, 1},
    {"Polar Skate", 82, 0},
    {"Chocolate", 115.8, 2},
    {"Charge", 55.9, 4},
    {"Baker", 90.65, 5},
};

int show() {
    printf("\n      Name  Price  Quantity\n");
    const int count = sizeof(decks) / sizeof(decks[0]);
    for (int i = 0; i < count; i++) {
        if (decks[i].quantity > 0) {
            printf("%d. - %s - %.2f€ - ", i + 1, decks[i].name, decks[i].price);
            (decks[i].quantity == 1) ? printf("%d deck\n", decks[i].quantity) : printf("%d decks\n", decks[i].quantity);
        } else {
            printf("%d. - %s - %.2f€ - No decks on stock \n", i + 1, decks[i].name, decks[i].price);
        }
    }
    return 0;
}


int searchName() {
    char name[100];

    printf("\nSearch name: ");
    scanf("%s", name);
    const int count = sizeof(decks) / sizeof(decks[0]);
    for (int i = 0; i < count; i++) {
        if (strcasecmp(decks[i].name, name) == 0) {
            printf("Deck found: %s\n", decks[i].name);
            return 0;
        }
    }
    printf("Not Found\n");
    return 0;
}

int searchPrice() {
    double price;

    printf("\nSearch price: ");
    scanf("%lf", &price);
    const int count = sizeof(decks) / sizeof(decks[0]);
    for (int i = 0; i < count; i++) {
        if (fabs(decks[i].price - price) < 0.01) {
            printf("Deck found: %s\n", decks[i].name);
            return 0;
        }
    }
    printf("Not Found\n");
    return 0;
}

int searchType() {
    int searchType;
    printf("\n1. Name ");
    printf("\n2. Price ");
    printf("\n");
    printf("\nSearch by: ");
    scanf("%d", &searchType);

    switch (searchType) {
        case 1:
            searchName();
            break;
        case 2:
            searchPrice();
            break;
        default:
            printf("Invalid action");
            break;
    }

    return 0;
}

int showDetails() {
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
        printf(" ####################################");
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
                searchType();
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
