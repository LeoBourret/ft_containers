#ifndef BTREE_HPP
# define BTREE_HPP

#include <cstdlib>
#include <iostream>

namespace ft
{
	template <typename T, class A = std::allocator<T>>
		class Tree
		{
			public:

				typedef	A						allocator_type;
				typedef typename A::value_type	value_type;
				typedef	size_t					size_type;
				class Node
				{
					public:
						typedef T	value_type;

						Node(value_type val)
							: _value(val), _black(false), _isLeftChild(false), _isDoubleBlack(false)
						{
							_left = _right = _parent = NULL;
						}

					private:
						value_type	_value;
						Node		*_left;
						Node		*_right;
						Node		*_parent;
						bool		_isLeftChild;
						bool		_black;
						bool		_isDoubleBlack;
				};


			private:
				Node		_root;
				size_type	_size;

			public:
				void	add(value_type value)
				{
					Node =  Node(value);
					if (_root == NULL)
					{
						_root = node;
						_root.black = true;
						_size++;
						return ;
					}
					add(_root, node);
					checkColor(node);
					_size++;
				}
			private:
				bool	compare(value_type val1, value_type val2)
				{
					return (val1 > val2);
				}
				void	add(Node parent, Node newNode)
				{
					if (compare(newNode._value, parent._value))
					{
						if (parent._right == NULL)
						{
							parent._right = newNode;
							newNode._parent = parent;
							newNode._isLeftChild = false;
							return ;
						}
						return add(parent._right, newNode);
					}
					if (parent._left == NULL)
					{
						parent._left = newNode;
						newNode._parent = parent;
						newNode._isLeftChild = true;
						return ;
					}
					return add(parent._left, newNode);
				}
				/*
				**
				**		TOOLS
				**
				*/
				Node findMinimum(Node node)
				{
					while (node._left != NULL)
						node = node._left;
					return node;
				}
				Node getSibling(Node node)
				{
					Node parent = node._parent;
					if (node._isLeftChild == true)
						return parent.right;
					else if (node == parent.right)
						return parent.left;
				}
				bool isBlack(Node node)
				{
					return node == NULL || node._black == true;
				}
				/*
				**
				**		CHECK AND FIX TREE
				**
				*/
				void	checkColor(Node node)
				{
					if (node == _root)
						return ;
					if (!node._black && !node._parent._black)
						correctTree(node);
					checkColor(node._parent);
				}
				void	correctTree(Node node)
				{
					// AUNT IS GRANDPARENT.RIGHT
					if (node._parent._isLeftChild)
					{
						if (node._parent._parent._right == NULL || node._parent._parent._right._black)
							return (rotate(node));
					}
					if (node._parent._parent._right != NULL)
						node._parent._right._black = true;
					node._parent._parent._black = false;
					node._parent._black = true;
					return ;
					// AUNT IS GRANDPARENT.LEFT
					if (node._parent._parent._left == NULL || node._parent._parent._left._black)
							return (rotate(node));
					if (node._parent._parent._left != NULL)
						node._parent._left._black = true;
					node._parent._parent._black = false;
					node._parent._black = true;
					return ;
				}
				void	rotate(Node node)
				{
					if (node._isLeftChild)
					{
						if (node._parent._isLeftChild)
						{
							rightRotate(node._parent._parent);
							node.black = false;
							node._parent._black = true;
							if (node._parent._right != NULL)
								node._parent._right._black = false;
						}
						return ;
					}
					else if (node._parent._isLeftChild == false)
					{
						rightLeftRotate(node._parent._parent);
						node._black = true;
						node._right._black = false;
						node._left._black = false;
						return ;
					}
					if (node._isLeftChild == false)
					{
						if (node._parent._isLeftChild == false)
						{
							leftRotate(node._parent._parent);
							node.black = false;
							node._parent._black = true;
							if (node._parent._left != NULL)
								node._parent._left._black = false;
						}
						return ;
					}
					else if (node._parent._isLeftChild)
					{
						leftRightRotate(node._parent._parent);
						node._black = true;
						node._right._black = false;
						node._left._black = false;
						return ;
					}
				}
				void	leftRotate(Node node)
				{
					Node *tmp;

					tmp = node._right;
					node._right = tmp->_left;
					if (node._right != NULL)
					{
						node._right._parent = node;
						node._right._isLeftChild = false;
					}
					if (node._parent == NULL)
					{
						//NODE IS ROOT
						_root = tmp;
						tmp->_parent = NULL;
					}
					else
					{
						tmp->_parent = node._parent;
						if (node._isLeftChild)
						{
							tmp->isLeftChild = true;
							tmp->_parent._left = tmp;
						}
						else
						{
							tmp->_isLeftChild = false;
							tmp->_parent._right = tmp;
						}

					}
					tmp->_left = node;
					node._isLeftChild = true;
					node._parent = tmp;
				}
				void	rightRotate(Node node)
				{
					Node *tmp;

					tmp = node._left;
					node._left = tmp->_right;
					if (node._left != NULL)
					{
						node._left._parent = node;
						node._left._isLeftChild = true;
					}
					if (node._parent == NULL)
					{
						//NODE IS ROOT
						_root = tmp;
						tmp->_parent = NULL;
					}
					else
					{
						tmp->_parent = node._parent;
						if (node._isLeftChild == false)
						{
							tmp->isLeftChild = false;
							tmp->_parent._right = tmp;
						}
						else
						{
							tmp->_isLeftChild = true;
							tmp->_parent._left = tmp;
						}

					}
					tmp->_right = node;
					node._isLeftChild = false;
					node._parent = tmp;
				}
				void	leftRightRotate(Node node)
				{
					leftRotate(node._left);
					rightRotate(node);
				}
				void	rightLeftRotate(Node node)
				{
					rightRotate(node._right);
					leftRotate(node);
				}
				/*
				**
				**	SEARCH
				**
				*/
				Node searchNode(int key)
				{
					Node node = _root;
					while (node != NULL) {
						if (key == node.data) {
							return node;
						} else if (key < node.data) {
							node = node._left;
						} else {
							node = node._right;
						}
					}
					return (NULL);
				}
				/*
				**
				**		DELETION
				**
				*/
				void deleteNode(int key)
				{
					Node node = _root;

					// Find the node to be deleted
					while (node != NULL && node.data != key)
					{
						// Traverse the tree to the left or right depending on the key
						if (key < node.data) {
							node = node._left;
						} else {
							node = node._right;
						}
					}

					// Node not found?
					if (node == NULL)
						return;
					// At this point, "node" is the node to be deleted

					// In this variable, we'll store the node at which we're going to start to fix the R-B
					// properties after deleting a node.
					Node movedUpNode;
					bool deletedNodeColorIsBlack;

					// Node has zero or one child
					if (node._left == NULL || node._right == NULL)
					{
						movedUpNode = deleteNodeWithZeroOrOneChild(node);
						deletedNodeColorIsBlack = node._black;
					}

					// Node has two children
					else
					{
						// Find minimum node of right subtree ("inorder successor" of current node)
						Node inOrderSuccessor = findMinimum(node._right);

						// Copy inorder successor's data to current node (keep its._black!)
						node.data = inOrderSuccessor.data;

						// Delete inorder successor just as we would delete a node with 0 or 1 child
						movedUpNode = deleteNodeWithZeroOrOneChild(inOrderSuccessor);
						deletedNodeColorIsBlack = inOrderSuccessor._black;
					}
					if (deletedNodeColorIsBlack == true)
					{
						fixRedBlackPropertiesAfterDelete(movedUpNode);

						// Remove the temporary NIL node
						if (movedUpNode._isDoubleBlack == true)
							replaceParentsChild(movedUpNode.parent, movedUpNode, NULL);
					}
				}
				Node deleteNodeWithZeroOrOneChild(Node node)
				{
					// Node has ONLY a left child --> replace by its left child
					if (node._left != NULL)
					{
						replaceParentsChild(node._parent, node, node._left);
						return node._left; // moved-up node
					}

					// Node has ONLY a right child --> replace by its right child
					else if (node._right != NULL)
					{
						replaceParentsChild(node._parent, node, node._right);
						return node._right; // moved-up node
					}

					// Node has no children -->
					// * node is red --> just remove it
					// * node is black --> replace it by a temporary NIL node (needed to fix the R-B rules)
					else
					{
						Node newChild = new Node();
						if (node._black == true)
							newChild._isDoubleBlack = true;
						else
						{
							delete newChild;
							newChild = NULL;
						}
						replaceParentsChild(node._parent, node, newChild);
						return newChild;
					}
				}
				void replaceParentsChild(Node parent, Node oldChild, Node newChild)
				{
					if (parent == NULL)
						_root = newChild;
					else if (oldChild.isLeftChild == true)
						parent.left = newChild;
					else
						parent.right = newChild;
					if (newChild != NULL)
						newChild.parent = parent;
				}
				void handleRedSibling(Node node, Node sibling)
				{
					// R._black...
					sibling._black = true;
					node._parent._black = false;

					// ... and rotate
					if (node._isLeftChild)
						rotateLeft(node._parent);
					else
						rotateRight(node._parent);
				}
				void handleBlackSiblingWithAtLeastOneRedChild(Node node, Node sibling)
				{
					// Case 5: Black sibling with at least one red child + "outer nephew" is black
					// --> R._black sibling and its child, and rotate around sibling
					if (node._isLeftChild && isBlack(sibling.right))
					{
						sibling._left._black == true;
						sibling._black = false;
						rotateRight(sibling);
						sibling = node._parent._right;
					}
					else if (!node._isLeftChild && isBlack(sibling.left))
					{
						sibling._right._black = true;
						sibling._black = false;
						rotateLeft(sibling);
						sibling = node._parent.left;
					}

					// Fall-through to case 6...

					// Case 6: Black sibling with at least one red child + "outer nephew" is red
					// --> R._black sibling + parent + sibling's child, and rotate around parent
					sibling._black = node._parent._black;
					node._parent._black = true;
					if (node._isLeftChild)
					{
						sibling.right._black = true;
						rotateLeft(node._parent);
					} else {
						sibling.left._black = true;
						rotateRight(node._parent);
					}
				}
		};
};

#endif
