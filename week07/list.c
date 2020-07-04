// Implementation of list module.
#include "list.h"
// ---------- Add headers here ----------
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Each node in a doubly linked list is stored in this structure. The user of the
// module does not have any knowledge of nodes.
struct node {
   struct node *back;
   item x;
   struct node *next;
 };
typedef struct node node;

// A list is to be represented as a circular list. It has to contain a doubly linked list
// of item nodes and one special sentinel node that links to the two ends of the item list.
// The none field holds this sentinel node. It has a default item, must always be present for
// a list and always sits before the first item node and after the last item node. For a list
// that holds no item nodes the back and next fields of the sentinel node point to the sentinel
// node itself. The current node refers to the currently selected item node in the list. If
// the current node is the none node then no item is selected.
struct list {
  node *none,//sentinel node
  *current; //currently selected node
 };
typedef struct list list;

// ---------- Add functions here ----------
typedef int item;

// The list type is opaque (declared here, and defined in lists.c).
struct list;
typedef struct list list;

// Create a new empty list, with the default item to return in case no item is selected.
// No item is selected in an empty list.
list *newList(item e){
  list *xs = malloc(sizeof(list));
  xs -> none = malloc(sizeof(node));
  xs -> none -> x = e;
  xs -> current = xs -> none;
  xs -> none -> back = xs -> none;
  xs -> none -> next = xs -> none;
  return xs;
}

// Free up the list and all the data in it.
void freeList(list *xs){
  struct node* temp;
  first(xs);
  while(xs -> current != xs -> none){
    temp = xs -> current;
    xs->current = xs -> current ->next;
    free(temp);
  }
  free(xs->none);
  free(xs);
}

// Set the current item to the first item or to the last item
// of the list. If the list has no items the functions do nothing
// and no item is selected.
void first(list *xs){
  if(xs ->current != NULL){
    xs -> current = xs -> none -> next;
  }
}
void last(list *xs){
  if(xs->current != NULL){
    xs -> current = xs -> none -> back;
  }
}

// Returns true if no item is selected, i.e. the 'none' position.
// Otherwise it returns false.
bool none(list *xs){
  if(xs -> current == xs -> none){
    return true;
  }
  else{
    return false;
  }
}

// Move the current item one place forwards in the list and return true.
// If after is called while the last item is the current item, then no item is
// selected and true is returned. If the function is called while no item
// is selected then the function does nothing and returns false.
bool after(list *xs){
  if(none(xs) == true){
    return false;
  }
  else{
    xs -> current = xs -> current -> next;
    return true;
  }
}

// Move the current item one place forwards in the list and return true.
// If before is called while the first item is the current item, then no item is
// selected and true is returned. If the function is called while no item
// is selected then the function does nothing and returns false.
bool before(list *xs){
  if(none(xs) == true){
    return false;
  }
  else{
    xs -> current = xs -> current -> back;
    return true;
  }
}

// Get the current item. If get is called and no item is selected
// then the default item is returned.
item get(list *xs){
  if (xs->current != NULL){
    return (xs -> current -> x);
  }
  else{
    return 0;
  }
}

// Set the current item and return true. If set is called while no
// item is selected then the function does nothing and returns false.
bool set(list *xs, item x){
  if(none(xs) == true){
    return false;
  }
  else{
    xs -> current -> x = x;
    return true;
  }
}

// Inserts an item after the current item and makes it the current item.
// If insertAfter is called while no item is selected then
// the function inserts the item at the beginning of the list
// before the first item.
void insertAfter(list *xs, item x){
  node *p, *q;
  node *newNode = malloc(sizeof(node));
  newNode -> x = x;
  if(none(xs) == true){
    first(xs);
    p = xs -> none;
    q = xs -> current;
    newNode -> back = p;
    newNode -> next = q;
    p -> next = newNode;
    q -> back = newNode;
    first(xs);
  }
  else{
    p = xs -> current;
    q = p -> next;
    newNode -> back = p;
    newNode -> next = q;
    q -> back = newNode;
    p -> next = newNode;
    xs->current = p -> next;
  }
}

// Inserts an item before the current item and makes it the current item.
// If insertAfter is called while no item is selected then the function inserts
// the item at the end of the list after the last item.
void insertBefore(list *xs, item x){
  node *newNode = malloc(sizeof(node));
  node *p, *q;
  newNode -> x = x;
  if(none(xs) == true){
    last(xs);
    p = xs -> none;
    q = xs -> current;
    newNode -> next = p;
    newNode -> back = q;
    p -> back = newNode;
    q -> next = newNode;
    last(xs);
  }
  else{
    p = xs -> current;
    q = xs -> current -> back;
    newNode -> next = p;
    newNode -> back = q;
    q -> next = newNode;
    p -> back = newNode;
    xs -> current = p -> back;
  }
}

