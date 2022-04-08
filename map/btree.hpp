#ifndef BTREE_HPP
# define BTREE_HPP

#include <cstdlib>
#include <iostream>

namespace ft
{
	template <typename K, typename V>
		class Tree
		{
			typedef	size_t	size_type;
			class Node
			{
				private:
					K			_key;
					V			_value;
					Node		*_left;
					Node		*_right;
					Node		*_parent;
					bool		_isLeftChild;
					bool		_black;

				public:
					Node(K key, V value)
						: _key(key), _value(value), _black(false), _isLeftChild(false)
					{
						_left = _right = _parent = NULL;
					}
			};
			private:
				Node		_root;
				size_type	_size;

			public:
				void	add(K key, V value)
				{
					Node	node = new Node(key, value);
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
				bool	compare(K key1, K key2)
				{
					return (key1 > key2);
				}
				void	add(Node parent, Node newNode)
				{
					if (compare(newNode._key, parent._key))
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
							node = node.left;
						} else {
							node = node.right;
						}
					}
					return (NULL);
				}
				/*
				 **
				 **		DELETION
				 **
				 */
				void deleteNode(int key) {
					Node node = _root;

					// Find the node to be deleted
					while (node != NULL && node.data != key) {
						// Traverse the tree to the left or right depending on the key
						if (key < node.data) {
							node = node.left;
						} else {
							node = node.right;
						}
					}

					// Node not found?
					if (node == NULL) {
						return;
					}

					// At this point, "node" is the node to be deleted

					// In this variable, we'll store the node at which we're going to start to fix the R-B
					// properties after deleting a node.
					Node movedUpNode;
					bool deletedNodeColorIsBlack;

					// Node has zero or one child
					if (node.left == NULL || node.right == NULL) {
						movedUpNode = deleteNodeWithZeroOrOneChild(node);
						deletedNodeColorIsBlack = node._black;
					}

					// Node has two children
					else {
						// Find minimum node of right subtree ("inorder successor" of current node)
						Node inOrderSuccessor = findMinimum(node.right);

						// Copy inorder successor's data to current node (keep its color!)
						node.data = inOrderSuccessor.data;

						// Delete inorder successor just as we would delete a node with 0 or 1 child
						movedUpNode = deleteNodeWithZeroOrOneChild(inOrderSuccessor);
						deletedNodeColorIsBlack = inOrderSuccessor.color;
					}

					if (deletedNodeColorIsBlack == true) {
						fixRedBlackPropertiesAfterDelete(movedUpNode);

						// Remove the temporary NIL node
						if (movedUpNode.getClass() == NilNode.class) {
							replaceParentsChild(movedUpNode.parent, movedUpNode, NULL);
						}
					}
				}
				void replaceParentsChild(Node parent, Node oldChild, Node newChild)
				{
					if (parent == NULL)
						_root = newChild;
					else if (parent.left == oldChild)
						parent.left = newChild;
					else if (parent.right == oldChild)
						parent.right = newChild;
					else
						throw new std::invalid_argument("Node is not a child of its parent");
					if (newChild != NULL)
						newChild.parent = parent;
				}
		};
};

#endif
