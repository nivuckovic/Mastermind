#pragma once

#include <vector>
#include <map>

extern int m_colors;
extern int m_codeLength;

void generateSet(std::vector<std::vector<int>> &m_combinations);

void recursivePermutation(int position, std::vector<int> &m_current, std::vector<std::vector<int>> &m_combinations);

std::vector<int> getCode();
std::string checkCode(std::vector<int> m_guess, std::vector<int> m_code);

void removeCode(std::vector<std::vector<int>> &m_set, std::vector<int> &m_code);

void removeIncorrectCodes(std::vector<int> &m_current, std::vector<std::vector<int>> &m_possibleSolutions, std::string &m_pegScore);

std::vector<std::vector<int>> minmax(std::vector<std::vector<int>> &m_combinations, std::vector<std::vector<int>> &m_possibleSolutions);

std::vector<int> getNextGuess(std::vector<std::vector<int>> &m_nextGuesses, std::vector<std::vector<int>> &m_combinations, std::vector<std::vector<int>> &m_possibleSolutions);