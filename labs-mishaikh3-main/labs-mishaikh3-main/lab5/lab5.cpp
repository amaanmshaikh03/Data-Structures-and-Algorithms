#include <iostream>
#include <string>

template <typename T>
class Stack {
	T* sta;
	int maximum;
	int attop; 
	void grow() {
		T* temp = new T[maximum * 2];
		for (int i = 0;i < maximum;i++) {
			temp[i] = sta[i];
		}
		maximum *= 2;
		delete[] sta;
		sta = temp;
	}
public:
	Stack() {
		maximum = 50;
		sta = new T[maximum];
		attop = 0;
	}
	void push(const T& data) {
		if (attop == maximum) {
			grow();
		}
		sta[attop++] = data;
	}
	void pop() {
		if (attop > 0) {
			attop--;
		}
	}
	T top() const {
		return sta[attop - 1];
	}
	~Stack() {
		delete[] sta;
	}
};
bool bracketCheck(const std::string& s) {
	Stack<char>* stack = new Stack<char>();
	int a = 0;
	bool b = true;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
			stack->push(s[i]);
			a++;
		}
		else if (s[i] == ')' || s[i] == ']' || s[i] == '}') {
			if ((s[i] == ')' && stack->top() == '(') || (s[i] == ']' && stack->top() == '[') || (s[i] == '}' && stack->top() == '{')) {
				stack->pop();
				a--;
			}
			else {	
				b = false;
			}
		}
	}
	if (a != 0) {
		b = false;
	}
	return b;
}