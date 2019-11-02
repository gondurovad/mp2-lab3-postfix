#ifndef __STACK_H__
#define __STACK_H__

const int MaxStackSize = 100;

template <class T>
class TStack
{
	T* pMem; //указатель на массив элементов
	int size; //длина стека
	int top; //вершина стека

public:
	TStack(int _size)
	{
		size = _size;
		top = -1;
		if ((size < 1) || (size > MaxStackSize))
			throw "size";
		pMem = new T[size];
	}/*-----------------------------------------------------------*/

	TStack(const TStack& st) //конструктор копирования
	{
		size = st.size;
		pMem = new T[size];
		for (int i = 0; i < size; i++) {
			pMem[i] = st.pMem[i];
		}
	}/*-----------------------------------------------------------*/

	~TStack()
	{
		delete[] pMem;
	}/*-----------------------------------------------------------*/

	void Push(const T& val) //добавление элемента
	{
		if (IsFull()) throw "full";
		pMem[++top] = val;
	}/*-----------------------------------------------------------*/

	T Pop(void) //удаление элемента
	{
		if (IsEmpty()) throw "empty";
		return pMem[top--];
	}/*-----------------------------------------------------------*/

	bool IsEmpty() //проверка на пустоту
	{
		return top == -1;
	}/*-----------------------------------------------------------*/

	bool IsFull() //проверка на полноту
	{
		return top == size;
	}
};

#endif
