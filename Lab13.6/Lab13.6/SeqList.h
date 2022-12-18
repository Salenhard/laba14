#pragma once
#include <iostream>
#include"LinkedList.h"
#include "List.h"
template<class T>
class SeqListIterator;
template<class T>
class SeqList:public List<T>
{
private:
	LinkedList<T> llist;
public:

	SeqList();
	// методы доступа
	int ListSize() const;
	int ListEmpty() const;
	int Find(const T& item);
	T GetData(int pos);

	// методы модификации
	void Insert(const T& item);
	void Delete(const T& item);
	T DeleteFront();
	void ClearList();
	friend class SeqListIterator<T>;
};

template<class T>
SeqList<T>::SeqList() : List<T>(), llist() {
	
}
template<class T>
int SeqList<T>::Find(const T& item) {
	for(llist.Reset();!llist.EndOfList(); llist.Next())
		if (item == llist.Data()) {
			return 1;
		}
	return 0;
}

template<class T>
T SeqList<T>::GetData(int pos) {
	if (pos < 0 || pos >= llist.ListSize()) {

		cerr << "pos вне диапозона!" << endl;
		exit(1);
	}

	llist.Reset(pos);
	return llist.Data();
}

template<class T>
int SeqList<T>::ListSize() const {
	return llist.ListSize();
}

template<class T>
int SeqList<T>::ListEmpty() const {
	return llist.ListEmpty();
}

template<class T>
void SeqList<T>::Insert(const T& item) {
	llist.InsertRear(item);
}

template<class T>
void SeqList<T>::Delete(const T& item) {
	for (llist.Reset(); !llist.ListEmpty(); llist.Next())
		if (item == llist.Data())
			llist.DeleteAt();
}

template<class T>
T SeqList<T>::DeleteFront() {
	return llist.DeleteFront();
}

template <class T>
void SeqList<T>::ClearList() {
	llist.ClearList();
}
