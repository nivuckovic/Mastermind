#include "KnuthAlgorithm.h"

#include <ctime>
#include <algorithm>
#include <iostream>
#include <functional>

int m_colors = 6;
int m_codeLength = 4;

void generateSet(std::vector<std::vector<int>>& m_combinations)
{
	std::vector<int> m_current(m_codeLength, 0);

	recursivePermutation(0, m_current, m_combinations);
}

void recursivePermutation(int position, std::vector<int>& m_current, std::vector<std::vector<int>> &m_combinations)
{
	if (position >= m_codeLength) {
		m_combinations.push_back(m_current);
		return;
	}

	for (int i = 0; i < m_colors; ++i) {
		m_current[position] = i + 1;
		recursivePermutation(position + 1, m_current, m_combinations);
	}
}

std::vector<int> getCode()
{
	srand(time(NULL));

	std::vector<int> m_code;

	for (int i = 0; i < m_codeLength; ++i) {
		m_code.push_back(1 + rand() % m_colors);
	}

	return m_code;
}

std::string checkCode(std::vector<int> m_guess, std::vector<int> m_code)
{
	std::string m_result;

	for (int i = 0; i < m_codeLength; ++i) {
		if (m_guess[i] == m_code[i]) {
			m_result.append("B");
			m_guess[i] = -1;
			m_code[i] = -1;
		}
	}

	for (int i = 0; i < m_codeLength; ++i) {
		if (m_code[i] > 0) {
			auto it = std::find(m_guess.begin(), m_guess.end(), m_code[i]);

			if (it != m_guess.end()) {
				m_result.append("W");
				*it = -1;
			}
		}
	}

	return m_result;
}

void removeCode(std::vector<std::vector<int>>& m_set, std::vector<int>& m_code)
{
	auto it = std::find(m_set.begin(), m_set.end(), m_code);
	
	if (it != m_set.end())
		m_set.erase(it);
}

void removeIncorrectCodes(std::vector<int>& m_current, std::vector<std::vector<int>> &m_possibleSolutions, std::string & m_pegScore)
{
	auto it = m_possibleSolutions.begin();

	while (it != m_possibleSolutions.end()) {
		if (m_pegScore != checkCode(m_current, *it)) {
			it = m_possibleSolutions.erase(it);
		}
		else {
			++it;
		}
	}
}

std::vector<std::vector<int>> minmax(std::vector<std::vector<int>> &m_combinations, std::vector<std::vector<int>> &m_possibleSolutions)
{
	std::map<std::string, int> m_caseCount;
	std::map<std::vector<int>, int> m_scoreTable;

	int max, min;

	for (int i = 0; i < m_combinations.size(); ++i) {
		for (int j = 0; j < m_possibleSolutions.size(); ++j) {
			std::string m_pegScore = checkCode(m_combinations[i], m_possibleSolutions[j]);

			m_caseCount[m_pegScore]++;
		}
		
		max = std::max_element(m_caseCount.begin(), m_caseCount.end(), [](auto &p1, auto &p2) { return p1.second < p2.second; })->second;
		
		m_scoreTable[m_combinations[i]] = max;

		m_caseCount.clear();
	}

	min = std::min_element(m_scoreTable.begin(), m_scoreTable.end(), [](auto &p1, auto &p2) { return p1.second < p2.second; })->second;

	
	std::vector<std::vector<int>> m_nextGuesses;

	for (auto &x : m_scoreTable) {
		if (x.second == min) {
			m_nextGuesses.push_back(x.first);
		}
	}

	return m_nextGuesses;
}

std::vector<int> getNextGuess(std::vector<std::vector<int>>& m_nextGuesses, std::vector<std::vector<int>>& m_combinations, std::vector<std::vector<int>>& m_possibleSolutions)
{
	std::vector<int> m_nextGuess;

	for (auto &x : m_nextGuesses) {
		if (std::find(m_possibleSolutions.begin(), m_possibleSolutions.end(), x) != m_possibleSolutions.end())
			return x;
	}

	for (auto &x : m_nextGuesses) {
		if (std::find(m_combinations.begin(), m_combinations.end(), x) != m_combinations.end())
			return x;
	}

	return m_nextGuess;
}

