#include "btree.hpp"
#include "pair.hpp"
#include "binary_tree_node1.hh"

int		main()
{
	ft::Rb_tree<ft::pair<int, std::string>> tree;
	ft::pair<int, std::string> truc(42, "ecole");
	tree.add(truc);
}
