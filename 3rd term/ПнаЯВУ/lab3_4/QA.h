#pragma once
#include "Header.h"

class QA
{
private:
	std::string question;
	std::vector<std::string> answers;
public:
	QA();
	QA(std::string question_, std::vector<std::string> answers_);

	void setQuestion(std::string line);
	void setAnswers(std::string line);
	void setAnswer(std::string line, int n);
	std::string getQuestion();
	size_t getNumOfAnswers();
	std::string getAnswers(int a);
	void deleteAnswer(int a);
};

void readSiteFromFile(std::vector<QA>& pages);