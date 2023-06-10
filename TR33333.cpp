// TR33333.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#pragma once
#define TRIE_H
#ifndef TRIE_H

using namespace std;

struct TrieNode
{
	struct TrieNode* children[ALPHABET_SIZE];
	// isEndOfWord - true, если ключ является концом слова
	bool isEndOfWord;
};

TrieNode* getNewNode(void)
{
	// Выделяем память под новый узел
	struct TrieNode* pNode = new TrieNode;

	// устанавливаем флаг конца слова в false
	pNode->isEndOfWord = false;

	// инициализируем детей нулевым указателем
	for (int i = 0; i < ALPHABET_SIZE; i++)
		pNode->children[i] = nullptr;

	return pNode;
}

bool search(struct TrieNode* root, string key)
{
	TrieNode* node = root;
	for (int i = 0; i < key.length(); i++)
	{
		int index = key[i] - 'a';
		if (!node->children[index])
			return false;

		node = node->children[index];
	}

	return (node != nullptr && node->isEndOfWord);
}
bool isEmpty(TrieNode* root)
{
	for (int i = 0; i < ALPHABET_SIZE; i++)
		if (root->children[i])
			return false;
	return true;
}
TrieNode* remove(TrieNode* root, string key, int depth = 0)
{
	// Если дерево пустое
	if (!root)
		return nullptr;
	// Если дошли до конца ключа
	if (depth == key.size()) {
		// Этот узел больше не конец слова
		// поэтому снимаем метку
		if (root->isEndOfWord)
			root->isEndOfWord = false;
		// Если ключ не является префиксом, удаляем его
		if (isEmpty(root)) {
			delete (root);
			root = nullptr;
		}

		return root;
	}

	// Пока не дошли до конца ключа или определили, 
	// что его нет в дереве, рекурсивно вызываем для ребенка
	// соответствующего символа
	int index = key[depth] - 'a';
	root->children[index] = remove(root->children[index], key, depth + 1);
	// Если у корня нет дочернего слова
	// (удален только один его дочерний элемент),
	// и он не заканчивается другим словом.
	if (isEmpty(root) && root->isEndOfWord == false) {
		delete (root);
		root = nullptr;
	}
	// возвращаем новый корень
	return root;
}
#endif

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
