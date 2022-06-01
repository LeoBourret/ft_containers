#ifndef RBTREE_HPP
# define RBTREE_HPP

#include <iostream>
#include "../utils.hpp"
#include "pair.hpp"
//#include "bidirectional_iterator.hpp"
//#include "binary_tree_node1.hh"


namespace ft
{
	template <class T>
			class Node
			{
				public:
					T		data;
					Node<T>	*parent;
					Node<T>	*left;
					Node<T>	*right;
					int		color;

					Node(T value = T())
						: data(value), parent(u_nullptr), left(u_nullptr), right(u_nullptr), color(0)
					{}

			};

	template <class T>
		class	bidirectional_iterator
		{
			public:
				typedef	T																						value_type;
				typedef Node<T>																					Node;
				typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type		difference_type;
				typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category	iterator_category;
				typedef value_type*																				pointer;
				typedef value_type&																				reference;

			private:
				Node*	_ptr;
				Node*	_management_node;
				Node*	_leaf;

			public:
				bidirectional_iterator()									: _ptr(u_nullptr), _management_node(u_nullptr), _leaf(u_nullptr)				{};
				bidirectional_iterator(Node* ptr, Node* mn, Node* leaf)		: _ptr(ptr), _management_node(mn), _leaf(leaf)									{};
				bidirectional_iterator(const bidirectional_iterator &src)	: _ptr(src._ptr), _management_node(src._management_node), _leaf(src._leaf)		{};

				bidirectional_iterator&	operator=(const bidirectional_iterator &rhs)
				{
					if (*this == rhs)
						return (*this);
					_ptr = rhs._ptr;
					_management_node = rhs._management_node;
					_leaf = rhs._leaf;
					return (*this);
				};
				virtual ~bidirectional_iterator() {};


				bool		operator==(const bidirectional_iterator &it) const	{return (this->_ptr == it._ptr);};
				bool		operator==(Node *ptr) const							{return (this->_ptr == ptr);};
				bool		operator!=(const bidirectional_iterator &it) const	{return (this->_ptr != it._ptr);};

				reference	operator*() const									{return (this->_ptr->data);};
				pointer		operator->() const									{return &operator*();};
				bidirectional_iterator & operator++()
				{
					if (_ptr == _management_node)
					{
						_ptr = _ptr->right;
						return (*this);
					}

					if (_ptr->right != _leaf)
					{
						_ptr = _ptr->right;
						while (_ptr->left != _leaf)
							_ptr = _ptr->left;
					}
					else
					{
						while (_ptr == _ptr->parent->right && _ptr != _ptr->parent->parent)
							_ptr = _ptr->parent;
						_ptr = _ptr->parent;
					}
					return (*this);
				}

				bidirectional_iterator	operator++(int)
				{
					bidirectional_iterator	tmp = *this;
					operator++();
					return (tmp);
				}

				bidirectional_iterator &	operator--()
				{
					if (_ptr == _management_node)
					{
						_ptr = _ptr->right;
						return (*this);
					}

					if (_ptr->left && _ptr->left!= _leaf)
					{
						_ptr = _ptr->left;
						while (_ptr->right != _leaf)
							_ptr = _ptr->right;
					}
					else
					{
						while (_ptr == _ptr->parent->left && _ptr != _ptr->parent->parent)
							_ptr = _ptr->parent;
						_ptr = _ptr->parent;
					}
					return (*this);
				}

				bidirectional_iterator operator--(int)
				{
					bidirectional_iterator tmp = *this;
					operator--();
					return (tmp);
				}

				Node	*getNode() const
				{
					return (_ptr);
				}

				Node	*getLeaf() const
				{
					return (_leaf);
				}

				Node	*getManagement() const
				{
					return (_management_node);
				}

		};

	template <class T>
		class	const_bidirectional_iterator
		{
			public:
				typedef	T const																					value_type;
				typedef Node<T>																					Node;
				typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type		difference_type;
				typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category	iterator_category;
				typedef value_type const*																		pointer;
				typedef value_type	const&																		reference;

