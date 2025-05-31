#include <opencv2/opencv.hpp>
#include <vector>

int main() 
{
    setlocale(0, "");
    // �������� ����������� � �������� ������
    cv::Mat image = cv::imread("input2.jpg", cv::IMREAD_GRAYSCALE);
    if (image.empty()) 
    {
        std::cout << "�� ������� ��������� �����������" << std::endl;
        return 1;
    }

    // ��������� ������ � ������
    int height = image.rows;
    int width = image.cols;

    // ����� ������� ��� ���������������� ����������� (�������� �������� 0-255)
    cv::Mat filteredImage(height, width, CV_8U);

    // �������� ������
    std::vector<std::vector<int>> sobelX = { {-1,  0,  1},
                                             {-2,  0,  2},
                                             {-1,  0,  1} };
 
    std::vector<std::vector<int>> sobelY = { {-1, -2, -1},
                                             { 0,  0,  0},
                                             { 1,  2,  1} };

    // ���������� ��������� ������
    for (int y = 1; y < height - 1; ++y) 
    {
        for (int x = 1; x < width - 1; ++x) 
        {
            int pixelX = 0;
            int pixelY = 0;

            // ���������� ��� ���� ������� ������ ������ �������
            for (int i = -1; i <= 1; ++i) 
            {
                for (int j = -1; j <= 1; ++j) 
                {
                    pixelX += image.at<uchar>(y + i, x + j) * sobelX[i + 1][j + 1];
                    pixelY += image.at<uchar>(y + i, x + j) * sobelY[i + 1][j + 1];
                }
            }

            int gradient = std::sqrt(pixelX * pixelX + pixelY * pixelY);    // ���������� ���������
            gradient = std::min(255, std::max(0, gradient));                // ����������� �������� ��������� � ��������� �� 0 �� 255
            filteredImage.at<uchar>(y, x) = gradient;                       // ������ �������� � ��������������� �����������
        }
    }

    cv::imwrite("output.jpg", filteredImage);                  // ���������� ������ �����������

    cv::Mat combinedImage;
    cv::vconcat(image, filteredImage, combinedImage);           // ������������ ����������� �����������
    cv::namedWindow("Combined Image", cv::WINDOW_NORMAL);     // �������� ����
    cv::imshow("Combined Image", combinedImage);                // ����� �����������
    cv::waitKey(0);                                             // �������� ������� �������

    return 0;
}

/*#include <opencv2/opencv.hpp>
#include <vector>

int main()
{
    setlocale(0, "");
    // �������� ����������� � �����
    cv::Mat image = cv::imread("input2.jpg", cv::IMREAD_COLOR);
    if (image.empty())
    {
        std::cout << "�� ������� ��������� �����������" << std::endl;
        return 1;
    }

    // ��������� ������ � ������
    int height = image.rows;
    int width = image.cols;

    // ����� ������� ��� ���������������� ����������� (�������� �������� 0-255, 3 ������)
    cv::Mat filteredImage(height, width, CV_8UC3);

    // �������� ������
    std::vector<std::vector<int>> sobelX = { {-1,  0,  1},
                                             {-2,  0,  2},
                                             {-1,  0,  1} };

    std::vector<std::vector<int>> sobelY = { {-1, -2, -1},
                                             { 0,  0,  0},
                                             { 1,  2,  1} };


    // ���������� ��������� ������ � ������� ������ �����
    for (int y = 1; y < height - 1; y++)
    {
        for (int x = 1; x < width - 1; x++)
        {
            cv::Vec3i pixelX(0, 0, 0);
            cv::Vec3i pixelY(0, 0, 0);

            // ���������� ��������� ������ � ������ ������
            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    pixelX += image.at<cv::Vec3b>(y + i, x + j) * sobelX[i + 1][j + 1];
                    pixelY += image.at<cv::Vec3b>(y + i, x + j) * sobelY[i + 1][j + 1];
                }
            }

            // ���������� ���������
            cv::Vec3i gradient = cv::Vec3i(std::sqrt(pixelX[0] * pixelX[0] + pixelY[0] * pixelY[0]),
                std::sqrt(pixelX[1] * pixelX[1] + pixelY[1] * pixelY[1]),
                std::sqrt(pixelX[2] * pixelX[2] + pixelY[2] * pixelY[2]));
            // ����������� �������� ��������� � ��������� �� 0 �� 255
            gradient[0] = std::min(255, std::max(0, gradient[0]));
            gradient[1] = std::min(255, std::max(0, gradient[1]));
            gradient[2] = std::min(255, std::max(0, gradient[2]));
            // ������ �������� � ��������������� �����������
            filteredImage.at<cv::Vec3b>(y, x) = gradient;
        }
    }

    cv::imwrite("output5.jpg", filteredImage);                  // ���������� ������ �����������

    cv::Mat combinedImage;
    cv::vconcat(image, filteredImage, combinedImage);           // ������������ ����������� �����������
    cv::namedWindow("Combined Image", cv::WINDOW_NORMAL);       // �������� ����
    cv::imshow("Combined Image", combinedImage);                // ����� �����������
    cv::waitKey(0);                                             // �������� ������� �������

    return 0;
}*/


