#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>

struct objFeatures
{
    int P;
    int S;
    double C;
};

int main()
{
    setlocale(0, "");
    // загрузка изображени€ в оттенках серого
    cv::Mat image = cv::imread("input4.jpg", cv::IMREAD_GRAYSCALE);
    if (image.empty())
    {
        std::cout << "Ќе удалось загрузить изображение" << std::endl;
        return 1;
    }

    // получение ширины и высоты
    int height = image.rows;
    int width = image.cols;

    // нова€ матрица дл€ отфильтрованного изображени€ (значени€ пикселей 0-255)
    cv::Mat binarImage(height, width, CV_8U);

    int S = width / 2;
    int s2 = S / 2;
    float t = 0.01;
    unsigned long* integralImg = 0;
    int sum = 0;
    int count = 0;
    int index;
    int x1, y1, x2, y2;

    // расчЄт интегрального изображени€
    integralImg = new unsigned long[height * width * sizeof(unsigned long*)];

    for (int i = 0; i < width; i++)
    {
        sum = 0;
        for (int j = 0; j < height; j++)
        {
            index = j * width + i;
            sum += image.at<uchar>(index);
            if (i == 0)
                integralImg[index] = sum;
            else
                integralImg[index] = integralImg[index - 1] + sum;
        }
    }

    // границы дл€ локальных областей
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            index = j * width + i;

            x1 = i - s2;
            x2 = i + s2;
            y1 = j - s2;
            y2 = j + s2;

            if (x1 < 0)
                x1 = 0;
            if (x2 >= width)
                x2 = width - 1;
            if (y1 < 0)
                y1 = 0;
            if (y2 >= height)
                y2 = height - 1;

            count = (x2 - x1) * (y2 - y1);

            sum = integralImg[y2 * width + x2] - integralImg[y1 * width + x2] -
                integralImg[y2 * width + x1] + integralImg[y1 * width + x1];
            if ((long)(image.at<uchar>(index) * count) <
                (long)(sum * (1.0 - t)))
                binarImage.at<uchar>(index) = 0;
            else
                binarImage.at<uchar>(index) = 255;
        }
    }

    delete[] integralImg;


    // массив параметров каждого объекта
    std::vector<objFeatures> objects;
    // двумерный вектор посещЄнных пикселей
    std::vector<std::vector<bool>> visited(height, std::vector<bool>(width, false));
    // смещени€ дл€ перемещени€ по соседним пиксел€м (дл€ P)
    int dx[] = { -1, 0, 1, 0 };
    int dy[] = { 0, -1, 0, 1 };

    for (int i = 0; i < height; ++i)
    {
        for (int j =0; j < width; ++j)
        {
            if (binarImage.at<uchar>(i, j) == 0 && !visited[i][j])
            {
                objFeatures features;
                features.P = 0;
                features.S = 0;
                // стек пикселей
                std::vector<std::pair<int, int>> stack;
                stack.push_back(std::make_pair(i, j));  // координаты текущего пиксел€

                while (!stack.empty())
                {
                    // извлекаем верхний элемент стека (его координаты)
                    int x = stack.back().first;
                    int y = stack.back().second;
                    // удал€ем его
                    stack.pop_back();
                    // выход координат за пределы или уже посещены - пропуск итерации
                    if (x < 0 || x >= height || y < 0 || y >= width || visited[x][y])
                        continue;
                    // помечаем текущий пиксель как посещЄнный
                    visited[x][y] = true;
                    // если значение текущего пиксел€ 0
                    if (binarImage.at<uchar>(i, j) == 0)
                    {
                        // увеличение площади
                        features.S++;
                        // подсчЄт периметра
                        for (int k = 0; k < 4; ++k)
                        {
                            // перебор каждого соседнего пиксел€
                            int nx = x + dx[k];
                            int ny = y + dy[k];
                            // если за пределами изображени€ или у пиксел€ значение 255 - +1 к периметру (граница там, где есть пустое пространство)
                            if (nx < 0 || nx >= height || ny < 0 || ny >= width || binarImage.at<uchar>(nx, ny) == 255)
                                features.P++;
                            // в пределах изображени€ и пиксель == 255 и не посещЄн - пиксель в стек (чтобы потом обойти его соседей)
                            else if (!visited[nx][ny])
                                stack.push_back(std::make_pair(nx, ny));
                        }
                    }
                }
                if (features.S <= 3)
                    continue;
                features.C = (features.P * features.P) / (4.0 * 3.14 * features.S);
                objects.push_back(features);
            }
        }
    } 
    
    for (int i = 0; i < objects.size(); ++i)
    {
        std::cout << i + 1 << " ќЅЏ≈ “ " << std::endl;
        std::cout << "ѕлощадь: " << objects[i].S << std::endl;
        std::cout << "ѕериметр: " << objects[i].P << std::endl;
        std::cout << " омпактность: " << objects[i].C << std::endl << std::endl;
    }

    cv::imwrite("output.jpg", binarImage);                     // сохранение нового изображени€

    cv::Mat combinedImage;
    cv::vconcat(image, binarImage, combinedImage);              // вертикальное объединение изображений
    cv::namedWindow("Combined Image", cv::WINDOW_NORMAL);       // создание окна
    cv::imshow("Combined Image", combinedImage);                // вывод изображени€
    cv::waitKey(0);                                             // ожидание нажати€ клавиши


    return 0;
}