			private:
				Node*	_ptr;
				Node*	_management_node;
				Node*	_leaf;

			public:
				const_bidirectional_iterator()											: _ptr(u_nullptr), _management_node(u_nullptr), _leaf(u_nullptr)				{};
				const_bidirectional_iterator(Node* ptr, Node* mn, Node* leaf)			: _ptr(ptr), _management_node(mn), _leaf(leaf)									{};
				const_bidirectional_iterator(const const_bidirectional_iterator &src)	: _ptr(src._ptr), _management_node(src._management_node), _leaf(src._leaf)		{};
				const_bidirectional_iterator(const bidirectional_iterator<T> &src)		: _ptr(src.getNode()), _management_node(src.getManagement()), _leaf(src.getLeaf())	{};

				const_bidirectional_iterator&	operator=(const const_bidirectional_iterator &rhs)
				{
					if (*this == rhs)
						return (*this);
					_ptr = rhs._ptr;
					_management_node = rhs._management_node;
					_leaf = rhs._leaf;
					return (*this);
				};
				const_bidirectional_iterator&	operator=(const bidirectional_iterator<T> &rhs)
				{
					if (*this == rhs)
						return (*this);
					_ptr = rhs.getNode();
					_management_node = rhs.getManagement();
					_leaf = rhs.getLeaf();
					return (*this);
				};

				virtual ~const_bidirectional_iterator() {};


				bool		operator==(const const_bidirectional_iterator &it) const	{return (this->_ptr == it._ptr);};
				bool		operator==(Node *ptr) const									{return (this->_ptr == ptr);};
				bool		operator==(const bidirectional_iterator<T> &it) const		{return (this->_ptr == it.getNode());};
				bool		operator!=(const const_bidirectional_iterator &it) const	{return (this->_ptr != it._ptr);};

				reference	operator*() const									{return (this->_ptr->data);};
				pointer		operator->() const									{return &operator*();};
				const_bidirectional_iterator & operator++()
				{
					if (_ptr == _management_node)
					{
						_ptr = _ptr->right;
						return (*this);
					}

					if (_ptr->right != _leaf)
					{
						_ptr = _ptr->right;
						while (_ptr->left != _leaf)
							_ptr = _ptr->left;
					}
					else
					{
						while (_ptr == _ptr->parent->right && _ptr != _ptr->parent->parent)
							_ptr = _ptr->parent;
						_ptr = _ptr->parent;
					}
					return (*this);
				}

				const_bidirectional_iterator	operator++(int)
				{
					const_bidirectional_iterator	tmp = *this;
					operator++();
					return (tmp);
				}

				const_bidirectional_iterator &	operator--()
				{
					if (_ptr == _management_node)
					{
						_ptr = _ptr->right;
						return (*this);
					}

					if (_ptr->left != _leaf)
					{
						_ptr = _ptr->left;
						while (_ptr->right != _leaf)
							_ptr = _ptr->right;
					}
					else
					{
						while (_ptr == _ptr->parent->left && _ptr != _ptr->parent->parent)
							_ptr = _ptr->parent;
						_ptr = _ptr->parent;
					}
					return (*this);
				}

				const_bidirectional_iterator operator--(int)
				{
					const_bidirectional_iterator tmp = *this;
					operator--();
					return (tmp);
				}
				Node*	getNode() const
				{
					return (_ptr);
				}
		};



		template <class T, class Key, class Val>
	class RedBlackTree
	{
		typedef T								pair_type;
		typedef Key								key_type;
		typedef Val								mapped_type;
		typedef ft::Node<T>						*NodePtr;
		typedef bidirectional_iterator<T>		iterator;
		typedef const_bidirectional_iterator<T>	const_iterator;
		typedef size_t							size_type;

		private:
			NodePtr		management_node;
			NodePtr		TNULL;
			size_type	_size;


