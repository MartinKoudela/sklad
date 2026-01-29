#include <stdio.h>


struct product {
    char name[100];
    float price;
    int quantity;
    int inStock;
};

int show() {
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

int destroyProduct() {
    return 0;
}

int updateProduct() {
    return 0;
}

int main(void) {
    int choice;

    printf("#########################");
    printf("\n     Choose action       ");
    printf("\n#########################");
    printf("\n 1. Show all products");
    printf("\n 2. Search product by name");
    printf("\n 3. Search product by price");
    printf("\n 4. Show details of product");
    printf("\n 5. Delete a product");
    printf("\n 6. Update products info");
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
            destroyProduct();
            break;
        case 6:
            updateProduct();
            break;
        default:
            printf("Neplatna akce");
    }
    return 0;
}