#pragma once
#include <iostream>
#include "SeqList.h"
#include "Iterator.h"
template <class T>
class SeqListIterator : public Iterator<T> {
	SeqList<T>* listPtr;
	Node<T>* prevPtr, * currPtr;

public:

	SeqListIterator(SeqList<T>& lst) : Iterator<T>(){
		listPtr = &lst;
		this->iterationComplete = listPtr->llist.ListEmpty();
		Reset();
	}

	virtual void Next() {
		if (currPtr == NULL)
			return;
		prevPtr = currPtr;
		currPtr = currPtr->NextNode();
		if (currPtr == NULL)
			this->iterationComplete = 1;
	}
	virtual void Reset() {
		this->iterationComplete = listPtr->llist.ListEmpty();
		if (listPtr->llist.front == nullptr)
			return;
		prevPtr = nullptr;
		currPtr = listPtr->llist.front;
	}
	virtual T& Data() {
		if (listPtr->llist.ListEmpty() || currPtr == nullptr) {
			std::cerr << "Data: недопустимая ссылка!" << std::endl;
			exit(1);
		}
		return currPtr->data;
	}

	void SetList(SeqList<T>& lst) {
		listPtr = &lst;
		Reset();
	}
};

