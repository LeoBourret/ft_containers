	template <class T>
		class	bidirectional_iterator
		{
			public:
				typedef	T																						value_type;
				typedef ft::Node<T>																				Node;
				typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type		difference_type;
				typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category	iterator_category;
				typedef value_type*																				pointer;
				typedef value_type&																				reference;

			private:
				Node*	_ptr;
				Node*	_management_node;
				Node*	_leaf;

			public:
				bidirectional_iterator()									: _ptr(u_nullptr), _management_node(u_nullptr), _leaf(u_nullptr)			{};
				bidirectional_iterator(Node* ptr, Node* mn, Node* leaf)		: _ptr(ptr), _management_node(mn), _leaf(leaf)								{};
				bidirectional_iterator(const bidirectional_iterator &src)	: _ptr(src._ptr), _management_node(src._management_node), _leaf(src._leaf)	{};

				bidirectional_iterator&	operator=(const bidirectional_iterator &rhs)
				{
					if (*this == rhs)
						return (*this);
					_ptr = rhs._ptr;
					return (*this);
				};
				virtual ~bidirectional_iterator() {};


				bool		operator==(const bidirectional_iterator &it) const	{return (this->_ptr == it._ptr);};
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
						while (_ptr->left)
							_ptr = _ptr->left;
					}
					else
					{
						while (_ptr == _ptr->parent->right && _ptr != _ptr->parent)
							_ptr = _ptr->parent;
						_ptr = _ptr->parent;
					}
					return (*this);
				}
				bidirectional_iterator	operator++(int)
				{
					bidirectional_iterator	tmp = *this;
					operato++();
					return (tmp);
				}
				bidirectional_iterator &	operator--()
				{
					if (_ptr == _management_node)
					{
						_ptr = _ptr->right;
						return (*this);
					}
					if (_ptr->left != _leaf)
					{
						_ptr = _ptr->left;
						while (_ptr->right)
							_ptr = _ptr->right;
					}
					else
					{
						while (_ptr == _ptr->parent->left && _ptr != _ptr->parent)
							_ptr = _ptr->parent;
						_ptr = _ptr->parent;
					}
					return (*this);
				}
				bidirectional_iterator	operator--(int)
				{
					bidirectional_iterator	tmp(*this);
					operator--();
					return (tmp);
				}

				Node	*getNode()
				{
					return (_ptr);
				}

				Node	*getLeaf()
				{
					return (_leaf);
				}
		};

