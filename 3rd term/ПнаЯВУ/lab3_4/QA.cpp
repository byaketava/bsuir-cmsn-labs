#include "Header.h"
#include "QA.h"

QA::QA() :question(" "), answers(0) {}
QA::QA(std::string question_, std::vector<std::string> answers_) : question(question_), answers(answers_) {}
void QA::setQuestion(std::string line)
{
    this->question = line;
}
void QA::setAnswers(std::string line)
{
    this->answers.push_back(line);
}
void QA::setAnswer(std::string line, int n)
{
    this->answers[n] = line;
}
std::string QA::getQuestion()
{
    return this->question;
}
size_t QA::getNumOfAnswers()
{
    return this->answers.size();
}
std::string QA::getAnswers(int a)
{
    return this->answers[a];
}
void QA::deleteAnswer(int a)
{
    this->answers.erase(answers.begin() + a);;
}

void readSiteFromFile(std::vector<QA>& pages)
{
    std::ifstream file("site.txt"); // Открытие файла для чтения в бинарном режиме
    if (file.is_open())
    {
        QA quest;
        std::string line;
        while (std::getline(file, line))
        {
            // Читаем вопрос
            quest.setQuestion(line);

            // Читаем ответы на вопрос
            while (std::getline(file, line) && !line.empty())
                quest.setAnswers(line);
            pages.push_back(quest);
            quest = QA();
        }
        file.close(); // Закрытие файла
    }
}