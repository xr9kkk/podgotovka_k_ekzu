#include <iostream>
#include <string>
#include "trie_tree.h"
#include "binary_tree.h"
#include <queue>
#include <vector>
#include <stack>

//kim ¹4----------------------------------------------------------------------------------
//recursion delete yarus
bool recursion_delete_tiers(btree::ptrNODE& root, int level)
{
	if (!root)
		return false;
	if (level == 1)
	{
		delete root;
		root = nullptr;
		return true;
	}
	bool left_deleted = recursion_delete_tiers(root->left, level - 1);
	bool right_deleted = recursion_delete_tiers(root->right, level - 1);
	return left_deleted || right_deleted;
}

bool recursion_delete_tiers(btree::BTREE& tree, int level)
{
	if (tree.empty())
	{
		return false;
	}
	return recursion_delete_tiers(tree.get_root(), level);
}

//non-recursive search function for the sum of elements from the root to a given level
int find_sum(btree::ptrNODE& root, int level)
{
	if (!root || level < 1)
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

//The third task: duplicating the last letter of each word
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


//kim ¹3----------------------------------------------------------------------------------
//recursive add new yarus
bool recursion_add_tiers(btree::ptrNODE& root)
{
	if (!root)
		return false;

	bool added{};

	if (!root->left)
	{
		root->left = new btree::NODE(0);
		added = true;
	}

	if (!root->right)
	{
		root->right = new btree::NODE(0);
		added = true;
	}

	if (added)
		return true;

	bool left_added = recursion_add_tiers(root->left);
	bool right_added = recursion_add_tiers(root->right);
	return added || left_added || right_added;
}

//non-recursive find sum from 0 element to first odd inclusive
int find_sum_to_odd(btree::ptrNODE& root)
{
	if (!root)
		return 0;
	std::stack<btree::ptrNODE> s;
	if (root->info % 2 == 1)
		s.push(root);

	int sum{};
	while (!s.empty())
	{
		auto current = s.top();
		s.pop();
		sum += current->info;
		if (current->right != nullptr && current->right->info % 2 == 1)
			s.push(current->right);
		if (current->left != nullptr && current->left->info % 2 == 1)
			s.push(current->left);
	}
	return sum;
}


//delete last char
bool ptrs_node_empty(ttree::ptrNODE r) {
	for (size_t i{}; i < 26UL; ++i)
		if (r->ptrs[i])
			return false;;
	return true;
}

void remove_last_ch(ttree::ptrNODE& r) {
	if (!r)
		return;
	for (size_t i{}; i < 26UL; ++i) {
		if (r->ptrs[i]) {
			if (r->ptrs[i]->eow) {
				if (ptrs_node_empty(r->ptrs[i])) {
					delete r->ptrs[i];
					r->ptrs[i] = nullptr;
				}
				else {
					r->ptrs[i]->eow = false;
				}
				r->eow = true;
			}
			remove_last_ch(r->ptrs[i]);
		}
	}
}




int main()
{
	setlocale(LC_ALL, "ru");
	/*ttree::TTREE ttree("trie.txt");
	ttree.print("");*/
	btree::BTREE btree("binary.txt");
	btree.print();

	/*std::cout << "KIM ¹4\n";
	std::cout << "The first task: recursive removal of tiers. \n";
	int level = 3;
	if (recursion_delete_tiers(btree, level)) {
		std::cout << "Level " << level << " deleted\n";
		btree.print();
	}

	std::cout << "The second task is to find the amount up to a given level.\n";
	int new_level = 3;
	int sum = find_sum(btree.get_root(), new_level);
	std::cout << sum << std::endl;

	std::cout << "The third task: duplicating the last letter of each word. \n";
	std::vector<char> word;
	ttree::ptrNODE new_root = double_last_sym(ttree.get_root(), word);
	ttree::printW(new_root, "");*/

	std::cout << "KIM ¹3\n";
	std::cout << "The first task: recursive add new 0 leafs\n";
	if (recursion_add_tiers(btree.get_root()))
		btree.print();
	int sum_odd = find_sum_to_odd(btree.get_root());
	std::cout << "The second task: sum before odd element " << sum_odd << std::endl;
	std::cout << "Third task: delete last sym in word\n";
	ttree::TTREE ttree("trie.txt");
	ttree::ptrNODE root = ttree.get_root();
	remove_last_ch(root);
	ttree.print("");
	return 0;
}

