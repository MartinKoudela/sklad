#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define CYAN    "\033[1;36m"
#define RESET   "\033[0m"
#define CSV_FILE "sklad.csv"

struct Product {
    char name[100];
    char ean[14];
    double purchasePrice;
    double sellingPrice;
    int quantity;
    int vatLevel;
};

struct Product *products = NULL;
int productCount = 0;
int productCapacity = 0;

void addProduct(struct Product p) {
    if (productCount >= productCapacity) {
        productCapacity = (productCapacity == 0) ? 4 : productCapacity * 2;
        products = realloc(products, productCapacity * sizeof(struct Product));
    }
    products[productCount++] = p;
}

void saveCSV() {
    FILE *f = fopen(CSV_FILE, "w");
    if (!f) {
        printf(RED "Failed to save file" RESET "\n");
        return;
    }
    for (int i = 0; i < productCount; i++) {
        fprintf(f, "%s;%s;%.2f;%.2f;%d;%d\n",
                products[i].name, products[i].ean,
                products[i].purchasePrice, products[i].sellingPrice,
                products[i].quantity, products[i].vatLevel);
    }
    fclose(f);
}

void loadCSV() {
    FILE *f = fopen(CSV_FILE, "r");
    if (!f) return;

    char line[256];
    while (fgets(line, sizeof(line), f)) {
        line[strcspn(line, "\n")] = '\0';
        struct Product p;
        if (sscanf(line, "%99[^;];%13[^;];%lf;%lf;%d;%d",
                   p.name, p.ean, &p.purchasePrice, &p.sellingPrice,
                   &p.quantity, &p.vatLevel) == 6) {
            addProduct(p);
        }
    }
    fclose(f);
}

int show() {
    if (productCount == 0) {
        printf(YELLOW "\nNo products in stock\n" RESET);
        return 0;
    }
    printf("\n" CYAN "%-4s %-20s %-14s %10s %10s %6s %5s" RESET "\n",
           "#", "Name", "EAN", "Buy price", "Sell price", "Qty", "VAT");
    printf(CYAN "------------------------------------------------------------------------" RESET "\n");
    for (int i = 0; i < productCount; i++) {
        printf("%-4d %-20s %-14s %9.2f€ %9.2f€ %6d %4d%%\n",
               i + 1, products[i].name, products[i].ean,
               products[i].purchasePrice, products[i].sellingPrice,
               products[i].quantity, products[i].vatLevel);
    }
    return 0;
}

int showWithVAT() {
    if (productCount == 0) {
        printf(YELLOW "\nNo products in stock\n" RESET);
        return 0;
    }
    printf("\n" CYAN "%-4s %-20s %-14s %10s %10s %12s %6s" RESET "\n",
           "#", "Name", "EAN", "Buy price", "Sell price", "With VAT", "Qty");
    printf(CYAN "------------------------------------------------------------------------------------" RESET "\n");
    for (int i = 0; i < productCount; i++) {
        double priceWithVAT = products[i].sellingPrice * (1 + products[i].vatLevel / 100.0);
        printf("%-4d %-20s %-14s %9.2f€ %9.2f€ %11.2f€ %6d\n",
               i + 1, products[i].name, products[i].ean,
               products[i].purchasePrice, products[i].sellingPrice,
               priceWithVAT, products[i].quantity);
    }
    return 0;
}

int searchProduct() {
    char input[100];
    int found = 0;

    printf("\nSearch product (name or price): ");
    getchar();
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    double price;
    int isPrice = sscanf(input, "%lf", &price);

    for (int i = 0; i < productCount; i++) {
        if (isPrice == 1 && products[i].sellingPrice >= price - 0.01 && products[i].sellingPrice <= price + 0.01) {
            double priceWithVAT = products[i].sellingPrice * (1 + products[i].vatLevel / 100.0);
            printf(GREEN "\nFound: %s | EAN: %s | %.2f€ (%.2f€ with VAT) | %d pcs" RESET "\n",
                   products[i].name, products[i].ean, products[i].sellingPrice, priceWithVAT, products[i].quantity);
            found = 1;
        } else if (isPrice != 1 && strcasecmp(products[i].name, input) == 0) {
            double priceWithVAT = products[i].sellingPrice * (1 + products[i].vatLevel / 100.0);
            printf(GREEN "\nFound: %s | EAN: %s | %.2f€ (%.2f€ with VAT) | %d pcs" RESET "\n",
                   products[i].name, products[i].ean, products[i].sellingPrice, priceWithVAT, products[i].quantity);
            found = 1;
        }
    }
    if (!found) printf(RED "No products found" RESET "\n");
    return 0;
}

