#include "dll.h"
#include <stdio.h>
#include <stdlib.h>


void dll_init(dll_t *l)
{
	l->size=0;
	l->head=(dll_entry_t*)malloc(sizeof(dll_entry_t));
	l->tail=(dll_entry_t*)malloc(sizeof(dll_entry_t));
	l->head->next=l->tail;
	l->head->prev=NULL;
	l->tail->next=NULL;
	l->tail->prev=l->head;
}

void dll_destroy(dll_t *l)
{
	free(l->head);
	free(l->tail);
}

void dll_add_to_tail(dll_t *l, void *data)
{
	dll_entry_t *mytemp=(dll_entry_t*)malloc(sizeof(dll_entry_t));
	mytemp->data=data;
	l->size++;
	mytemp->next=l->tail;
	mytemp->prev=l->tail->prev;
	mytemp->prev->next=mytemp;
	mytemp->next->prev=mytemp;
}

void dll_add_to_head(dll_t *l, void *data)
{
	dll_entry_t *mytemp = malloc(sizeof(*mytemp));
	mytemp->data = data;
	l->size++;
	mytemp->prev = l->head;
	mytemp->next = l->head->next;
	mytemp->prev->next = mytemp;
	mytemp->next->prev = mytemp;
}

void dll_add_between(dll_t *l,dll_entry_t *prev, dll_entry_t *next, void *data)
{
	dll_entry_t *mytemp = malloc(sizeof(*mytemp));
	mytemp->data = data;
	l->size++;
	mytemp->next = next;
	mytemp->prev = prev;
	next->prev = mytemp;
	prev->next = mytemp;
}

void dll_add_at_index(dll_t *l, void *data,unsigned int index)
{
	if (index == 0) {
		dll_add_to_head(l,data);
	} else if (index == l->size) {
		dll_add_to_tail(l,data);
	} else {
		dll_entry_t *prev,*next;
		prev = dll_pointer_at(l,index-1);
		next = dll_pointer_at(l,index+1);
		dll_add_between(l,prev,next,data);
	}
}

void* dll_remove_from_head(dll_t *l)
{
	if(l->size==0)
		return NULL;

	dll_entry_t *mytemp=l->head->next;
	void *ret=mytemp->data;
	l->head->next=mytemp->next;
	mytemp->next->prev=l->head;
	l->size--;
	free(mytemp);
	return ret;
}

dll_entry_t* dll_pointer_at(dll_t *l,int index)
{
	int i;
	dll_entry_t *it=l->head;
	if(l->size==0) return NULL;
	if((unsigned int)index+1>l->size) return NULL;
	for(i=0;i<index+1;i++)
		it=it->next;
	return it;
}

void* dll_at(dll_t *l,int index)
{
	dll_entry_t *ret=dll_pointer_at(l,index);
	if(ret)
		return ret->data;
	return NULL;
}

int dll_size(dll_t *l)
{
	return l->size;
}
