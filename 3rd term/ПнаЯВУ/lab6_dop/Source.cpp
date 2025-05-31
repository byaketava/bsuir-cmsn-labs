#include <opencv2/opencv.hpp>
#include <vector>

int main() 
{
    setlocale(0, "");
    // загрузка изображения в оттенках серого
    cv::Mat image = cv::imread("input2.jpg", cv::IMREAD_GRAYSCALE);
    if (image.empty()) 
    {
        std::cout << "Не удалось загрузить изображение" << std::endl;
        return 1;
    }

    // получение ширины и высоты
    int height = image.rows;
    int width = image.cols;

    // новая матрица для отфильтрованного изображения (значения пикселей 0-255)
    cv::Mat filteredImage(height, width, CV_8U);

    // оператор Собеля
    std::vector<std::vector<int>> sobelX = { {-1,  0,  1},
                                             {-2,  0,  2},
                                             {-1,  0,  1} };
 
    std::vector<std::vector<int>> sobelY = { {-1, -2, -1},
                                             { 0,  0,  0},
                                             { 1,  2,  1} };

    // применение оператора Собеля
    for (int y = 1; y < height - 1; ++y) 
    {
        for (int x = 1; x < width - 1; ++x) 
        {
            int pixelX = 0;
            int pixelY = 0;

            // применение для всей матрицы вокруг одного пикселя
            for (int i = -1; i <= 1; ++i) 
            {
                for (int j = -1; j <= 1; ++j) 
                {
                    pixelX += image.at<uchar>(y + i, x + j) * sobelX[i + 1][j + 1];
                    pixelY += image.at<uchar>(y + i, x + j) * sobelY[i + 1][j + 1];
                }
            }

            int gradient = std::sqrt(pixelX * pixelX + pixelY * pixelY);    // вычисление градиента
            gradient = std::min(255, std::max(0, gradient));                // ограничение значения градиента в диапазоне от 0 до 255
            filteredImage.at<uchar>(y, x) = gradient;                       // запись значения в отфильтрованное изображение
        }
    }

    cv::imwrite("output.jpg", filteredImage);                  // сохранение нового изображения

    cv::Mat combinedImage;
    cv::vconcat(image, filteredImage, combinedImage);           // вертикальное объединение изображений
    cv::namedWindow("Combined Image", cv::WINDOW_NORMAL);     // создание окна
    cv::imshow("Combined Image", combinedImage);                // вывод изображения
    cv::waitKey(0);                                             // ожидание нажатия клавиши

    return 0;
}

/*#include <opencv2/opencv.hpp>
#include <vector>

int main()
{
    setlocale(0, "");
    // загрузка изображения в цвете
    cv::Mat image = cv::imread("input2.jpg", cv::IMREAD_COLOR);
    if (image.empty())
    {
        std::cout << "Не удалось загрузить изображение" << std::endl;
        return 1;
    }

    // получение ширины и высоты
    int height = image.rows;
    int width = image.cols;

    // новая матрица для отфильтрованного изображения (значения пикселей 0-255, 3 канала)
    cv::Mat filteredImage(height, width, CV_8UC3);

    // оператор Собеля
    std::vector<std::vector<int>> sobelX = { {-1,  0,  1},
                                             {-2,  0,  2},
                                             {-1,  0,  1} };

    std::vector<std::vector<int>> sobelY = { {-1, -2, -1},
                                             { 0,  0,  0},
                                             { 1,  2,  1} };


    // Применение оператора Собеля к каждому каналу цвета
    for (int y = 1; y < height - 1; y++)
    {
        for (int x = 1; x < width - 1; x++)
        {
            cv::Vec3i pixelX(0, 0, 0);
            cv::Vec3i pixelY(0, 0, 0);

            // Применение оператора Собеля в каждом канале
            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    pixelX += image.at<cv::Vec3b>(y + i, x + j) * sobelX[i + 1][j + 1];
                    pixelY += image.at<cv::Vec3b>(y + i, x + j) * sobelY[i + 1][j + 1];
                }
            }

            // вычисление градиента
            cv::Vec3i gradient = cv::Vec3i(std::sqrt(pixelX[0] * pixelX[0] + pixelY[0] * pixelY[0]),
                std::sqrt(pixelX[1] * pixelX[1] + pixelY[1] * pixelY[1]),
                std::sqrt(pixelX[2] * pixelX[2] + pixelY[2] * pixelY[2]));
            // ограничение значения градиента в диапазоне от 0 до 255
            gradient[0] = std::min(255, std::max(0, gradient[0]));
            gradient[1] = std::min(255, std::max(0, gradient[1]));
            gradient[2] = std::min(255, std::max(0, gradient[2]));
            // запись значения в отфильтрованное изображение
            filteredImage.at<cv::Vec3b>(y, x) = gradient;
        }
    }

    cv::imwrite("output5.jpg", filteredImage);                  // сохранение нового изображения

    cv::Mat combinedImage;
    cv::vconcat(image, filteredImage, combinedImage);           // вертикальное объединение изображений
    cv::namedWindow("Combined Image", cv::WINDOW_NORMAL);       // создание окна
    cv::imshow("Combined Image", combinedImage);                // вывод изображения
    cv::waitKey(0);                                             // ожидание нажатия клавиши

    return 0;
}*/


