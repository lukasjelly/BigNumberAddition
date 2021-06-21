////////////////   159201   ///////////////////////////////////
//SAMPLE CODE FOR ASSIGNMENT 4 - Big Numbers
//2012 
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

/////// PART A

template<class T> // List is a class of datatype 'T'
class List {
private:
	struct Node {
		T data;
		Node* next, * prev;
	};
	Node* front, * rear, * current;
public:
	List();
	~List();
	void AddtoFront(T newthing);
	bool FirstItem(T& item);
	bool LastItem(T& item);
	bool NextItem(T& item);
	bool PrevItem(T& item);
	bool Reverse();
	bool MakeCopy(List& L);
	void PrintList(List& L);
	void PrintListReverse(List& L);
};

template<class T> //Must be used when defining methods. Data type used is of type 'T'
List<T>::List() { //Constructor. List<T>::List() instead of List:List() because defining with datatype 'T'
	front = NULL, rear = NULL, current = NULL;
}

template<class T>
List<T>::~List() {
}

template<class T>
void List<T>::AddtoFront(T newthing) {
	Node* temp; //create a new variable temp that points to struct Node
	temp = new Node; // allocate memory of size Node and place address in the pointer temp
	temp->data = newthing; //load data (type 'T') within allocated memory for Node with data passed as argument newthing
	temp->next = front; //temp pointing to next gets loaded with what is in front. first item in list = front will be NULL. second item front points to first item
	temp->prev = NULL;
	if (front == NULL) { rear = temp; } //list is empty. rear and front should point to first item. 
	if (front != NULL) {
		front->prev = temp;
	}

	front = temp; // load front with the address of temp
}

template<class T>
bool List<T>::FirstItem(T& item) { // item is changed through a pointer. item "returns" what is in front->data ie what is in the front of the list
	if (front == NULL) { return false; } //list is empty 
	item = front->data;
	current = front; // updates current pointer so that it points to what is in front of list
	return true;
}

template<class T>
bool List<T>::LastItem(T& item) {
	if (front == NULL) { return NULL; }
	item = rear->data;
	current = rear;
	return true;
}

template<class T>
bool List<T>::NextItem(T& item) {
	if (current == NULL) { return false; }
	current = current->next;
	if (current == NULL) { return false; }
	item = current->data;
	return true;
}

template<class T>
bool List<T>::PrevItem(T& item) {
	if (current == NULL) { return false; }
	current = current->prev;
	if (current == NULL) { return false; }
	item = current->data;
	return true;
}

template<class T>
bool List<T>::Reverse() {
	if (front == NULL) { return false; }
	Node* temp1, * temp2;
	temp2 = front;
	current = front->next;
	while (current != NULL) {
		temp1 = current->next;
		current->next = front;
		current->prev = temp1;
		front = current;
		current = temp1;
	}
	temp2->next = NULL;
	return true;
}

template<class T>
bool List<T>::MakeCopy(List& L) {
	if (front == NULL) { return false; }
	Node* temp;
	temp = front;
	while (temp != NULL) {
		L.AddtoFront(temp->data);
		temp = temp->next;
	}
	return true;
}

template<class T>
void List<T>::PrintList(List& L) {
	bool ok; int x;
	ok = L.FirstItem(x); // argument passed to this method is the address of x
	while (ok) { //while firstitem returns true ie front is not equal to NULL ie list is not empty
		printf("%d \n", x); //prints what firstitem method loaded into x through pointer argument in line 70
		ok = L.NextItem(x); // loads x with next item in list. ok is loaded with false if next item is null.
	}
}

template<class T>
void List<T>::PrintListReverse(List& L) {
	bool ok; int x;
	ok = L.LastItem(x);
	while (ok) {
		printf("%d \n", x);
		ok = L.PrevItem(x);
	}
}


/////// PART B
class BigNumber {
private:
	List<short> listofdigits;

public:
	//complete here...
	//what methods do you need?  
	BigNumber();
	~BigNumber();
	void ReadFromString(string decstring);
	void PrintBigNumber();
	void PrintBigNumberReverse();
	void AddBigNumbers(BigNumber B1, BigNumber B2);
};

BigNumber::BigNumber() {
	// anything here?

}