// Delete the current item and make its successor the current item, then return
// true. If deleteToAfter is called while the last item is the current item then
// the last item is deleted, no item is selected, and true is returned.
// If deleteToAfter is called while no item is selected then the
// function does nothing and returns false.
bool deleteToAfter(list *xs){
  node *p, *q, *r;
  if(none(xs)==true){
    return false;
  }
  else{
    p = xs -> current; //current item
    q = p -> next; //next item
    r = p -> back; //prev item
    r -> next = q;
    q -> back = r;
    xs -> current = q;
    free(p);
    return true;
  }
}

// Delete the current item and make its predecessor the current item, then return
// true. If deleteToBefore is called while the first item is the current item then
// the first item is deleted, no item is selected, and true is returned.
// If deleteToBefore is called while no item is selected then the
// function does nothing and returns false.
bool deleteToBefore(list *xs){
  node *p, *q, *r;
  if(none(xs)==true){
    return false;
  }
  else{
    p = xs -> current; //current item
    q = p -> next; //next item
    r = p -> back; //prev item
    r -> next = q;
    q -> back = r;
    xs -> current = r;
    free(p);
    return true;
  }
  return false;
}

// Test the list module, using int as the item type. Strings are used as
// 'pictograms' to describe lists. Single digits represent items and the '|' symbol
// in front of a digit indicates that this is the current item. If the '|' symbol
// is at the end of the string then 'none' of the items is selected. The strings
// "|37", "3|7", "37|" represent a list of two items, with the current position
// at the first item, the last item, and a situation where 'none' of the items
// is selected.
#ifdef test_list

// Build a list from a pictogram, with -1 as the default item.
list *build(char *s) {
  list *xs = malloc(sizeof(list));
    int n = strlen(s);
    node *nodes[n];
    for (int i = 0; i < n; i++) nodes[i] = malloc(sizeof(node));
    for (int i = 0; i < n; i++) nodes[i]->next = nodes[(i + 1) % n];
    for (int i = 1; i < n + 1; i++) nodes[i % n]->back = nodes[i - 1];
    xs->none = nodes[0];
    xs->none->x = -1;
    node *p = xs->none->next;
    for (int i = 0; i < strlen(s); i++) {
      if (s[i] == '|') xs->current = p;
      else {
        p->x = s[i] - '0';
        p = p->next;
      }
    }
  return xs;
}

// Destroy a list which was created with the build function and which matches a
// pictogram.
void destroy(list *xs, char *s) {
  int n = strlen(s);
  node *nodes[n];
  nodes[0] = xs->none;
  for (int i = 1; i < n; i++) nodes[i] = nodes[i-1]->next;
  for (int i = 0; i < n; i++) free(nodes[i]);
  free(xs);
}

// Check that a list matches a pictogram.
bool match(list *xs, char *s) {
  int n = strlen(s);
  node *nodes[n];
  nodes[0] = xs->none;
  for (int i = 1; i < n; i++) nodes[i] = nodes[i - 1]->next;
  if (nodes[n - 1]->next != xs->none) return false;
    for (int i = 1; i < n; i++) {
      if (nodes[i]->back != nodes[i - 1]) return false;
    }
  node *p = xs->none->next;
  for (int i = 0; i < strlen(s); i++) {
    if (s[i] == '|') {
      if (p != xs->current) return false;
    }
    else {
      if (p->x != s[i] - '0') return false;
      p = p->next;
    }
  }
  return true;
}

// Use constants to say which function to call.
enum { First, Last, None, After, Before, Get, Set, InsertAfter, InsertBefore, DeleteToAfter, DeleteToBefore};
typedef int function;

// A replacement for the library assert function.
void assert(int line, bool b) {
  if (b) return;
  printf("The test on line %d fails.\n", line);
  exit(1);
}

// Call a given function with a possible integer argument, returning a possible
// integer or boolean result (or -1).
int call(function f, list *xs, int arg) {
  int result = -1;
  switch (f) {
    case None: result = none(xs); break;
    case First: first(xs); break;
    case Last: last(xs); break;
    case After: result = after(xs); break;
    case Before: result = before(xs); break;
    case Get: result = get(xs); break;
    case Set: result = set(xs, arg); break;
    case InsertAfter: insertAfter(xs, arg); break;
    case InsertBefore: insertBefore(xs, arg); break;
    case DeleteToBefore: result = deleteToBefore(xs); break;
    case DeleteToAfter: result = deleteToAfter(xs); break;
    default: assert(__LINE__, false);
  }
  return result;
}

// Check that a given function does the right thing. The 'in' value is passed to
// the function or is -1. The 'out' value is the expected result, or -1.
bool check(function f, int in, char *before, char *after, int out) {
  list *xs = build(before);
  int result = call(f, xs, in);
  //check circular list structure
  assert(__LINE__, (xs->none == xs->none->next->back));
  assert(__LINE__, (xs->none == xs->none->back->next));
  //check correct workings of the function
  bool ok = (match(xs, after) && (result == out));
  destroy(xs, after);
  return ok;
}

