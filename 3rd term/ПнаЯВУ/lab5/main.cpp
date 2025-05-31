//#include <iostream>
//#include <queue>
//
//template<typename T>
//class Queue 
//{
//private:
//    std::queue<T> data;
//public:
//    void enqueue(const T& item) 
//    {
//        data.push(item);
//    }
//
//    T dequeue() 
//    {
//        T item = data.front();
//        data.pop();
//        return item;
//    }
//
//    bool isEmpty() const 
//    {
//        return data.empty();
//    }
//
//    friend std::ostream& operator<<(std::ostream& os, const Queue<T>& queue) 
//    {
//        os << "Queue: ";
//        std::queue<T> temp = queue.data;
//        while (!temp.empty()) {
//            os << temp.front() << " ";
//            temp.pop();
//        }
//        return os;
//    }
//
//    friend std::istream& operator>>(std::istream& is, Queue<T>& queue) 
//    {
//        T item;
//        is >> item;
//        queue.enqueue(item);
//        return is;
//    }
//};
//
//// Предположим, что можно использовать только матрицы целых чисел
//int main() 
//{
//    Queue<std::vector<int>> matrixQueue;
//
//    std::vector<int> matrix1 = { 1, 2, 3 };
//    std::vector<int> matrix2 = { 4, 5, 6 };
//    std::vector<int> matrix3 = { 7, 8, 9 };
//
//    matrixQueue.enqueue(matrix1);
//    matrixQueue.enqueue(matrix2);
//    matrixQueue.enqueue(matrix3);
//
//    std::cout << matrixQueue << std::endl;
//
//    std::cout << "Dequeued matrix: "  << matrixQueue.dequeue() << std::endl;
//    std::cout << matrixQueue << std::endl;
//
//    return 0;
//}

#include"Header.h"

int main()
{
	srand((unsigned int)time(NULL));
	setlocale(0, "");
	menu();
	return 0;
}