			void	clear(NodePtr node)
			{
				if (node->left && node->left != TNULL)
					clear(node->left);
				if (node->right && node->right != TNULL)
					clear(node->right);
				if (node != management_node && node != TNULL)
					delete node;
			}

			void initializeNULLNode(NodePtr node, NodePtr parent)
			{
				node->data = node->data();
				node->parent = parent;
				node->left = NULL;
				node->right = NULL;
				node->color = 0;
			}

			// Preorder
			void preOrderHelper(NodePtr node)
			{
				if (node != TNULL)
				{
					std::cout << node->data << " ";
					preOrderHelper(node->left);
					preOrderHelper(node->right);
				}
			}

			// Inorder
			void inOrderHelper(NodePtr node) {
				if (node != TNULL) {
					inOrderHelper(node->left);
					std::cout << node->data << " ";
					inOrderHelper(node->right);
				}
			}

			// Post order
			void postOrderHelper(NodePtr node) {
				if (node != TNULL) {
					postOrderHelper(node->left);
					postOrderHelper(node->right);
					std::cout << node->data << " ";
				}
			}

			NodePtr searchTreeHelper(NodePtr node, key_type key) const
			{
				if (node == TNULL || key == node->data.first) {
					return node;
				}

				if (key < node->data.first) {
					return searchTreeHelper(node->left, key);
				}
				return searchTreeHelper(node->right, key);
			}

			// For balancing the tree after deletion
			void deleteFix(NodePtr x)
			{
				NodePtr s;

				while (x != management_node->parent && x->color == 0)
				{
					if (x == x->parent->left)
					{
						s = x->parent->right;
						if (s->color == 1)
						{
							s->color = 0;
							x->parent->color = 1;
							leftRotate(x->parent);
							s = x->parent->right;
						}

						if (s->left->color == 0 && s->right->color == 0)
						{
							s->color = 1;
							x = x->parent;
						}
						else
						{
							if (s->right->color == 0)
							{
								s->left->color = 0;
								s->color = 1;
								rightRotate(s);
								s = x->parent->right;
							}

							s->color = x->parent->color;
							x->parent->color = 0;
							s->right->color = 0;
							leftRotate(x->parent);
							x = management_node->parent;
						}
					}
					else
					{
						s = x->parent->left;
						if (s->color == 1)
						{
							s->color = 0;
							x->parent->color = 1;
							rightRotate(x->parent);
							s = x->parent->left;
						}
						if (s->right->color == 0 && s->right->color == 0)
						{
							s->color = 1;
							x = x->parent;
						}
						else
						{
							if (s->left->color == 0)
							{
								s->right->color = 0;
								s->color = 1;
								leftRotate(s);
								s = x->parent->left;
							}
							s->color = x->parent->color;
							x->parent->color = 0;
							s->left->color = 0;
							rightRotate(x->parent);
							x = management_node->parent;
						}
					}
				}
				x->color = 0;
			}

			void rbTransplant(NodePtr u, NodePtr v) {
				if (u->parent == management_node) {
					management_node->parent = v;
				} else if (u == u->parent->left) {
					u->parent->left = v;
				} else {
					u->parent->right = v;
				}
				v->parent = u->parent;
			}

			void deleteNodeHelper(NodePtr node, pair_type val)
			{
				NodePtr z = TNULL;
				NodePtr x, y;
				while (node != TNULL)
				{
					if (node->data == val)
						z = node;
					if (node->data <= val)
						node = node->right;
					else
						node = node->left;
				}
				if (z == TNULL)
					return;
				y = z;
				int y_original_color = y->color;
				if (z->left == TNULL)
				{
					x = z->right;
					rbTransplant(z, z->right);
				}
				else if (z->right == TNULL)
				{
					x = z->left;
					rbTransplant(z, z->left);
				}
				else
				{
					y = minimum(z->right);
					y_original_color = y->color;
					x = y->right;
					if (y->parent == z)
						x->parent = y;
					else
					{
						rbTransplant(y, y->right);
						y->right = z->right;
						y->right->parent = y;
					}

					rbTransplant(z, y);
					y->left = z->left;
					y->left->parent = y;
					y->color = z->color;
				}
//				ft::Node<T>::DG_tree(management_node->parent);
				delete z;
				if (y_original_color == 0)
					deleteFix(x);
				_size--;
				management_node->right = findMax();
				management_node->left = findMin();
				//ft::Node<T>::DG_tree(management_node->parent);
			}