// Test newList, and call freeList. The test for freeList is that the memory
// leak detector in the -fsanitize=address or -fsanitize=leak compiler option
// reports no problems.
void testNewList() {
    list *xs = newList(-1);
    //check circular list structure
    assert(__LINE__, (xs->none == xs->none->next));
    assert(__LINE__, (xs->none == xs->none->back));
    //check that an empty list is produced with a sentinel correctly
    assert(__LINE__, match(xs, "|"));
    freeList(xs);
}

// Test the various functions.
void testFirst() {
    assert(__LINE__, check(First, -1, "|", "|", -1));
    assert(__LINE__, check(First, -1, "|37", "|37", -1));
    assert(__LINE__, check(First, -1, "3|7", "|37", -1));
    assert(__LINE__, check(First, -1, "37|", "|37", -1));
}

void testLast() {
    assert(__LINE__, check(Last, -1, "|", "|", -1));
    assert(__LINE__, check(Last, -1, "|37", "3|7", -1));
    assert(__LINE__, check(Last, -1, "3|7", "3|7", -1));
    assert(__LINE__, check(Last, -1, "37|", "3|7", -1));
}

void testNone() {
    assert(__LINE__, check(None, -1, "|", "|", true));
    assert(__LINE__, check(None, -1, "|37", "|37", false));
    assert(__LINE__, check(None, -1, "3|7", "3|7", false));
    assert(__LINE__, check(None, -1, "37|", "37|", true));
}

void testAfter() {
    assert(__LINE__, check(After, -1, "|", "|", false));
    assert(__LINE__, check(After, -1, "|37", "3|7", true));
    assert(__LINE__, check(After, -1, "3|7", "37|", true));
    assert(__LINE__, check(After, -1, "37|", "37|", false));
}

void testBefore() {
    assert(__LINE__, check(Before, -1, "|", "|", false));
    assert(__LINE__, check(Before, -1, "|37", "37|", true));
    assert(__LINE__, check(Before, -1, "3|7", "|37", true));
    assert(__LINE__, check(Before, -1, "37|", "37|", false));
}

void testGet() {
    assert(__LINE__, check(Get, -1, "|", "|", -1));
    assert(__LINE__, check(Get, -1, "|37", "|37", 3));
    assert(__LINE__, check(Get, -1, "3|7", "3|7", 7));
    assert(__LINE__, check(Get, -1, "37|", "37|", -1));
}

void testSet() {
    assert(__LINE__, check(Set, 5, "|", "|", false));
    assert(__LINE__, check(Set, 5, "|37", "|57", true));
    assert(__LINE__, check(Set, 5, "3|7", "3|5", true));
    assert(__LINE__, check(Set, 5, "37|", "37|", false));
}

void testInsertAfter() {
    assert(__LINE__, check(InsertAfter, 5, "|", "|5", -1));
    assert(__LINE__, check(InsertAfter, 5, "|37", "3|57", -1));
    assert(__LINE__, check(InsertAfter, 5, "3|7", "37|5", -1));
    assert(__LINE__, check(InsertAfter, 5, "37|", "|537", -1));
}

void testInsertBefore() {
    assert(__LINE__, check(InsertBefore, 5, "|", "|5", -1));
    assert(__LINE__, check(InsertBefore, 5, "|37", "|537", -1));
    assert(__LINE__, check(InsertBefore, 5, "3|7", "3|57", -1));
    assert(__LINE__, check(InsertBefore, 5, "37|", "37|5", -1));
}

void testDeleteToAfter() {
    assert(__LINE__, check(DeleteToAfter, -1, "|", "|", false));
    assert(__LINE__, check(DeleteToAfter, -1, "|37", "|7", true));
    assert(__LINE__, check(DeleteToAfter, -1, "3|7", "3|", true));
    assert(__LINE__, check(DeleteToAfter, -1, "37|", "37|", false));
    assert(__LINE__, check(DeleteToAfter, -1, "|5", "|", true));
}

void testDeleteToBefore() {
    assert(__LINE__, check(DeleteToBefore, -1, "|", "|", false));
    assert(__LINE__, check(DeleteToBefore, -1, "|37", "7|", true));
    assert(__LINE__, check(DeleteToBefore, -1, "3|7", "|3", true));
    assert(__LINE__, check(DeleteToBefore, -1, "37|", "37|", false));
    assert(__LINE__, check(DeleteToBefore, -1, "|5", "|", true));
}

int main() {
    testNewList();
    testFirst();
    testLast();
    testNone();
    testAfter();
    testBefore();
    testGet();
    testSet();
    testInsertAfter();
    testInsertBefore();
    testDeleteToAfter();
    testDeleteToBefore();
    printf("List module tests run OK.\n");
    return 0;
}
#endif
