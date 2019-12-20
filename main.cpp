#include <iostream>
#include <vector>

#include "KnuthAlgorithm.h"

#include <stdlib.h>
#include <string>
#include <map>
#include <algorithm>

void coutCode(std::vector<int> m_code, std::string m_pegScore = "") {
	for (auto n : m_code) {
		std::cout << n << " ";
	}

	std::cout << ": " <<  m_pegScore<< std::endl;
}

int main() {

	std::vector<int> m_code;
	std::vector<int> m_currentGuess;

	std::vector<std::vector<int>> m_combinations;
	std::vector<std::vector<int>> m_possibleSolutions;
	std::vector<std::vector<int>> m_nextGuesses;

	m_code = getCode();
	m_currentGuess = { 1, 1, 2, 2};

	generateSet(m_combinations);
	m_possibleSolutions.insert(m_possibleSolutions.end(), m_combinations.begin(), m_combinations.end());
	
	std::cout << "Zadani kod: ";
	coutCode(m_code);

	int m_turn = 1;
	bool m_found = false;
	while (!m_found) {
		
		removeCode(m_combinations, m_currentGuess);
		removeCode(m_possibleSolutions, m_currentGuess);

		std::string m_pegScore = checkCode(m_currentGuess, m_code);

		std::cout << m_turn++ << ". ";
		coutCode(m_currentGuess, m_pegScore);

		if (m_pegScore == "BBBB") {
			m_found = true;
			continue;
		}

		removeIncorrectCodes(m_currentGuess, m_possibleSolutions, m_pegScore);

		m_nextGuesses = minmax(m_combinations, m_possibleSolutions);

		m_currentGuess = getNextGuess(m_nextGuesses, m_combinations, m_possibleSolutions);
	}

	system("pause");
	return 0;
}