//#include <iostream>
//#include <fstream>
//#include <vector>
//
//using namespace std;
//
//// �������� ������
//void Sobel(const vector<unsigned char>& image, int width, int height, vector<unsigned char>& filteredImage) 
//{
//    // ������� ������
//    int sobelX[3][3] = { {-1,  0,  1}, 
//                         {-2,  0,  2}, 
//                         {-1,  0,  1} };
//    int sobelY[3][3] = { {-1, -2, -1}, 
//                         { 0,  0,  0}, 
//                         { 1,  2,  1} };
//
//    // ���������� ��������� ������ � ������� �������
//    for (int y = 1; y < height - 1; ++y)
//    {
//        for (int x = 1; x < width - 1; ++x) 
//        {
//            int gx = 0;
//            int gy = 0;
//            // ���������� ���������� �� X � Y 
//            for (int j = -1; j <= 1; j++) 
//            {
//                for (int i = -1; i <= 1; i++) 
//                {
//                   gx += sobelX[j + 1][i + 1] * image[(y + j) * width + (x + i)];
//                   gy += sobelY[j + 1][i + 1] * image[(y + j) * width + (x + i)];
//                }
//            }
//
//            // ���������� ������������������� ������ ���������
//            int magnitude = sqrt(gx * gx + gy * gy);
//
//            // ����������� �������� ������������������� ������ ��������� � ��������� [0, 255]
//            magnitude = min(255, max(0, magnitude));
//
//            // ������ ���������������� ������� � �������� ������
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
//    // �������� �����
//    ifstream input(inputFile, ios::binary | ios::ate);
//    if (!input)
//    {
//        cout << "�� ������� ������� ���� " << inputFile << endl;
//        return 1;
//    }
//
//    // ��������� �������� �����������
//    streamsize fileSize = input.tellg();                                // ��������� ������� �������, �.�. ������� �����    
//    input.seekg(0, ios::beg);                                           // ������� ������������ � ������
//    vector<unsigned char> idata(fileSize);
//    if (!input.read(reinterpret_cast<char*>(idata.data()), fileSize))   // reinterpret_cast<char*> ��� ���������� ������ ����������� .read
//    {
//        cout << "������ ��� ������ " << inputFile << endl;
//        return 1;
//    }       
//    input.close();
//
//    // ������ � ������ �����������
//    int width = 0;
//    int height = 0;
//    int flag = 0;
//    // �������� ������� ����� (����� ��� JPEG)
//    if (idata[0] == 0xFF && idata[1] == 0xD8 &&                     // ������� ������ �����������
//        idata[fileSize - 2] == 0xFF && idata[fileSize - 1] == 0xD9) // ������� ����� ����������� 
//    {
//        // ���������� ������ � ������ �� ��������� JPEG
//        unsigned int i = 2;                                         // �.�. 0 � 1 ������� ������
//        while (i < fileSize - 1)                                    // �.�. ��������� � ������������� ������� �����
//        {
//            if (idata[i] == 0xFF && idata[i + 1] == 0xC0)           // ������ ������ �����
//            {
//                height = idata[i + 5] * 256 + idata[i + 6];
//                width = idata[i + 7] * 256 + idata[i + 8];
//                flag = i;
//                break;
//            }
//            else
//                i += 2;
//                //i = i + 2 + idata[i + 2] * 256 + idata[i + 3];         // ����������� � ���������� �������
//        }
//    }
//
//    if (width == 0 || height == 0) 
//    {
//        cout << "������ ����������� ������ � ������" << endl;
//        return 1;
//    }
//
//    // ������ ��� ��������� �����������
//    vector<unsigned char> Image(width * height);
//
//    // �������� ������
//    Sobel(idata, width, height, Image);
//
//    // ������ ����������� � �������� ����
//    ofstream output(outputFile, ios::binary);
//
//    if (!output) 
//    {
//        cout << "�� ������� ������� ���� " << outputFile << endl;
//        return 1;
//    }
//
//    // ������ ��������� ��� JPEG
//    // ������ ������ �����
//    output.write(reinterpret_cast<const char*>(idata.data()), 2);
//    // ������ ������ �����
//    output.put(0xFF);
//    output.put(0xC0);
//    //// ��������� �����������
//    //output.put(0x00);
//    //output.put(0x11);
//    //output.put(0x08);
//    // �������� ������
//    output.put((height >> 8) & 0xFF);
//    output.put(height & 0xFF);
//    // �������� ������
//    output.put((width >> 8) & 0xFF);
//    output.put(width & 0xFF);
//    //// ��� ��������� �����������
//    //output.put(0x03);
//    //output.put(0x01);
//    //output.put(0x11);
//    //output.put(0x00);
//
//    // ������ ������
//    output.write(reinterpret_cast<const char*>(Image.data()), Image.size());
//
//    // ������ �����
//    output.put(0xFF);
//    output.put(0xD9);
//    output.close();
//
//    cout << "����������� ��������� � " << outputFile << std::endl;
//    return 0;
//}