#pragma once
#include "Matrix.h"

template <typename T>
class Queue
{
public:
	struct Element
	{
		T matrix;
		struct Element* next;
		friend class Queue;
	};
	Element* head;					// указатель на начало очереди
	Element* tail;					// указатель на конец очереди

	int size;						// текущее количество элементов в очереди

	// конструктор
	Queue()
	{
		static_assert(std::is_same<T, Matrix>::value, "Можно пока только матрицы!!!");
		head = tail = nullptr;
		size = 0;
	}

	// деструктор
	~Queue()
	{
		while (head != nullptr)
		{
			Element* temp = head;
			head = head->next;
			delete temp;
		}
	}

	// конструктор копирования
	Queue(const Queue<T>& object)	
	{
		try
		{
			head = tail = nullptr;
			Element* current = object.head;

			while (current != nullptr)
			{
				Element* newElement = new Element;
				
				newElement->matrix = current->matrix;
				newElement->next = nullptr;

				if (tail == nullptr)
				{
					head = tail = newElement;
				}
				else
				{
					tail->next = newElement;
					tail = newElement;
				}
				current = current->next;
			}
			size = object.size;
		}
		catch (const std::bad_alloc& e)
		{
			cout << e.what() << endl;

			while (head != nullptr)					// очистка созданных элементов (если есть)
			{
				Element* temp = head;
				head = head->next;
				delete temp;
			}

			size = 0;								// создать пустую очередь
			head = tail = nullptr;
		}
	}

	// проверка на наличие элементов в очереди
	bool isEmpty() const
	{
		return size == 0;
	}

	// получение количества элементов в очереди
	int queueSize() const			// определение количества элементов в очереди
	{
		return this->size;
	}

	// добавление элемента в конец
	bool enqueue(const T& mx)		
	{
		try
		{
			Element* newElement = new Element;		// создание нового элемента очереди

			newElement->matrix = mx;				// занесение матрицы
			newElement->next = nullptr;				// указатель на следующий указывает на 0


			if (isEmpty())
				head = newElement;					// если очередь пуста - элемент в начало очереди
			else
				tail->next = newElement;			// иначе в конец
			
			size++;

			tail = newElement;						// указатель конца на новую матрицу
			return true;
		}
		catch (const std::bad_alloc& e)
		{
			cout << e.what() << endl;
			return false;
		}
	}

	// удаление элемента из начала 
	bool dequeue()					
	{
		try
		{
			if (isEmpty())
				return false;

			Element* temp = head;
			head = head->next;

			if (isEmpty())
				tail = nullptr;

			delete temp;
			size--;
			return true;
		}
		catch (const std::exception& e)
		{
			cout << e.what() << endl;
			return false;
		}
	}

	// взятие без удаления
	T getObject() const			
	{
		if (head != nullptr)
			return head->matrix;
		else
			return T();
	}

	// вывод всех элементов в очереди
	void print(std::ostream& os) const
	{
		Element* current = head;
		while (current)
		{
			os << current->matrix;
			current = current->next;
		}
	}

	// перегрузки вывода и ввода
	friend std::ostream& operator<<(std::ostream& os, const Queue<T>& queue)
	{
		queue.print(std::cout);
		return os;
	}
	friend std::istream& operator>>(std::istream& is, Queue<T>& queue)
	{
		int queueSize;
		cout << "Введите количество элементов в очереди:" << endl;
		is >> queueSize;

		for (int i = 0; i < queueSize; i++)
		{
			T elem;
			is >> elem;
			queue.enqueue(elem);
		}
		return is;
	}
};