			// For balancing the tree after insertion
			void insertFix(NodePtr k)
			{
				NodePtr u;
				while (k->parent->color == 1)
				{
					if (k->parent == k->parent->parent->right)
					{
						u = k->parent->parent->left;
						if (u->color == 1)
						{
							u->color = 0;
							k->parent->color = 0;
							k->parent->parent->color = 1;
							k = k->parent->parent;
						}
						else
						{
							if (k == k->parent->left)
							{
								k = k->parent;
								rightRotate(k);
							}
							k->parent->color = 0;
							k->parent->parent->color = 1;
							leftRotate(k->parent->parent);
						}
					}
					else
					{
						u = k->parent->parent->right;
						if (u->color == 1)
						{
							u->color = 0;
							k->parent->color = 0;
							k->parent->parent->color = 1;
							k = k->parent->parent;
						}
						else
						{
							if (k == k->parent->right)
							{
								k = k->parent;
								leftRotate(k);
							}
							k->parent->color = 0;
							k->parent->parent->color = 1;
							rightRotate(k->parent->parent);
						}
					}
					if (k == management_node->parent)
						break;
				}
				management_node->parent->color = 0;
			}



		public:
			RedBlackTree()
			{
				TNULL = new Node<pair_type>();
				TNULL->color = 0;
				TNULL->left = NULL;
				TNULL->right = NULL;
				management_node = new Node<pair_type>;
				management_node->parent = TNULL;
				management_node->right = TNULL;
				management_node->left = TNULL;
				_size = 0;
			}

			RedBlackTree (RedBlackTree const & src)
				:  management_node(NULL), TNULL(NULL)
			{
				TNULL = new Node<pair_type>();
				TNULL->color = 0;
				TNULL->left = NULL;
				TNULL->right = NULL;
				management_node = new Node<pair_type>;
				management_node->parent = TNULL;
				management_node->right = TNULL;
				management_node->left = TNULL;
				_size = 0;
				*this = src;
			}

			~RedBlackTree()
			{
				clear(management_node->parent);
				delete management_node;
				delete TNULL;
			};

			RedBlackTree &	operator= (RedBlackTree const & rhs)
			{
				const_iterator ite = rhs.end();

				clear();
				for (const_iterator it = rhs.begin(); it != ite; it++)
				{
					insert(*it);
				}
				_size = rhs._size;
//				ft::Node<T>::DG_tree(management_node->parent);
				return *this;
			}

			iterator begin()
			{
				return (iterator(findMin(), getManagement(), getLeaf()));
			};

			const_iterator begin() const
			{
				return (const_iterator(findMin(), getManagement(), getLeaf()));
			};

			iterator end()
			{
				return (iterator(getManagement(), getManagement(), getLeaf()));
			};
			const_iterator end() const
			{
				return (const_iterator(getManagement(), getManagement(), getLeaf()));
			};

			void preorder() {
				preOrderHelper(this->management_node->parent);
			}

			void inorder() {
				inOrderHelper(this->management_node->parent);
			}

			void postorder() {
				postOrderHelper(this->management_node->parent);
			}

			NodePtr searchTree(key_type key) const
			{
				return searchTreeHelper(this->management_node->parent, key);
			}

			NodePtr minimum(NodePtr node) {
				while (node->left != TNULL) {
					node = node->left;
				}
				return node;
			}

			NodePtr maximum(NodePtr node) {
				while (node->right != TNULL) {
					node = node->right;
				}
				return node;
			}

