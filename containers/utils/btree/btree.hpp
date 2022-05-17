#ifndef BTREE_HPP
# define BTREE_HPP

#include <cstdlib>
#include <iostream>
#include "binary_tree_node1.hh"
#include "pair.hpp"
namespace ft
{
/*	template <typename T>
	class Node
	{
		public:
			typedef T		value_type;

			Node(value_type val)
				: val(val), black(false), isLeftChild(false), _isDoubleBlack(false)
			{
				left = right = parent = NULL;
			}

		private:
			value_type	val;
			Node		*left;
			Node		*right;
			Node		*parent;
			bool		isLeftChild;
			bool		black;
			bool		_isDoubleBlack;
	};*/

	template <typename Pair, class Compare = std::less<Pair>, class Node = ft::node<Pair>,
			 class Node_Alloc = std::allocator<Node>,class Pair_Alloc = std::allocator<Pair>>
		class Rb_tree
		{
			public:

				typedef	Pair_Alloc							allocator_type;
				typedef typename Pair_Alloc::value_type	value_type;
				typedef Node_Alloc						node_alloc;
				typedef	size_t							size_type;


			private:
				Node		*_root;
				/**
				 * @Brief _management_node will be used to manage end() begin()
				 *	and to manage the overall tree traversal when reaching minimum and maximum node.
				*/
				Node		*_management_node;
				size_type	_size;
				node_alloc	_node_alloc;
				Pair		_pair;

			public:
				Rb_tree(const node_alloc& node_alloc_init = node_alloc())
				:	_node_alloc(node_alloc_init)
				{
					_management_node = _node_alloc.allocate(1);
					_node_alloc.construct(_management_node, Node(_management_node, _management_node, _management_node));
				}
				~Rb_tree()
				{
					_node_alloc.destroy(_management_node);
					_node_alloc.deallocate(_management_node, 1);
				}

				Node	*add(value_type val)
				{
					Node *node =  _node_alloc.allocate(1);
					_node_alloc.construct(node, Node(val));
					if (_root == NULL)
					{
						_root = node;
						_root->black = true;
						_size++;
						_root->right = _management_node;
						_root->left = _management_node;
						_management_node->parent = _root;
						_management_node->right = _root;
						_management_node->left = _root;
						return _root;
					}
					if(!add(_root, node))
						return NULL;
					checkColor(node);
					_size++;
					if (isMinimum(node))
						updateMinimum(node);
					else if (isMaximum(node))
						updateMaximum(node);
					_management_node->value.first += 1;
					ft::node<Pair>::DG_tree(_root);
					return node;
				}

				size_type deleteNode(value_type val)
				{
					// In this variable, we'll store the node at which we're going to start to fix the R-B
					// properties after deleting a node.
					Node *movedUpNode;
					bool deletedNodeColorIsBlack;

					Node *node = _root;

					// Find the node to be deleted
					while (node != NULL && node->val.first != val.first)
					{
						// Traverse the tree to the left or right depending on the key
						if (Compare(val < node->val))
							node = node->left;
						else
							node = node->right;
					}

					// Node not found?
					if (node == NULL)
						return 0;
					// At this point, "node" is the node to be deleted


					// Node has zero or one child
					if (node->left == NULL || node->right == NULL)
					{
						movedUpNode = deleteNodeWithZeroOrOneChild(node);
						deletedNodeColorIsBlack = node->black;
					}

					// Node has two children
					else
					{
						// Find minimum node of right subtree ("inorder successor" of current node)
						Node *inOrderSuccessor = findMinimum(node->right);

						// Copy inorder successor's data to current node (keep its.black!)
						node->val.second = inOrderSuccessor->val.second;

						// Delete inorder successor just as we would delete a node with 0 or 1 child
						movedUpNode = deleteNodeWithZeroOrOneChild(inOrderSuccessor);
						deletedNodeColorIsBlack = inOrderSuccessor->black;
					}
					if (deletedNodeColorIsBlack == true)
					{
						fixRedBlackPropertiesAfterDelete(movedUpNode);

						// Remove the temporary NIL node
						if (movedUpNode->_isDoubleBlack == true)
							replaceParentsChild(movedUpNode->parent, movedUpNode, NULL);
					}
					_management_node->value.first -= 1;
					return (1);
				}

				size_type max_size() const
				{
					return (node_alloc().max_size());
				}
			private:
				bool	compare(value_type val1, value_type val2)
				{
					return (val1 > val2);
				}

