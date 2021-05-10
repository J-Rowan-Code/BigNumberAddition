#include <cstdlib>
#include <iostream>
#include <fstream>
#include <locale>
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
using namespace std;

template <class T>
class List {
	private:
		struct Node{
			T data;
			Node *next;
		};
		Node *front, *current;
		
	public:
		List();
		~List();
		void printLL();
		void addToFront(T new1);
		void addToTail(T new1);
		void reverse();
		void pop();
		bool firstItem(T &item);
		bool nextItem(T &item);
		bool isEmpty();
		T showTop();
};


class bigNumber {
	private:
		List<int> L;
		bool overflow;
		int count;
	public:
		bigNumber();
		~bigNumber();
		void readFromString(string inString);
		void addNum(int x);
		void showList();
		int topNum();
		void addBigNumber(bigNumber x, bigNumber y);
		void nextL();
		void reverse();
		bool emptyN();
};

bigNumber B1, B2, Lulu;

int main (int argc, char **argv){
	string numberString;
	int checkN=0;
	ifstream inputFile;
	
	if(argc==2) inputFile.open(argv[1]);
	else { cout<< "cannot read the file " << argv[1] << endl; exit(0);}
	//inputFile.open("samplenumbers6.txt");
	//if(inputFile.is_open()==false){ cout << "bruh." << endl; exit(1);}
	while(!inputFile.eof()){
		getline(inputFile, numberString);
		if(!inputFile.eof()){
			//cout << "reading a big number from file:" << numberString << endl;
			if(checkN==0){
				B1.readFromString(numberString);
				checkN=1;
			}else{
				B2.readFromString(numberString);
			}
		}
	}
	B1.reverse();
	B1.showList();
	B1.reverse();
	cout << endl;
	cout << "+" << endl;
	B2.reverse();
	B2.showList();
	B2.reverse();
	cout << endl;
	cout << "=" << endl;
	Lulu.addBigNumber(B1, B2);
	Lulu.showList();
}

bigNumber::bigNumber(){
	overflow = false;
}

bigNumber::~bigNumber(){
	return;
}

void bigNumber::addNum(int x){
	L.addToFront(x);
}

void bigNumber::showList(){
	L.printLL();
}

int bigNumber::topNum(){
	return L.showTop();
}

void bigNumber::readFromString(string inString){
	for(int i = 0; i < inString.size(); i++){
		if(inString[i]!='\n' && inString[i]!='\r'){
			int temp = inString[i] -48;
			//cout << "Digit " << i << "/" << inString[i] << " is " << temp << endl;
			L.addToFront(temp);
		}
	}			
}

void bigNumber::addBigNumber(bigNumber x, bigNumber y){
	int temp;
	while((!x.emptyN())&&(!y.emptyN())){
		temp = y.topNum() + x.topNum();
		if (overflow == true){
			temp = temp+1;
			overflow=false;
		}
		if(temp>9){
			temp = temp-10;
			overflow=true;
		}
		L.addToFront(temp);
		x.nextL();
		y.nextL();
	}
	while(!x.emptyN()){
		temp = x.topNum();
		if(overflow){
			temp = temp+1;
			overflow=false;
		}
		if(temp>9){
			temp = temp-10;
			overflow=true;
		}
		L.addToFront(temp);
		x.nextL();
	}
	while(!y.emptyN()){
		temp = y.topNum();
		if(overflow){
			temp = temp+1;
			overflow=false;
		}
		if(temp>9){
			temp = temp-10;
			overflow=true;
		}
		L.addToFront(temp);
		y.nextL();
	}
	if(overflow){
		L.addToFront(1);
	}
	//cout << endl << "TOP NUM: " << temp << endl;
	
}

void bigNumber::nextL(){
	L.pop();
}

void bigNumber::reverse(){
	L.reverse();
}

bool bigNumber::emptyN(){
	return L.isEmpty();
}

template <class T>
List<T>::List(){
	front = NULL;
	current = NULL;
}

template <class T>
List<T>::~List(){
	return;
}

template <class T>
void List<T>::printLL(){
	Node *currentp;
	currentp = front;
	if(currentp==NULL){
		cout << "The list is empty" << endl;
		return;
	}
	while(currentp!=NULL){
		cout /*<< "Value stored is: " */<< currentp->data;// << endl;
		currentp = currentp->next;
	}
	//cout << "End of list" << endl;
}

template <class T>
void List<T>::addToFront(T new1){
	Node *temp;
	temp = new Node;
	temp->data = new1;
	temp->next = front;
	front = temp;
}

template <class T>
void List<T>::addToTail(T new1){
	Node *end;
	end = front;
	if(end!=NULL){
		while(end->next!=NULL){
			end = end->next;
		}
	}
	Node *temp;
	temp = new Node;
	temp->data = new1;
	temp->next = NULL;
	if(end!=NULL){
		end->next = temp;
	}else{
		front=temp;
	}
}

template <class T>
void List<T>::pop(){
	Node *temp;
	if(front == NULL){
		cout << "List is empty" << endl;
		return;
	}
	temp = front;
	front = front->next;
	delete temp;
}

template <class T>
bool List<T>::firstItem(T &item){
	if (front==NULL){
		return false;
	}
	item = front->data;
	current = front;
	return true;
}

template <class T>
bool List<T>::nextItem(T &item){
	current = current->next;
	if (current==NULL){
		return false;
	}
	item = current->data;
	return true;
}

template <class T>
void List<T>::reverse(){
	Node *P1, *P2, *P3;
	P2 = front;
	P3 = front->next;
	while(P3!=NULL){
		P1 = P3->next;
		P3->next = front;
		front = P3;
		P3 = P1;
	}
	P2->next = NULL;
}

template <class T>
T List<T>::showTop(){
	return front->data;
}

template <class T>
bool List<T>::isEmpty(){
	if(front == NULL){
		return true;
	}
	return false;
}
