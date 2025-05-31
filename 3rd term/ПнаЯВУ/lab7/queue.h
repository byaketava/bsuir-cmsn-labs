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
	Element* head;					// ��������� �� ������ �������
	Element* tail;					// ��������� �� ����� �������

	int size;						// ������� ���������� ��������� � �������

	// �����������
	Queue()
	{
		static_assert(std::is_same<T, Matrix>::value, "����� ���� ������ �������!!!");
		head = tail = nullptr;
		size = 0;
	}

	// ����������
	~Queue()
	{
		while (head != nullptr)
		{
			Element* temp = head;
			head = head->next;
			delete temp;
		}
	}

	// ����������� �����������
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

			while (head != nullptr)					// ������� ��������� ��������� (���� ����)
			{
				Element* temp = head;
				head = head->next;
				delete temp;
			}

			size = 0;								// ������� ������ �������
			head = tail = nullptr;
		}
	}

	// �������� �� ������� ��������� � �������
	bool isEmpty() const
	{
		return size == 0;
	}

	// ��������� ���������� ��������� � �������
	int queueSize() const			// ����������� ���������� ��������� � �������
	{
		return this->size;
	}

	// ���������� �������� � �����
	bool enqueue(const T& mx)		
	{
		try
		{
			Element* newElement = new Element;		// �������� ������ �������� �������

			newElement->matrix = mx;				// ��������� �������
			newElement->next = nullptr;				// ��������� �� ��������� ��������� �� 0


			if (isEmpty())
				head = newElement;					// ���� ������� ����� - ������� � ������ �������
			else
				tail->next = newElement;			// ����� � �����
			
			size++;

			tail = newElement;						// ��������� ����� �� ����� �������
			return true;
		}
		catch (const std::bad_alloc& e)
		{
			cout << e.what() << endl;
			return false;
		}
	}

	// �������� �������� �� ������ 
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

	// ������ ��� ��������
	T getObject() const			
	{
		if (head != nullptr)
			return head->matrix;
		else
			return T();
	}

	// ����� ���� ��������� � �������
	void print(std::ostream& os) const
	{
		Element* current = head;
		while (current)
		{
			os << current->matrix;
			current = current->next;
		}
	}

	// ���������� ������ � �����
	friend std::ostream& operator<<(std::ostream& os, const Queue<T>& queue)
	{
		queue.print(std::cout);
		return os;
	}
	friend std::istream& operator>>(std::istream& is, Queue<T>& queue)
	{
		int queueSize;
		cout << "������� ���������� ��������� � �������:" << endl;
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

