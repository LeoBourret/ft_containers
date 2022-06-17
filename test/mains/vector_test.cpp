#include "../../containers/vector.hpp"
#include <vector>

#ifdef STD
	using namespace std;
#elif FT
	using namespace ft;
#endif

template <class T = int>
void	print_vector(vector<T> to_print)
{
	for (typename vector<T>::iterator it = to_print.begin(); it != to_print.end(); ++it)
		std::cout << *it << " ";
	std::cout << "\n";
}

void	constructor_test()
{
	std::cout << "\nCONSTRUCTOR TEST\n";
	// constructors used in the same order as described above:
	vector<int> first;                                // empty vector of ints
	vector<int> second (4,100);                       // four ints with value 100
	vector<int> third (second.begin(),second.end());  // iterating through second
	vector<int> fourth (third);                       // a copy of third

	// the iterator constructor can also be used to construct from arrays:
	int myints[] = {16,2,77,29};
	vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

	std::cout << "The contents of fifth are:";
	for (vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

void	operator_equal_test()
{
	std::cout << "\nOPERATOR_EQUAL TEST\n";

	vector<int> foo (3,0);
	vector<int> bar (5,0);

	bar = foo;
	foo = vector<int>();

	std::cout << "Size of foo: " << int(foo.size()) << '\n';
	std::cout << "Size of bar: " << int(bar.size()) << '\n';
}

void	begin_test()
{
	std::cout << "\nBEGIN_TEST\n";
	vector<int> myvector;
	for (int i=1; i<=5; i++) myvector.push_back(i);

	std::cout << "myvector contains:";
	for (vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

void	end_test()
{
	std::cout << "\nEND_TEST\n";
	vector<int> myvector;
	for (int i=1; i<=5; i++) myvector.push_back(i);

	std::cout << "myvector contains:";
	for (vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

void	rbegin_test()
{

	std::cout << "\nRBEGIN_TEST\n";
	vector<int> myvector (5);  // 5 default-constructed ints

	int i=0;

	vector<int>::reverse_iterator rit = myvector.rbegin();
	for (; rit!= myvector.rend(); ++rit)
		*rit = ++i;

	std::cout << "myvector contains:";
	for (vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

void	rend_test()
{

	std::cout << "\nREND_TEST\n";
	vector<int> myvector (5);  // 5 default-constructed ints

	vector<int>::reverse_iterator rit = myvector.rbegin();

	int i=0;
	for (rit = myvector.rbegin(); rit!= myvector.rend(); ++rit)
		*rit = ++i;

	std::cout << "myvector contains:";
	for (vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

void	size_test()
{
	std::cout << "\nSIZE_TEST\n";
	vector<int> myints;
	std::cout << "0. size: " << myints.size() << '\n';

	for (int i=0; i<10; i++) myints.push_back(i);
	std::cout << "1. size: " << myints.size() << '\n';

	myints.insert (myints.end(),10,100);
	std::cout << "2. size: " << myints.size() << '\n';

	myints.pop_back();
	std::cout << "3. size: " << myints.size() << '\n';
}

void	max_size_test()
{
	std::cout << "\nMAX_SIZE TEST\n";
	vector<int> myvector;

	// set some content in the vector:
	for (int i=0; i<100; i++) myvector.push_back(i);

	std::cout << "size: " << myvector.size() << "\n";
	std::cout << "capacity: " << myvector.capacity() << "\n";
	std::cout << "max_size: " << myvector.max_size() << "\n";
}

void	resize_test(void)
{
	std::cout << "\nRESIZE TEST\n";
	vector<int> myvector;

  // set some initial content:
  for (int i=1;i<10;i++) myvector.push_back(i);

  myvector.resize(5);
  myvector.resize(8,100);
  myvector.resize(12);

  std::cout << "myvector contains:";
  for (unsigned long i=0;i<myvector.size();i++)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';
}

void	capacity_test()
{
	std::cout << "\nCAPACITY TESTS\n";
	vector<int> myvector;

	// set some content in the vector:
	for (int i=0; i<100; i++) myvector.push_back(i);

	std::cout << "size: " << (int) myvector.size() << '\n';
	std::cout << "capacity: " << (int) myvector.capacity() << '\n';
	std::cout << "max_size: " << (int) myvector.max_size() << '\n';
}

void	empty_test()
{
	std::cout << "\nEMPTY TEST\n";
	vector<int> myvector;
	int sum (0);

	for (int i=1;i<=10;i++)
		myvector.push_back(i);

	while (!myvector.empty())
	{
		sum += myvector.back();
		myvector.pop_back();
	}

	std::cout << "total: " << sum << '\n';
}

void	reserve_test()
{
	std::cout << "\nRESERVE TEST\n";
	vector<int>::size_type sz;

  vector<int> foo;
  sz = foo.capacity();
  std::cout << "making foo grow:\n";
  for (int i=0; i<100; ++i) {
    foo.push_back(i);
    if (sz!=foo.capacity()) {
      sz = foo.capacity();
      std::cout << "capacity changed: " << sz << '\n';
    }
  }

  vector<int> bar;
  sz = bar.capacity();
  bar.reserve(100);   // this is the only difference with foo above
  std::cout << "making bar grow:\n";
  for (int i=0; i<100; ++i) {
    bar.push_back(i);
    if (sz!=bar.capacity()) {
      sz = bar.capacity();
      std::cout << "capacity changed: " << sz << '\n';
    }
  }
}

void	operator_bracket_test()
{
	std::cout << "\nOPERATOR_BRACKET TESTS\n";
	vector<int> myvector (10);   // 10 zero-initialized elements

	vector<int>::size_type sz = myvector.size();

	// assign some values:
	for (unsigned i=0; i<sz; i++) myvector[i]=i;

	// reverse vector using operator[]:
	for (unsigned i=0; i<sz/2; i++)
	{
		int temp;
		temp = myvector[sz-1-i];
		myvector[sz-1-i]=myvector[i];
		myvector[i]=temp;
	}

	std::cout << "myvector contains:";
	for (unsigned i=0; i<sz; i++)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';
}

void	at_test()
{
	std::cout << "\nAT TESTS\n";

	vector<int> myvector (10);   // 10 zero-initialized ints

	// assign some values:
	for (unsigned i=0; i<myvector.size(); i++)
		myvector.at(i)=i;

	std::cout << "myvector contains:";
	for (unsigned i=0; i<myvector.size(); i++)
		std::cout << ' ' << myvector.at(i);
	std::cout << '\n';
}

void	front_test()
{
	std::cout << "\nFRONT TESTS\n";
	vector<int> myvector;

  myvector.push_back(78);
  myvector.push_back(16);

  // now front equals 78, and back 16

  myvector.front() -= myvector.back();

  std::cout << "myvector.front() is now " << myvector.front() << '\n';
}

void	back_test()
{
	std::cout << "\nBACK TESTS\n";
	  vector<int> myvector;

  myvector.push_back(10);

  while (myvector.back() != 0)
  {
    myvector.push_back ( myvector.back() -1 );
  }

  std::cout << "myvector contains:";
  for (unsigned i=0; i<myvector.size() ; i++)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';
}


void	assign_test()
{
	vector<int> first;
	vector<int> second;
	vector<int> third;
	vector<int>::iterator it;
	int					int_arr[] = {1313, 14, 92};

	std::cout << "\nASSIGN TEST\n";
	first.assign(12, 42);
	it = first.begin() + 1;
	second.assign(it, first.end() - 1);
	third.assign(int_arr, int_arr + 3);

	print_vector<int>(first);
	print_vector<int>(second);
	print_vector<int>(third);
}

void	push_back_test()
{
	std::cout << "\nPUSH_BACK TEST\n";

	vector<int>				test;
	vector<int>::iterator	it;
	int						n;
	int						i;

	do
	{
		n = rand() % 40000;
		test.push_back(n);
	} while (test.size() < 40);
	it = test.begin();
	for (; it != test.end();  ++it)
	{
		i = 0;
		std::cout << *it << " ";
		if (i == 9)
		{
			std::cout << "\n";
		}
		i++;
	}
	std::cout << "\n";
}
void	pop_back_test()
{
	std::cout << "\nPOP_BACK TEST\n";
	vector<int> myvector;
	int sum (0);

	myvector.push_back (100);
	myvector.push_back (200);
	myvector.push_back (300);

	while (!myvector.empty())
	{
		sum+=myvector.back();
		myvector.pop_back();
	}
	std::cout << "The elements of myvector add up to " << sum << '\n';
}

void	insert_test()
{
	std::cout << "\nINSERT TEST\n";
  std::vector<int> myvector (3,100);
  std::vector<int>::iterator it;

  it = myvector.begin();
  it = myvector.insert ( it , 200 );

  myvector.insert (it,2,300);

  // "it" no longer valid, get a new one:
  it = myvector.begin();

  std::vector<int> anothervector (2,400);
  myvector.insert (it+2,anothervector.begin(),anothervector.end());

  int myarray [] = { 501,502,503 };
  myvector.insert (myvector.begin(), myarray, myarray+3);

  std::cout << "myvector contains:";
  for (it=myvector.begin(); it<myvector.end(); it++)
    std::cout << ' ' << *it;
  std::cout << '\n';
}

void	erase_test()
{
	std::cout << "\nERASE TEST\n";
	vector<int> myvector;

	// set some values (from 1 to 10)
	for (int i=1; i<=10; i++) myvector.push_back(i);

	// erase the 6th element
	myvector.erase (myvector.begin()+5);

	// erase the first 3 elements:
	myvector.erase (myvector.begin(),myvector.begin()+3);

	std::cout << "myvector contains:";
	for (unsigned i=0; i<myvector.size(); ++i)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';
}

void	swap_test()
{
	std::cout << "\nSWAP TEST\n";
	vector<int> foo (3,100);   // three ints with a value of 100
	vector<int> bar (5,200);   // five ints with a value of 200

	foo.swap(bar);

	std::cout << "foo contains:";
	for (unsigned i=0; i<foo.size(); i++)
		std::cout << ' ' << foo[i];
	std::cout << '\n';

	std::cout << "bar contains:";
	for (unsigned i=0; i<bar.size(); i++)
		std::cout << ' ' << bar[i];
	std::cout << '\n';
}

void	clear_test()
{
	std::cout << "\nCLEAR TEST\n";
	vector<int> foo (3,100);   // three ints with a value of 100
	vector<int> bar (5,200);   // five ints with a value of 200

	foo.swap(bar);

	std::cout << "foo contains:";
	for (unsigned i=0; i<foo.size(); i++)
		std::cout << ' ' << foo[i];
	std::cout << '\n';

	std::cout << "bar contains:";
	for (unsigned i=0; i<bar.size(); i++)
		std::cout << ' ' << bar[i];
	std::cout << '\n';
}

void	get_allocator_test()
{
	std::cout << "\nGET_ALLOCATOR TEST\n";
	vector<int> myvector;
	int * p;
	unsigned int i;

	// allocate an array with space for 5 elements using vector's allocator:
	p = myvector.get_allocator().allocate(5);

	// construct values in-place on the array:
	for (i=0; i<5; i++) myvector.get_allocator().construct(&p[i],i);

	std::cout << "The allocated array contains:";
	for (i=0; i<5; i++) std::cout << ' ' << p[i];
	std::cout << '\n';

	// destroy and deallocate:
	for (i=0; i<5; i++) myvector.get_allocator().destroy(&p[i]);
	myvector.get_allocator().deallocate(p,5);

}

int	main()
{
	constructor_test();
	operator_equal_test();
	begin_test();
	end_test();
	rbegin_test();
	rend_test();
	size_test();
	max_size_test();
	resize_test();
	capacity_test();
	empty_test();
	reserve_test();
	operator_bracket_test();
	at_test();
	front_test();
	back_test();
	assign_test();
	push_back_test();
	pop_back_test();
	insert_test();
	erase_test();
	swap_test();
	clear_test();
	get_allocator_test();
}












