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
    // �������� ����������� � �������� ������
    cv::Mat image = cv::imread("input4.jpg", cv::IMREAD_GRAYSCALE);
    if (image.empty())
    {
        std::cout << "�� ������� ��������� �����������" << std::endl;
        return 1;
    }

    // ��������� ������ � ������
    int height = image.rows;
    int width = image.cols;

    // ����� ������� ��� ���������������� ����������� (�������� �������� 0-255)
    cv::Mat binarImage(height, width, CV_8U);

    int S = width / 2;
    int s2 = S / 2;
    float t = 0.01;
    unsigned long* integralImg = 0;
    int sum = 0;
    int count = 0;
    int index;
    int x1, y1, x2, y2;

    // ������ ������������� �����������
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

    // ������� ��� ��������� ��������
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


    // ������ ���������� ������� �������
    std::vector<objFeatures> objects;
    // ��������� ������ ���������� ��������
    std::vector<std::vector<bool>> visited(height, std::vector<bool>(width, false));
    // �������� ��� ����������� �� �������� �������� (��� P)
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
                // ���� ��������
                std::vector<std::pair<int, int>> stack;
                stack.push_back(std::make_pair(i, j));  // ���������� �������� �������

                while (!stack.empty())
                {
                    // ��������� ������� ������� ����� (��� ����������)
                    int x = stack.back().first;
                    int y = stack.back().second;
                    // ������� ���
                    stack.pop_back();
                    // ����� ��������� �� ������� ��� ��� �������� - ������� ��������
                    if (x < 0 || x >= height || y < 0 || y >= width || visited[x][y])
                        continue;
                    // �������� ������� ������� ��� ����������
                    visited[x][y] = true;
                    // ���� �������� �������� ������� 0
                    if (binarImage.at<uchar>(i, j) == 0)
                    {
                        // ���������� �������
                        features.S++;
                        // ������� ���������
                        for (int k = 0; k < 4; ++k)
                        {
                            // ������� ������� ��������� �������
                            int nx = x + dx[k];
                            int ny = y + dy[k];
                            // ���� �� ��������� ����������� ��� � ������� �������� 255 - +1 � ��������� (������� ���, ��� ���� ������ ������������)
                            if (nx < 0 || nx >= height || ny < 0 || ny >= width || binarImage.at<uchar>(nx, ny) == 255)
                                features.P++;
                            // � �������� ����������� � ������� == 255 � �� ������� - ������� � ���� (����� ����� ������ ��� �������)
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
        std::cout << i + 1 << " ������ " << std::endl;
        std::cout << "�������: " << objects[i].S << std::endl;
        std::cout << "��������: " << objects[i].P << std::endl;
        std::cout << "������������: " << objects[i].C << std::endl << std::endl;
    }

    cv::imwrite("output.jpg", binarImage);                     // ���������� ������ �����������

    cv::Mat combinedImage;
    cv::vconcat(image, binarImage, combinedImage);              // ������������ ����������� �����������
    cv::namedWindow("Combined Image", cv::WINDOW_NORMAL);       // �������� ����
    cv::imshow("Combined Image", combinedImage);                // ����� �����������
    cv::waitKey(0);                                             // �������� ������� �������


    return 0;
}