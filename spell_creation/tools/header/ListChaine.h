#pragma once

typedef void* LinkList;

typedef char(*Condition)(void* _param, void* _value);
typedef void(*Action)(void* _param, void* _value);
typedef void(*destroy)(void* _value);

void pushBackValue(LinkList* _list, void* _newValue);
void pushFrontValue(LinkList* _list, void** _newValue);
void insertAt(LinkList* _list, void* _newValue, int _index);

void forAll(LinkList* _list, Action _action, void* _param);
void forAllIf(LinkList* _list, Condition _condition, void* _paramCond, Action _action, void* _paramAction);

void* getLast(LinkList* _list);
char getIndexFromValue(LinkList* _list, void* _value);
void* getValueFromIndex(LinkList* _list, char _index);

void delValue(LinkList* _list, void* _value);
void removeAt(LinkList* _list, int _index);
void popFront(LinkList* _list);
void popBack(LinkList* _list);

void delAll(LinkList* _list);
void delAllWith(LinkList* _list, destroy _destroyFonction);
