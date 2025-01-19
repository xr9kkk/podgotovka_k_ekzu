#include <iostream>
#include <string>
#include "trie_tree.h"
#include "binary_tree.h"
#include <queue>

//��� �4----------------------------------------------------------------------------------
//����������� �������� ������
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

//������������� ������� ������ ����� ��������� �� ����� �� ��������� ������
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

//������ ������: ������������ ��������� ����� ������� �����
void double_last_sym(ttree::ptrNODE& root, std::string& word)
{
	if (!root)
		return;

	if (root->eow) //������ �� ����� ��� ������ �������� root->eow ����� false, ��� �� ���, ���� ����������� � ����, ���� ������ � ����� ��� �������� ������ �� ����� �������� � true
	{
		char last_char = word.back(); 
		int index = last_char - 'a';

		if (!root->ptrs[index])
		{
			root->ptrs[index] = new ttree::NODE();
		}

		root->ptrs[index]->eow = true;
	}

	for (int i = 0; i < 26; ++i)
	{
		if (root->ptrs[i])
		{
			word.push_back('a' + i);
			double_last_sym(root->ptrs[i], word);
			word.pop_back(); 
		}
	}
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
	

	std::cout << "������ ������: ����������� �������� ������ \n";
	//int level = 3;
	//if (recursion_delete_yarus(btree, level)) {
	//	std::cout << "Level " << level << " deleted\n";
	//	btree.print();
	//}
	// 
	std::cout << "������ ������: ����� ����� �� ��������� ������\n";
	int level = 3;
	int sum = find_sum(btree.get_root(), level);
	std::cout << sum << std::endl;

	std::cout << "������ ������: ������������ ��������� ����� ������� �����\n";
	std::string word = "";
	ttree::ptrNODE root = ttree.get_root();
	double_last_sym(root, word);
	ttree.print("");

	return 0;
}