			NodePtr	findMax() const
			{
				NodePtr node = management_node->parent;

				if (management_node->parent == TNULL)
					return management_node;
				while (node->right != TNULL)
					node = node->right;
				return node;
			}

			NodePtr findMin() const
			{
				NodePtr node = management_node->parent;

				if (management_node->parent == TNULL)
					return management_node;
				while (node->left != TNULL)
					node = node->left;
				return node;

			}

			NodePtr successor(NodePtr x)
			{
				if (x->right != TNULL)
					return minimum(x->right);

				NodePtr y = x->parent;
				while (y != management_node && x == y->right)
				{
					x = y;
					y = y->parent;
				}
				return y;
			}

			NodePtr predecessor(NodePtr x)
			{
				if (x->left != TNULL)
					return maximum(x->left);

				NodePtr y = x->parent;

				while (y != management_node && x == y->left)
				{
					x = y;
					y = y->parent;
				}
				return y;
			}

			void leftRotate(NodePtr x)
			{
				NodePtr y = x->right;

				x->right = y->left;
				if (y->left != TNULL)
					y->left->parent = x;
				y->parent = x->parent;
				if (x->parent == management_node)
					this->management_node->parent = y;
				else if (x == x->parent->left)
					x->parent->left = y;
				else
					x->parent->right = y;
				y->left = x;
				x->parent = y;
			}

			void rightRotate(NodePtr x)
			{
				NodePtr y = x->left;

				x->left = y->right;
				if (y->right != TNULL)
				{
					y->right->parent = x;
				}
				y->parent = x->parent;
				if (x->parent == management_node)
				{
					management_node->parent = y;
				}
				else if (x->parent && x == x->parent->right)
				{
					x->parent->right = y;
				}
				else
				{
					x->parent->left = y;
				}
				y->right = x;
				x->parent = y;
			}

			// Inserting a node
			NodePtr insert(pair_type val)
			{
				NodePtr node = new Node<pair_type>(val);
				node->parent = NULL;
				node->left = TNULL;
				node->right = TNULL;
				node->color = 1;

				NodePtr y = NULL;
				NodePtr x = this->management_node->parent;

				while (x != TNULL)
				{
					y = x;
					if (node->data < x->data)
						x = x->left;
					else
						x = x->right;
				}
				node->parent = y;
				if (y == NULL)
					management_node->parent = node;
				else if (node->data < y->data)
					y->left = node;
				else
					y->right = node;
				if (node->parent == NULL)
				{
					node->parent = management_node;
					management_node->right = node;
					management_node->left = node;
					node->color = 0;
					_size++;
//					ft::Node<T>::DG_tree(management_node->parent);
					return (node);
				}
				if (node->parent->parent == management_node)
				{
					if (node == findMax())
					{
						management_node->right = node;
						node->right = TNULL;
					}
					else if (node == findMin())
						management_node->left = node;
					_size++;
//					ft::Node<T>::DG_tree(management_node->parent);
					return (node);
				}
				insertFix(node);
				if (node == findMax())
					management_node->right = node;
				else if (node == findMin())
					management_node->left = node;
				_size++;
//				ft::Node<T>::DG_tree(management_node->parent);
				return (node);

			}

			void	clear()
			{
				clear(management_node->parent);
				delete management_node;
				delete TNULL;
				TNULL = new Node<pair_type>();
				TNULL->color = 0;
				TNULL->left = NULL;
				TNULL->right = NULL;
				management_node = new Node<pair_type>;
				management_node->parent = TNULL;
				management_node->right = TNULL;
				management_node->left = TNULL;
				_size = 0;
			}

			NodePtr getRoot() const
			{
				return this->management_node->parent;
			}

			NodePtr getManagement() const
			{
				return this->management_node;
			}

			NodePtr getLeaf() const
			{
				return this->TNULL;
			}

			size_type	getSize() const
			{
				return this->_size;
			}

			void deleteNode(key_type data)
			{
				deleteNodeHelper(this->management_node->parent, data);
			}
	};
}

#endif
