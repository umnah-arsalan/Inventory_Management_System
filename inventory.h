#ifndef INVENTORY_H
#define INVENTORY_H

#define DB_FILE "inventory.dat"

struct Product {
    int id;
    char name[50];
    int quantity;
    float price;
};

int id_check(int id);
void sort_inventory(void);
void add_product(void);
void view_products(void);
void search_product(void);
void update_product(void);
void delete_product(void);
void low_stock_alert(void);

#endif