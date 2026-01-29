#include<stdio.h>
#include<stdlib.h>
#include "inventory.h"

int main() {
    int choice;

    while (1) {
        printf("--- Inventory Management System ---\n\n");
        printf("1. Add Product\n");
        printf("2. View Products\n");
        printf("3. Search Product\n");
        printf("4. Update Product\n");
        printf("5. Delete Product\n");
        printf("6. Low Stock Alert\n");
        printf("7. Exit\n\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: add_product(); break;
            case 2: view_products(); break;
            case 3: search_product(); break;
            case 4: update_product(); break;
            case 5: delete_product(); break;
            case 6: low_stock_alert(); break;
            case 7: exit(0);
            default: printf("\nInvalid choice!\n\n");
        }
    }
}