BigNumber::~BigNumber() {
	//you can keep that empty
}

void BigNumber::ReadFromString(string decstring) {
	//cout<< "testing string passing: "<< decstring << endl;
	  //read a string, adding a new node per digit of the decimal string
	  // To translate 'digits' to integers: myinteger=decstring[index]-48

	for (unsigned int i = 0; i < decstring.size(); i++) {
		if (decstring[i] != '\n' && decstring[i] != '\r') {
			int temp = decstring[i] - 48;
			listofdigits.AddtoFront(temp);
			//cout << "Digit " << i << " is " << temp << endl;  //Comment this out for your final version
			//You need to use the AddtoFront()
		}
	}
}

void BigNumber::PrintBigNumber() {
	//complete here, print the list (i.e., use FirstItem() and NextItem() )
	//remember that the print out may be inverted, depending on the order you enter the 'digits'
	short item;
	bool ok = listofdigits.LastItem(item);
	while (ok) {
		printf("%d", item);
		ok = listofdigits.PrevItem(item);
	}
	printf("\n");
}

void BigNumber::PrintBigNumberReverse() {
	short item;
	bool ok = listofdigits.FirstItem(item);
	while (ok) {
		printf("%d", item);
		ok = listofdigits.NextItem(item);
	}
	printf("\n");
}

void BigNumber::AddBigNumbers(BigNumber B1, BigNumber B2) {
	//complete here.
	//use FirstItem(), NextItem() and AddNode()
	//to add two big numbers, what do you have to do? Be careful about the carry
	//Remember to add the last carry, the resulting number can have one more digit than B1 or B2
	short num1, num2, carry = 0, res = 0;
	bool ok1, ok2;
	ok1 = B1.listofdigits.FirstItem(num1);
	ok2 = B2.listofdigits.FirstItem(num2);
	if (num1 + num2 > 9) {
		carry = 1;
		res = (num1 + num2) - 10;
	}
	else { res = num1 + num2; }
	listofdigits.AddtoFront(res);
	//printf("num1=%d num2=%d carry=%d res=%d ok1=%d ok2=%d\n", num1, num2, carry, res, ok1, ok2);

	ok1 = B1.listofdigits.NextItem(num1);
	ok2 = B2.listofdigits.NextItem(num2);
	while (ok1 || ok2) {
		if (!ok1) {
			num1 = 0;

		}
		else if (!ok2) {
			num2 = 0;

		}
		if (num1 + num2 + carry > 9) {
			res = (num1 + num2 + carry) - 10;
			carry = 1;
		}
		else {
			res = num1 + num2 + carry;
			carry = 0;
		}
		listofdigits.AddtoFront(res);
		//printf("num1=%d num2=%d carry=%d res=%d ok1=%d ok2=%d\n", num1, num2, carry, res, ok1, ok2);
		ok1 = B1.listofdigits.NextItem(num1);
		ok2 = B2.listofdigits.NextItem(num2);

	}
	if (carry > 0) {
		listofdigits.AddtoFront(carry);
		//printf("num1=%d num2=%d carry=%d res=%d ok1=%d ok2=%d\n", num1, num2, carry, res, ok1, ok2);
	}
}

/////// PART C

BigNumber B1, B2, RES;

int main(int argc, char** argv) {
	string numberstring;
	int stringseq = 0;
	ifstream input_file;
	if (argc == 2) input_file.open(argv[1]);
	else { cout << "cannot read the file " << argv[1] << endl; exit(0); }
	while (!input_file.eof()) {
		getline(input_file, numberstring);
		if (!input_file.eof()) {
			//cout << numberstring << endl;//Comment this out for your final version
			if (stringseq == 0) {
				B1.ReadFromString(numberstring);
				stringseq = 1;
			}
			else {
				B2.ReadFromString(numberstring);
			}
		}
	}
	//print
	B1.PrintBigNumber();//PROBLEM: Is the printing inverted? How can you solve this problem? Before or after using AddBigNumbers()?
	cout << "+" << endl;
	B2.PrintBigNumber();
	cout << "=" << endl;
	//compute the addition
	RES.AddBigNumbers(B1, B2);
	//print the result
	RES.PrintBigNumberReverse();
}
