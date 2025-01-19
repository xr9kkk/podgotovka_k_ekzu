#include <iostream>
#include <string>
#include "trie_tree.h"
#include "binary_tree.h"
#include <queue>
#include <vector>

//ким є4----------------------------------------------------------------------------------
//рекурсивное удаление €русов
bool recursion_delete_yarus(btree::ptrNODE& root, int level)
{
	if (!root)
		return false;
	if (level == 1)
	{
		delete root; 
		root = nullptr; 
		return true;
	}
	bool left_deleted = recursion_delete_yarus(root->left, level - 1);
	bool right_deleted = recursion_delete_yarus(root->right, level - 1);
	return left_deleted || right_deleted;
}

bool recursion_delete_yarus(btree::BTREE& tree, int level)
{
	if (tree.empty())
	{
		return false;
	} 
	return recursion_delete_yarus(tree.get_root(), level);
}

//нерекурсивна€ функци€ поиска суммы элементов от корн€ до заданного уровн€
int find_sum(btree::ptrNODE& root, int level)
{
	if (!root|| level<1)
		return 0;
	
	std::queue<std::pair<btree::ptrNODE, int>> q;
	q.push({ root, 1 });
	int sum{};
	

	while (!q.empty())
	{
		auto [current, current_level] = q.front();
		q.pop();

		if (current_level <= level)
			sum += current->info;
		if (current_level < level)
		{
			if (current->left)
				q.push({ current->left, current_level + 1 });
			if (current->right)
				q.push({ current->right, current_level + 1 });
		}
	}
	return sum;
}

//“реть€ задача: дублирование последней буквы каждого слова
ttree::ptrNODE double_last_sym(ttree::ptrNODE root, std::vector<char>& word) {
	if (!root)
		return nullptr;

	ttree::ptrNODE new_node = new ttree::NODE();
	new_node->eow = root->eow;

	if (root->eow && !word.empty()) {
		char last_char = word.back();
		int index = last_char - 'a';

		if (!new_node->ptrs[index]) {
			new_node->ptrs[index] = new ttree::NODE();
			new_node->ptrs[index]->eow = true;
		}
	}

	for (int i = 0; i < 26; ++i) {
		if (root->ptrs[i]) {
			word.push_back('a' + i);
			new_node->ptrs[i] = double_last_sym(root->ptrs[i], word);
			word.pop_back();
		}
	}

	return new_node;
}




int main()
{
	setlocale(LC_ALL, "ru");
	ttree::TTREE ttree("trie.txt");
	ttree.print("");
	bool flag = ttree.get_root()->eow;
	std::cout << std::endl;
	btree::BTREE btree("binary.txt");
	btree.print();
	

	std::cout << "ѕерва€ задача: рекурсивное удаление €русов \n";
	int level = 3;
	if (recursion_delete_yarus(btree, level)) {
		std::cout << "Level " << level << " deleted\n";
		btree.print();
	}
	 
	std::cout << "¬тора€ задача: поиск суммы до заданного уровн€\n";
	int new_level = 3;
	int sum = find_sum(btree.get_root(), new_level);
	std::cout << sum << std::endl;

	std::cout << "“реть€ задача: дублирование последней буквы каждого слова\n";
	std::vector<char> word;
	ttree::ptrNODE new_root = double_last_sym(ttree.get_root(), word);
	ttree::printW(new_root, "");
	

	return 0;
}