//#include <iostream>
//#include <fstream>
//#include <vector>
//
//using namespace std;
//
//// оператор Собеля
//void Sobel(const vector<unsigned char>& image, int width, int height, vector<unsigned char>& filteredImage) 
//{
//    // матрицы Собеля
//    int sobelX[3][3] = { {-1,  0,  1}, 
//                         {-2,  0,  2}, 
//                         {-1,  0,  1} };
//    int sobelY[3][3] = { {-1, -2, -1}, 
//                         { 0,  0,  0}, 
//                         { 1,  2,  1} };
//
//    // применение оператора Собеля к каждому пикселю
//    for (int y = 1; y < height - 1; ++y)
//    {
//        for (int x = 1; x < width - 1; ++x) 
//        {
//            int gx = 0;
//            int gy = 0;
//            // вычисление градиентов по X и Y 
//            for (int j = -1; j <= 1; j++) 
//            {
//                for (int i = -1; i <= 1; i++) 
//                {
//                   gx += sobelX[j + 1][i + 1] * image[(y + j) * width + (x + i)];
//                   gy += sobelY[j + 1][i + 1] * image[(y + j) * width + (x + i)];
//                }
//            }
//
//            // Вычисление аппроксимированного модуля градиента
//            int magnitude = sqrt(gx * gx + gy * gy);
//
//            // Ограничение значения аппроксимированного модуля градиента в диапазоне [0, 255]
//            magnitude = min(255, max(0, magnitude));
//
//            // Запись отфильтрованного пикселя в выходной массив
//            filteredImage[y * width + x] = magnitude;
//        }
//    }
//}
//
//int main()
//{
//    setlocale(0, "");
//
//    string inputFile  = "input2.jpg";
//    string outputFile = "output.jpg";
//
//    // открытие файла
//    ifstream input(inputFile, ios::binary | ios::ate);
//    if (!input)
//    {
//        cout << "Не удалось открыть файл " << inputFile << endl;
//        return 1;
//    }
//
//    // получение размеров изображения
//    streamsize fileSize = input.tellg();                                // получение текущей позиции, т.е. размера файла    
//    input.seekg(0, ios::beg);                                           // позиция перемещается в начало
//    vector<unsigned char> idata(fileSize);
//    if (!input.read(reinterpret_cast<char*>(idata.data()), fileSize))   // reinterpret_cast<char*> для временного обхода ограничений .read
//    {
//        cout << "Ошибка при чтении " << inputFile << endl;
//        return 1;
//    }       
//    input.close();
//
//    // ширина и высота изображения
//    int width = 0;
//    int height = 0;
//    int flag = 0;
//    // проверка формата файла (чтобы был JPEG)
//    if (idata[0] == 0xFF && idata[1] == 0xD8 &&                     // маркеры начала изображения
//        idata[fileSize - 2] == 0xFF && idata[fileSize - 1] == 0xD9) // маркеры конца изображения 
//    {
//        // Извлечение ширины и высоты из заголовка JPEG
//        unsigned int i = 2;                                         // т.к. 0 и 1 маркеры начала
//        while (i < fileSize - 1)                                    // т.к. последний и предпоследний маркеры конца
//        {
//            if (idata[i] == 0xFF && idata[i + 1] == 0xC0)           // маркер начала кадра
//            {
//                height = idata[i + 5] * 256 + idata[i + 6];
//                width = idata[i + 7] * 256 + idata[i + 8];
//                flag = i;
//                break;
//            }
//            else
//                i += 2;
//                //i = i + 2 + idata[i + 2] * 256 + idata[i + 3];         // перемещение к следующему маркеру
//        }
//    }
//
//    if (width == 0 || height == 0) 
//    {
//        cout << "Ошибка определения ширины и высоты" << endl;
//        return 1;
//    }
//
//    // массив для конечного изображения
//    vector<unsigned char> Image(width * height);
//
//    // оператор Собеля
//    Sobel(idata, width, height, Image);
//
//    // запись изображения в выходной файл
//    ofstream output(outputFile, ios::binary);
//
//    if (!output) 
//    {
//        cout << "Не удалось открыть файл " << outputFile << endl;
//        return 1;
//    }
//
//    // запись заголовка для JPEG
//    // маркер начала файла
//    output.write(reinterpret_cast<const char*>(idata.data()), 2);
//    // маркер начала кадра
//    output.put(0xFF);
//    output.put(0xC0);
//    //// параметры изображения
//    //output.put(0x00);
//    //output.put(0x11);
//    //output.put(0x08);
//    // значения высоты
//    output.put((height >> 8) & 0xFF);
//    output.put(height & 0xFF);
//    // значения ширины
//    output.put((width >> 8) & 0xFF);
//    output.put(width & 0xFF);
//    //// ещё параметры изображения
//    //output.put(0x03);
//    //output.put(0x01);
//    //output.put(0x11);
//    //output.put(0x00);
//
//    // запись данных
//    output.write(reinterpret_cast<const char*>(Image.data()), Image.size());
//
//    // маркер конца
//    output.put(0xFF);
//    output.put(0xD9);
//    output.close();
//
//    cout << "Изображение сохранено в " << outputFile << std::endl;
//    return 0;
//}