int addNewProduct() {
    struct Product p;
    printf("\n" BLUE "Enter new product information" RESET);
    printf("\n" BLUE "----------------------------" RESET "\n");

    printf("Name: ");
    scanf(" %[^\n]", p.name);
    printf("EAN: ");
    scanf(" %[^\n]", p.ean);
    printf("Purchase price: ");
    scanf("%lf", &p.purchasePrice);
    printf("Selling price: ");
    scanf("%lf", &p.sellingPrice);
    printf("Quantity: ");
    scanf("%d", &p.quantity);
    printf("VAT level (21, ...): ");
    scanf("%d", &p.vatLevel);

    addProduct(p);
    saveCSV();
    printf(GREEN "\nProduct added successfully" RESET "\n");
    return 0;
}

int destroyProduct() {
    char input[100];
    int found = 0;

    printf("\nSearch product to delete: ");
    getchar();
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    double price;
    int isPrice = sscanf(input, "%lf", &price);

    for (int i = 0; i < productCount; i++) {
        int match = 0;
        if (isPrice == 1 && products[i].sellingPrice >= price - 0.01 && products[i].sellingPrice <= price + 0.01) {
            match = 1;
        } else if (isPrice != 1 && strcasecmp(products[i].name, input) == 0) {
            match = 1;
        }
        if (match) {
            printf(YELLOW "\nDeleted: %s - %s" RESET "\n", products[i].name, products[i].ean);
            for (int j = i; j < productCount - 1; j++) {
                products[j] = products[j + 1];
            }
            productCount--;
            i--;
            found = 1;
        }
    }
    if (!found) printf(RED "No products found" RESET "\n");
    else saveCSV();
    return 0;
}

int updateForm(int index) {
    int choice;
    printf("\n" BLUE "--------------------------------------" RESET);
    printf("\n" BLUE " Update product details" RESET);
    printf("\n" BLUE "--------------------------------------" RESET);
    printf("\n 1. Update name");
    printf("\n 2. Update EAN");
    printf("\n 3. Update purchase price");
    printf("\n 4. Update selling price");
    printf("\n 5. Update quantity");
    printf("\n 6. Update VAT level");
    printf("\n 0. Back");
    printf("\n");

    printf("\nChoose an action: ");
    scanf("%d", &choice);

    switch (choice) {
        case 0:
            return 0;
        case 1:
            printf("New name: ");
            scanf(" %[^\n]", products[index].name);
            break;
        case 2:
            printf("New EAN: ");
            scanf(" %[^\n]", products[index].ean);
            break;
        case 3:
            printf("New purchase price: ");
            scanf("%lf", &products[index].purchasePrice);
            break;
        case 4:
            printf("New selling price: ");
            scanf("%lf", &products[index].sellingPrice);
            break;
        case 5:
            printf("New quantity: ");
            scanf("%d", &products[index].quantity);
            break;
        case 6:
            printf("New VAT level: ");
            scanf("%d", &products[index].vatLevel);
            break;
        default:
            printf(RED "Invalid action" RESET "\n");
    }
    saveCSV();
    return 0;
}

int updateProduct() {
    char input[100];
    int found = 0;

    printf("\nSearch product to update: ");
    getchar();
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    double price;
    int isPrice = sscanf(input, "%lf", &price);

    for (int i = 0; i < productCount; i++) {
        if (isPrice == 1 && products[i].sellingPrice >= price - 0.01 && products[i].sellingPrice <= price + 0.01) {
            printf(GREEN "Found: %s | EAN: %s | %.2f€ | %d pcs" RESET "\n",
                   products[i].name, products[i].ean, products[i].sellingPrice, products[i].quantity);
            found = 1;
            updateForm(i);
        } else if (isPrice != 1 && strcasecmp(products[i].name, input) == 0) {
            printf(GREEN "Found: %s | EAN: %s | %.2f€ | %d pcs" RESET "\n",
                   products[i].name, products[i].ean, products[i].sellingPrice, products[i].quantity);
            found = 1;
            updateForm(i);
        }
    }
    if (!found) printf(RED "No products found" RESET "\n");
    return 0;
}

int main(void) {
    int choice;
    loadCSV();

    while (1) {
        printf("\n" CYAN "--------------------------------------" RESET);
        printf("\n" CYAN " Storage management system" RESET);
        printf("\n" CYAN "--------------------------------------" RESET);
        printf("\n 1. Show all products");
        printf("\n 2. Show all products with VAT");
        printf("\n 3. Search product");
        printf("\n 4. Add new product");
        printf("\n 5. Delete product");
        printf("\n 6. Update product");
        printf("\n 0. Exit");
        printf("\n");

        printf("\nChoose an action: ");
        scanf("%d", &choice);

        switch (choice) {
            case 0:
                printf(YELLOW "Bye\n" RESET);
                free(products);
                return 0;
            case 1:
                show();
                break;
            case 2:
                showWithVAT();
                break;
            case 3:
                searchProduct();
                break;
            case 4:
                addNewProduct();
                break;
            case 5:
                destroyProduct();
                break;
            case 6:
                updateProduct();
                break;
            default:
                printf(RED "Invalid action" RESET "\n");
        }
    }
}
