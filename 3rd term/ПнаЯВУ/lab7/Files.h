#pragma once
#include "Header.h"
#include <fstream>
#include <string>
#include "queue.h"

template<typename T>
class File 
{
private:
    std::string filename;
public:
    File(const std::string& filename): filename(filename) {}    
   
    void RemoveKMatrix(int k)
    {
        std::ifstream inputFile(filename);
        if (!inputFile.is_open())
        {
            cout << "Ошибка открытия файла." << endl;
            return;
        }

        std::string tempFilename = "temp.txt";
        std::ofstream tempFile(tempFilename);
        if (!tempFile.is_open())
        {
            cout << "Ошибка открытия файла." << endl;
            inputFile.close();
            return;
        }

        std::string line;
        std::string deleteFrom = std::to_string(k) + " matrix:";
        std::string deleteBy = std::to_string(k + 1) + " matrix:";

        bool flagNotFound = true;
        while (std::getline(inputFile, line))
        {
            if (line.find(deleteFrom) == std::string::npos)
            {
                tempFile << line << endl;
            }
            else
            {
                flagNotFound = false;
                while (line != deleteBy)
                {
                    std::getline(inputFile, line);
                    if (inputFile.eof())
                    {
                        break;
                    }
                }
                tempFile << line << endl;
            }
        }

        inputFile.close();
        tempFile.close();

        if (std::remove(filename.c_str()) != 0)
        {
            cout << "Ошибка удаления файла " << filename << endl;
            return;
        }
        if (std::rename(tempFilename.c_str(), filename.c_str()) != 0)
        {
            cout << "Ошибка переименовывания файла " << endl;
        }
        if (flagNotFound)
        {
            cout << "\nМатрицы с таким порядковым номером не найдено.\n" << endl;
        }
        else
        {
            cout << "\nМатрица успешно удалена!\n" << endl;
        }
    }

    friend std::ostream& operator>>(File& file, const Queue<T>& queue)
    {
        std::ofstream outputFile(file.filename, std::ios::app);
        if (outputFile.is_open())
        {
            int i = 1;
            typename Queue<T>::Element* current = queue.head;
            while (current != nullptr)
            {
                outputFile << i << " matrix:\n";
                outputFile << current->matrix;
                current = current->next;
                i++;
            }
            outputFile.close();
        }
        else
        {
            cout << "Ошибка открытия файла." << std::endl;
        }       
        return outputFile;
    }
    friend std::ostream& operator<<(std::ostream& os, const File& file)
    {
        std::ifstream input(file.filename, std::ios::in);
        if (input.is_open()) 
        {
            std::string line;
            while (std::getline(input, line)) 
            {
                os << line << std::endl;
            }
            input.close();
        }
        else 
        {
            os << "Ошибка открытия файла." << file.filename << std::endl;
        }
        return os;
    }
};