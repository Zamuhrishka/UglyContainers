/**
 * @file bt.h
 * @author Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief
 * @date 2023-02-20
 */

#pragma once


//_____ I N C L U D E S _______________________________________________________
#include <stdint.h>
#include <stdbool.h>
//_____ C O N F I G S  ________________________________________________________

//_____ D E F I N I T I O N S _________________________________________________
struct bt;
typedef struct bt bt_t;

typedef int (*btcmp_fn_t)(void*, void*);
//_____ M A C R O S ___________________________________________________________

//_____ V A R I A B L E S _____________________________________________________

//_____ P U B L I C  F U N C T I O N S_________________________________________
bt_t* bt_create(size_t esize, btcmp_fn_t compare_cb);
void bt_delete(bt_t* bt);
bool bt_insert(bt_t* bt, void* data);
bool bt_remove(bt_t* bt, void* data);
void* bt_min(const bt_t* bt);
void* bt_max(const bt_t* bt);
bool bt_search(bt_t* bt, void* data);

void bt_pre_order_traversal(const bt_t* bt, void (*callback)(void* data));
void bt_post_order_traversal(const bt_t* bt, void (*callback)(void* data));
void bt_in_order_traversal(const bt_t* bt, void (*callback)(void* data));