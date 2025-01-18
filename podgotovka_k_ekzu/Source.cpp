#include <iostream>
#include <string>
#include "trie_tree.h"
#include "binary_tree.h"





int main()
{
	ttree::TTREE ttree("trie.txt");
	ttree.print("");
	std::cout << std::endl;
	btree::BTREE btree("binary.txt");
	btree.print();
	btree.clear(btree.get_root());
	btree.print();

	return 0;
}