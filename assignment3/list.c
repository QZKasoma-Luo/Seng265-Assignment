/** @file list.c
 *  @brief Implementation of a linked list.
 *
 * Based on the implementation approach described in "The Practice
 * of Programming" by Kernighan and Pike (Addison-Wesley, 1999).
 *
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "emalloc.h"
#include "list.h"

/**
 * Function:  new_node
 * -------------------
 * @brief  Allows to dynamically allocate memory for a new node to be added to the linked list.
 *
 * This function should confirm that the argument being passed is not NULL (i.e., using the assert library). Then,
 * It dynamically allocates memory for the new node using emalloc(), and assign values to attributes associated with the node (i.e., val and next).
 *
 * @param artist The value to be associated with the node.
 * @param popularity The value to be associated with the node.
 * @param song The value to be associated with the node.
 * @param year The value to be associated with the node.
 * @param energy The value to be associated with the node.
 * @param danceability The value to be associated with the node.
 *
 * @return node_t* A pointer to the node created.
 *
 */
node_t *new_node(char *artist, int popularity, char *song, int year, double energy, double danceability)
{
    assert(artist != NULL);
    assert(song !=NULL);

    node_t *temp = (node_t *)emalloc(sizeof(node_t));

    temp->artist = strdup(artist);
    temp->song = strdup(song);
    temp->year = year;
    temp->popularity = popularity;
    temp->danceability = danceability;
    temp->energy = energy;
    temp->next = NULL;

    return temp;
}

/**
 * Function:  add_front
 * --------------------
 * @brief  Allows to add a node at the front of the list.
 *
 * @param list The list where the node will be added (i.e., a pointer to the first element in the list).
 * @param new The node to be added to the list.
 *
 * @return node_t* A pointer to the new head of the list.
 *
 */
node_t *add_front(node_t *list, node_t *new)
{
    new->next = list;
    return new;
}

/**
 * Function:  add_end
 * ------------------
 * @brief  Allows to add a node at the end of the list.
 *
 * @param list The list where the node will be added (i.e., a pointer to the first element in the list).
 * @param new The node to be added to the list.
 *
 * @return node_t* A pointer to the head of the list.
 *
 */
node_t *add_end(node_t *list, node_t *new)
{
    node_t *curr;

    if (list == NULL)
    {
        new->next = NULL;
        return new;
    }

    for (curr = list; curr->next != NULL; curr = curr->next)
        ;
    curr->next = new;
    new->next = NULL;
    return list;
}

/**
 * Function:  add_inorder
 * ----------------------
 * @brief  Allows to add a new node to the list respecting an order.
 *
 * @param linked_list The list where the node will be added (i.e., a pointer to the first element in the list).
 * @param node The node to be added to the list.
 * @param sort_method The node to be added to the list.
 *
 * @return node_t* A pointer to the node created.
 *
 */
node_t *add_inorder(node_t *linked_list, node_t *new_node, char* sort_method ){
    node_t *prev = NULL;
    node_t *curr = NULL;
    if (linked_list == NULL){
        return new_node;
    }
    if(strcmp(sort_method, "danceability") ==0 ){// check which sort method it is and sort by that method
        for(curr = linked_list; curr != NULL; curr = curr->next){
            if ((new_node->danceability  == curr->danceability && strcmp(new_node->song, curr->song) <= 0)  || (new_node->danceability < curr->danceability)){
                prev = curr;
            }else{
                break;
            }
        }
    }
    if(strcmp(sort_method, "popularity") ==0){// check which sort method it is and sort by that method
        for(curr = linked_list; curr != NULL; curr = curr->next){
            if ((new_node->popularity  == curr->popularity && strcmp(new_node->song, curr->song) <= 0) || (new_node->popularity < curr->popularity)){
                prev = curr;
            }else{
                break;
            }
        }
    }
    if(strcmp(sort_method, "energy") ==0){// check which sort method it is and sort by that method
        for(curr = linked_list; curr != NULL; curr = curr->next){
            if ((new_node->energy  == curr->energy && strcmp(new_node->song, curr->song) <= 0) ||  (new_node->energy < curr->energy)){
                prev = curr;
            }else{
                break;
            }
        }
    }  
    new_node->next = curr;
    if (prev == NULL){
        return (new_node);
    }else{
        prev->next = new_node;
        return linked_list;
    }
}

/**
 * Function:  peek_front
 * ---------------------
 * @brief  Allows to get the head node of the list.
 *
 * @param list The list to get the node from.
 *
 * @return node_t* A pointer to the head of the list.
 *
 */
node_t *peek_front(node_t *list)
{
    return list;
}

/**
 * Function:  remove_front
 * -----------------------
 * @brief  Allows removing the head node of the list.
 *
 * @param list The list to remove the node from.
 *
 * @return node_t* A pointer to the head of the list.
 *
 */
node_t *remove_front(node_t *list)
{
    if (list == NULL)
    {
        return NULL;
    }

    return list->next;
}

/**
 * Function: apply
 * --------------
 * @brief  Allows to apply a function to the list.
 *
 * @param list The list (i.e., pointer to head node) where the function will be applied.
 * @param fn The pointer of the function to be applied.
 * @param arg The arguments to be applied.
 *
 */
void apply(node_t *list,
           void (*fn)(node_t *list, void *),
           void *arg)
{
    for (; list != NULL; list = list->next)
    {
        (*fn)(list, arg);
    }
}