				Node	*add(Node *parent, Node *newNode)
				{
					if (newNode->val->first == parent->val->first)
						return NULL;
					if (compare(newNode->val, parent->val))
					{
						if (parent->right == NULL)
						{
							parent->right = newNode;
							newNode->parent = parent;
							newNode->isLeftChild = false;
							return newNode;
						}
						return add(parent->right, newNode);
					}
					if (parent->left == NULL)
					{
						parent->left = newNode;
						newNode->parent = parent;
						newNode->isLeftChild = true;
						return newNode;
					}
					return add(parent->left, newNode);
				}

				/*		TOOLS		*/
				Node *findMinimum(Node *node)
				{
					while (node->left != NULL)
						node = node->left;
					return node;
				}

				bool	isMinimum(Node *node)
				{
					Node minimum = _root;

					while (minimum->left)
						minimum = minimum->left;
					return (node == minimum);
				}

				bool	isMaximum(Node *node)
				{
					Node maximum = _root;

					while (maximum->right)
						maximum = maximum->right;
					return (node == maximum);
				}

				void	updateRoot(Node *node)
				{
					_management_node->parent = node;
					node->parent = _management_node;
				}
				void	updateMinimum(Node *node)
				{
					_management_node->left = node;
					node->left = _management_node;
				}

				void	updateMaximum(Node *node)
				{
					_management_node->right = node;
					node->right = _management_node;
				}

				Node getSibling(Node *node)
				{
					Node parent = node->parent;
					if (node->isLeftChild == true)
						return parent->right;
					else if (node == parent->right)
						return parent->left;
				}

				bool isBlack(Node node)
				{
					return node == NULL || node.black == true;
				}
				/*
				**
				**		CHECK AND FIX TREE
				**
				*/
				void	checkColor(Node *node)
				{
					if (node == _root)
						return ;
					if (!node->black && !node->parent->black)
						correctTree(node);
					checkColor(node->parent);
				}

				void	correctTree(Node *node)
				{
					// AUNT IS GRANDPARENT.RIGHT
					if (node->parent->isLeftChild)
					{
						if (node->parent->parent->right == NULL || node->parent->parent->right->black)
							return (rotate(node));
					}
					if (node->parent->parent->right != NULL)
						node->parent->right->black = true;
					node->parent->parent->black = false;
					node->parent->black = true;
					return ;
					// AUNT IS GRANDPARENT.LEFT
					if (node->parent->parent->left == NULL || node->parent->parent->left->black)
							return (rotate(node));
					if (node->parent->parent->left != NULL)
						node->parent->left->black = true;
					node->parent->parent->black = false;
					node->parent->black = true;
					return ;
				}

				void	rotate(Node *node)
				{
					if (node->isLeftChild)
					{
						if (node->parent->isLeftChild)
						{
							rightRotate(node->parent->parent);
							node->black = false;
							node->parent->black = true;
							if (node->parent->right != NULL)
								node->parent->right->black = false;
						}
						return ;
					}
					else if (node->parent->isLeftChild == false)
					{
						rightLeftRotate(node->parent->parent);
						node->black = true;
						node->right->black = false;
						node->left->black = false;
						return ;
					}
					if (node->isLeftChild == false)
					{
						if (node->parent->isLeftChild == false)
						{
							leftRotate(node->parent->parent);
							node->black = false;
							node->parent->black = true;
							if (node->parent->left != NULL)
								node->parent->left->black = false;
						}
						return ;
					}
					else if (node->parent->isLeftChild)
					{
						leftRightRotate(node->parent->parent);
						node->black = true;
						node->right->black = false;
						node->left->black = false;
						return ;
					}
				}

				void	leftRotate(Node *node)
				{
					Node *tmp;

					tmp = node->right;
					node->right = tmp->left;
					if (node->right != NULL)
					{
						node->right->parent = node;
						node->right->isLeftChild = false;
					}
					if (node->parent == NULL)
					{
						//NODE IS ROOT
						_root = tmp;
						tmp->parent = NULL;
					}
					else
					{
						tmp->parent = node->parent;
						if (node->isLeftChild)
						{
							tmp->isLeftChild = true;
							tmp->parent->left = tmp;
						}
						else
						{
							tmp->isLeftChild = false;
							tmp->parent->right = tmp;
						}

					}
					tmp->left = node;
					node->isLeftChild = true;
					node->parent = tmp;
				}

				void	rightRotate(Node *node)
				{
					Node *tmp;

					tmp = node->left;
					node->left = tmp->right;
					if (node->left != NULL)
					{
						node->left->parent = node;
						node->left->isLeftChild = true;
					}
					if (node->parent == NULL)
					{
						//NODE IS ROOT
						_root = tmp;
						tmp->parent = NULL;
					}
					else
					{
						tmp->parent = node->parent;
						if (node->isLeftChild == false)
						{
							tmp->isLeftChild = false;
							tmp->parent->right = tmp;
						}
						else
						{
							tmp->isLeftChild = true;
							tmp->parent->left = tmp;
						}

					}
					tmp->right = node;
					node->isLeftChild = false;
					node->parent = tmp;
				}

