#include "header/ListChaine.h"
#include <stdlib.h>

void pushBackValue(LinkList* _list, void* _newValue) {
	if (*_list == NULL) { *_list = _newValue; return; }

	*((void**) getLast(_list)) = _newValue;
}

void pushFrontValue(LinkList* _list, void** _newValue) {
	if (_newValue == NULL) return;
	*_newValue = *_list;
	*_list = _newValue;
}

void insertAt(LinkList* _list, void* _newValue, int _index) {
	if (_list == NULL || *_list == NULL || _index < 1) return pushFrontValue(_list, _newValue);

	void** current = *_list;
	for (int i = 0; i < _index - 1; i++) {
		current = (void**)*current;
		if (current == NULL) return pushBackValue(_list, _newValue);
	}
	*current = _newValue;
}

void delValue(LinkList* _list, void* _value) {
	if (_list == NULL || *_list == NULL) return;

	void** last = NULL;
	void** current = *_list;
	while (current != _value) { // recherche la bonne valeur
		last = current;
		current = (void**) *current;
		if (current == NULL) return;
	}

	// puis l'extermine
	if (last == NULL) *_list = (LinkList*) *current;
	else *last = *current;

	free(current);
}

void removeAt(LinkList* _list, int _index) {
	if (_list == NULL || *_list == NULL || _index < 0) return popFront(_list);

	void** current = *_list;
	if (*current == NULL) return popBack(_list);
	for (int i = 0; i < _index - 1; i++) {
		current = (void**) *current;
		if (*current == NULL) return popBack(_list);
	}
	void** asuppr = *current;
	*current = (void**)*asuppr;

	free((void*) asuppr);
}

void popFront(LinkList* _list) {
	if (_list == NULL || *_list == NULL) return;

	void** current = *_list;
	*_list = *current;

	free((void*) current);
}

void popBack(LinkList* _list) {
	if (_list == NULL || *_list == NULL) return;
	void** current = *_list;
	if (*current == NULL) {
		*_list = NULL;
		return free(current);
	}

	while (*((void**) *current) != NULL) current = (void**) *current;

	free(*current);
	*current = NULL;
}

void delAll(LinkList* _list)
{
	if (_list == NULL || *_list == NULL) return;

	void** current = *_list;
	void** next = NULL;

	while (current != NULL) {
		next = *current;
		free(current);
		current = next;
	}
}

void delAllWith(LinkList* _list, destroy _destroyFonction)
{
	if (_list == NULL || *_list == NULL || _destroyFonction == NULL) return;

	void** current = *_list;
	void** next = NULL;

	while (current != NULL) {
		next = *current;
		_destroyFonction(current);
		free(current);
		current = next;
	}
}

void forAll(LinkList* _list, Action _action, void* _param) { // éxecute une action pour tous les éléments de la list
	if (_list  == NULL || *_list == NULL || _action == NULL) return;

	void** current = *_list;
	void** next = NULL;
	while (current != NULL) {
		next = *current;
		if (current != NULL)
			_action(_param, current);
		current = next;
	}
}

void forAllIf(LinkList* _list, Condition _condition, void* _paramCond, Action _action, void* _paramAction) {
	if (_list == NULL || *_list == NULL || _action == NULL) return;

	void** current = *_list;
	void** next = NULL;
	while (current != NULL) {
		next = *current;
		if (current != NULL && _condition(_paramCond, current)) // si condition
			_action(_paramAction, current);                     // alors action
		current = next;
	}
}

void* getLast(LinkList* _list) {
	if (_list == NULL || *_list == NULL) return NULL;

	void** current = *_list;
	while (*current != NULL) current = (void**)*current;

	return current;
}

char getIndexFromValue(LinkList* _list, void* _value) {
	if (_list == NULL || *_list == NULL) return -1;

	int i = 0;
	void** current = *_list;
	while (current != _value) {
		current = *current;
		i++;
		if (current == NULL) return -1;
	}
	return i;
}

void* getValueFromIndex(LinkList* _list, char _index) {
	if (_list == NULL || *_list == NULL || _index < 0) return NULL;

	void** current = *_list;
	for (int i = 0; i < _index; i++) {
		current = *current;
		if (current == NULL) return NULL;
	}
	return *current;
}
