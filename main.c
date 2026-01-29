#include <stdio.h>


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
    for (int i = 0; i < 6; i++) {
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
    return 0;
}

int searchPrice() {
    return 0;
}

int showDetails() {
    return 0;
}

int destroyDecks() {
    return 0;
}

int updateDeck() {
    return 0;
}

int main(void) {
    int choice;

    printf("####################################");
    printf("\n Welcome to DeckShops storage menu");
    printf("\n ####################################");
    printf("\n 1. Show all decks");
    printf("\n 2. Search deck by name");
    printf("\n 3. Search deck by price");
    printf("\n 4. Show details of deck");
    printf("\n 5. Delete a deck");
    printf("\n 6. Update decks info");
    printf("\n");

    printf("\nChoose an action: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            show();
            break;
        case 2:
            searchName();
            break;
        case 3:
            searchPrice();
            break;
        case 4:
            showDetails();
            break;
        case 5:
            destroyDecks();
            break;
        case 6:
            updateDeck();
            break;
        default:
            printf("Invalid action");
    }
    return 0;
}
