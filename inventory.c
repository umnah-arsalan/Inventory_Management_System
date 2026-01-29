#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "inventory.h"

int id_check(int id) {
    struct Product p;
    FILE *fp = fopen(DB_FILE, "rb");

    if (!fp) {
        printf("\nFile doesn't exist!\n\n");
        return 0;
    }

    while (fread(&p, sizeof(struct Product), 1, fp)) {
        if (id == p.id) {
            printf("\nID already exists!\n\n");
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

void sort_inventory() {
    struct Product products[100], temp;
    FILE *fp = fopen(DB_FILE, "rb");
    int count = 0, i, j;
    float grand_total = 0.0;

    if (!fp) {
        printf("\nNo products to print!\n\n");
        return;
    }

    while (fread(&products[count], sizeof(struct Product), 1, fp))
        count++;
    fclose(fp);

    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count - i - 1; j++) {
            if (strcmp(products[j].name, products[j + 1].name) > 0) {
                temp = products[j];
                products[j] = products[j + 1];
                products[j + 1] = temp;
            }
        }
    }

    for (i = 0; i < count; i++) {
        float value = products[i].price * products[i].quantity;
        grand_total += value;

        printf("%-6d %-20s %-10d %-10.2f %f\n", 
            products[i].id, products[i].name, products[i].quantity, products[i].price, value);
    }

    printf("\nTotal inventory value: %.2f\n\n", grand_total);
}

void add_product() {
    FILE *fp = fopen(DB_FILE, "ab");
    FILE *text = fopen("inventory.txt", "a");
    struct Product p;
    int id;

    printf("\nEnter product ID: ");
    scanf("%d", &id);

    while (id_check(id) != 0) {
        printf("Enter product ID: ");
        scanf("%d", &id);
    }
    p.id = id;

    printf("Enter product name: ");
    scanf(" %[^\n]", p.name);

    printf("Enter quantity: ");
    scanf("%d", &p.quantity);

    printf("Enter price: ");
    scanf("%f", &p.price);

    fwrite(&p, sizeof(struct Product), 1, fp);
    fprintf(text, "%d | %s | %d | %f\n", p.id, p.name, p.quantity, p.price);

    fclose(fp);
    fclose(text);

    printf("\nProduct added successfully!\n\n");
}

void view_products() {
    printf("\n%-6s %-20s %-10s %-10s %s\n",
           "ID", "Name", "Qty", "Price", "Value");
    printf("---------------------------------------------\n");

    sort_inventory();
}

void search_product() {
    FILE *fp = fopen(DB_FILE, "rb");
    struct Product p;
    int id, found = 0;

    printf("\nEnter Product ID to search: ");
    scanf("%d", &id);

    while (fread(&p, sizeof(struct Product), 1, fp)) {
        if (p.id == id) {
            printf("\nFound: %d | %s | %d | %.2f\n",
                   p.id, p.name, p.quantity, p.price);

            printf("\n");
            found = 1;
            break;
        }
    }

    if (!found)
        printf("\nProduct not found!\n\n");

    fclose(fp);
}

void update_product() {
    struct Product p;
    FILE *fp = fopen(DB_FILE, "rb+");
    int id, found = 0;

    if (!fp) {
        printf("\nFile doesn't exist!\n\n");
        return;
    }

    printf("\nEnter product ID to update: ");
    scanf("%d", &id);

    while (fread(&p, sizeof(struct Product), 1, fp)) {
        if (id == p.id) {

            printf("Enter new name: ");
            scanf(" %[^\n]", p.name);

            printf("Enter new quatity: ");
            scanf("%d", &p.quantity);

            printf("Enter new price: ");
            scanf("%f", &p.price);

            fseek(fp, -sizeof(struct Product), SEEK_CUR);
            fwrite(&p, sizeof(struct Product), 1, fp);

            printf("\nProduct updated successfully!\n\n");
            found = 1;
            break;
        }
    }

    if (!found)
        printf("\nProduct not found!\n\n");
    
    fclose(fp);
}

void delete_product() {
    struct Product p;
    FILE *fp = fopen(DB_FILE, "rb");
    FILE *temp = fopen("temp.dat", "wb");
    int id, found = 0;

    if (!fp || !temp) {
        printf("\nFile error!\n\n");
        return;
    }

    printf("\nEnter ID to delete: ");
    scanf("%d", &id);

    while (fread(&p, sizeof(struct Product), 1, fp)) {
        if (id != p.id) {
            fwrite(&p, sizeof(struct Product), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove(DB_FILE);
    rename("temp.dat", DB_FILE);

    if (found)
        printf("\nProduct deleted successfully!\n\n");
    else
        printf("\nProduct not found!\n\n");
}

void low_stock_alert() {
    struct Product p;
    FILE *fp = fopen(DB_FILE, "rb");

    printf("-------LOW STOCK PRODUCTS-------\n");

    while (fread(&p, sizeof(struct Product), 1, fp)) {
        if (p.quantity < 5)
            printf("%d | %s | %d\n", p.id, p.name, p.quantity);
    }

    printf("\n");

    fclose(fp);
}