				void	leftRightRotate(Node *node)
				{
					leftRotate(node->left);
					rightRotate(node);
				}

				void	rightLeftRotate(Node *node)
				{
					rightRotate(node->right);
					leftRotate(node);
				}

				/*
				**
				**	SEARCH
				**
				*/
				Node searchNode(int key)
				{
					Node *node = _root;
					while (node != NULL)
					{
						if (key == node->data)
							return node;
						else if (key < node->data)
							node = node->left;
						else
							node = node->right;
					}
					return (NULL);
				}

				/*
				**
				**		DELETION
				**
				*/
				void fixRedBlackPropertiesAfterDelete(Node *node)
				{
					// Case 1: Examined node is root, end of recursion
					if (node == _root)
					{
						/**
						 * Uncomment the following line if you want to enforce black roots (rule 2):
						 * node.color = BLACK;
						*/
						return;
					}

					Node *sibling = getSibling(node);

					/* Case 2: Red sibling */
					if (sibling->color == RED)
					{
						handleRedSibling(node, sibling);
						/* Get new sibling for fall-through to cases 3-6 */
						sibling = getSibling(node);
					}

					/* Cases 3+4: Black sibling with two black children */
					if (isBlack(sibling->left) && isBlack(sibling->right))
					{
						sibling->color = RED;

						/* Case 3: Black sibling with two black children + red parent */
						if (node->parent->color == RED)
							node->parent->color = BLACK;
						/* Case 4: Black sibling with two black children + black parent */
						else
							fixRedBlackPropertiesAfterDelete(node->parent);
					}

					/* Case 5+6: Black sibling with at least one red child */
					else
						handleBlackSiblingWithAtLeastOneRedChild(node, sibling);
				}

				Node *deleteNodeWithZeroOrOneChild(Node *node)
				{
					/* Node has ONLY a left child --> replace by its left child */
					if (node->left != NULL)
					{
						replaceParentsChild(node->parent, node, node->left);
						return node->left; // moved-up node
					}

					/* Node has ONLY a right child --> replace by its right child */
					else if (node->right != NULL)
					{
						replaceParentsChild(node->parent, node, node->right);
						return node->right; // moved-up node
					}

					/**
					 * Node has no children -->
					 * node is red --> just remove it
					 * node is black --> replace it by a temporary NIL node (needed to fix the R-B rules)
					*/
					else
					{
						Node *newChild = new Node();
						if (node->black == true)
							newChild->_isDoubleBlack = true;
						else
						{
							delete newChild;
							newChild = NULL;
						}
						replaceParentsChild(node->parent, node, newChild);
						return newChild;
					}
				}

				void replaceParentsChild(Node *parent, Node *oldChild, Node *newChild)
				{
					if (parent == NULL)
						_root = newChild;
					else if (oldChild->isLeftChild == true)
						parent->left = newChild;
					else
						parent->right = newChild;
					if (newChild != NULL)
						newChild->parent = parent;
				}

				void handleRedSibling(Node *node, Node *sibling)
				{
					// R.black...
					sibling->black = true;
					node->parent->black = false;

					// ... and rotate
					if (node->isLeftChild)
						rotateLeft(node->parent);
					else
						rotateRight(node->parent);
				}

				void handleBlackSiblingWithAtLeastOneRedChild(Node *node, Node *sibling)
				{
					/**
					 * Case 5: Black sibling with at least one red child + "outer nephew" is black
					 * --> R.black sibling and its child, and rotate around sibling
					*/
					if (node->isLeftChild && isBlack(sibling->right))
					{
						sibling->left->black == true;
						sibling->black = false;
						rotateRight(sibling);
						sibling = node->parent->right;
					}
					else if (!node->isLeftChild && isBlack(sibling->left))
					{
						sibling->right->black = true;
						sibling->black = false;
						rotateLeft(sibling);
						sibling = node->parent->left;
					}

					/**
					 * Fall-through to case 6...
					 *
					 * Case 6: Black sibling with at least one red child + "outer nephew" is red
					 * --> R.black sibling + parent + sibling's child, and rotate around parent
					*/
					sibling->black = node->parent->black;
					node->parent->black = true;
					if (node->isLeftChild)
					{
						sibling->right->black = true;
						rotateLeft(node->parent);
					}
					else
					{
						sibling->left->black = true;
						rotateRight(node->parent);
					}
				}
		};
};

#endif
