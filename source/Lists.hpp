# ifndef BUW_LIST_HPP
# define BUW_LIST_HPP
# include <cstddef>

// List .hpp
template <typename T>
struct List;

template <typename T>
struct ListNode
{
	ListNode(): m_value(), m_prev(nullptr), m_next(nullptr){}
	ListNode(T const&v, ListNode*prev, ListNode*next)
	: m_value(v), m_prev(prev), m_next(next)
	{}
	T m_value;
	ListNode * m_prev;
	ListNode * m_next;
};


template <typename T>
struct ListConstIterator
{
	friend class List <T >;
	// not implemented yet
	private :
	ListNode <T >* m_node = nullptr ;
};


template <typename T>
List<T> reverse(List<T> a)
{
	a.reverse();
	return a;
};

template <typename T>
List<T> copy(List<T> a)
{
	return a;
};





template <typename T>
struct ListIterator
{
	typedef ListIterator <T> Self;
	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;
	typedef ptrdiff_t difference_type;
	typedef std :: forward_iterator_tag iterator_category;

	friend class List <T>;

	ListIterator(): 
		m_node(nullptr){}

	ListIterator(ListNode <T>*n):
		m_node(n) {}

	reference operator*() const
		{return m_node->m_value;}

	pointer operator->() const
		{return *m_node;}

	Self& operator++() 
		{
			if (m_node)
			    m_node = m_node->m_next;
			return *this;
		}

	Self& operator--() 
		{
			m_node = m_node->m_prev;
			return *this;
		}

	Self operator++(int) 
	{
		Self tmp = *this;
		++(*this);
		return tmp;
	}

	bool operator==( const Self & x) const 
		{return m_node == x.m_node;}

	bool operator!=( const Self & x) const 
		{return m_node != x.m_node;}

	Self next() const
	{
		if (m_node)
			return ListIterator ( m_node -> m_next );
		else
			return ListIterator (nullptr);
	}

private:
	// The Node the iterator is pointing to
	ListNode <T >* m_node = nullptr ;
};



template <typename T>
bool operator==(List<T>const& xs , List<T>const& ys)
{	

		if (xs.size() != ys.size())
		{	
			return false;
		}

		std::cout <<"Size matches, start comparing:   " << "\n";
		ListIterator<T> a = ys.begin();
		for (auto i = xs.begin(); i != xs.end(); ++i, ++a)
		{	
			std::cout << *a <<"   " << *i << "\n";
			if (*i != *a)
			{
				return false;
			}
			
		}
		return true;
}


template < typename T >
bool operator !=( List <T > const & xs , List <T > const & ys )
{
	return !(xs==ys);
}



template <typename T>
class List
{
public:
	typedef T value_type ;
	typedef T* pointer ;
	typedef const T* const_pointer ;
	typedef T& reference ;
	typedef const T& const_reference ;
	typedef ListIterator<T> iterator ;
	typedef ListConstIterator<T> const_iterator ;
	friend class ListIterator<T>;
	friend class ListConstIterator<T>;


	List():
		m_size{0},
		m_first{nullptr},
		m_last{nullptr}
		 {}
	
	List(List const& a):
		m_size{0},
		m_first{nullptr},
		m_last{nullptr}
		
		{
			if (!a.empty())
			{
				for (auto i = a.begin(); i != a.end(); ++i)
				{
					push_back(*i);
				}
			}
		}

	friend void swap(List& a, List& b) // swap Funktion für zuweisungsoperator.
		{a.swap(b);}

	List<T> (List<T> && inlist)
		: m_size(inlist.m_size),
		m_first(inlist.m_first),
		m_last(inlist.m_last)

	{
		inlist.m_size = 0;
		inlist.m_first = nullptr;
		inlist.m_last = nullptr;
	}

	~List<T> () {clear();}				//Destruktor
	
	std::size_t size() const
		{
			return m_size;
		}

	bool empty () const
		{return size()== 0;}

	void push_front(T const& a)
	{
		if (empty())
		{
			ListNode<T>* v1 =new ListNode<T>(a, nullptr, nullptr);
			m_first = v1;
			m_last = v1;
		}

		else
		{
			ListNode<T>* v2 =new ListNode<T>(a, nullptr, m_first);
			m_first->m_prev = v2;
			m_first = v2;
		}
		m_size+=1;
	}


	void push_back(T const& a)
	{
		if (empty())
		{
			ListNode<T>* v1 =new ListNode<T>(a, nullptr, nullptr);
			m_first = v1;
			m_last = v1;
			
		}
		else
		{
			ListNode<T>* v3 =new ListNode<T>(a, m_last, nullptr);
			m_last->m_next = v3;
			m_last = v3;
		}
		m_size+=1;	
	}

	void pop_front()
	{	
		if (empty())
		{
        	throw std::out_of_range("Can't pop from empty list");
		}

		if (m_size == 1)
		{
			delete m_first;
			m_first = nullptr;
	    	m_last = nullptr;
	    	m_size -= 1;
		}
		
		else
		{
			auto *n = m_first->m_next;

			n->m_prev = nullptr;
			

			delete m_first;
			
			m_first = n;

			m_size -= 1;	
		}
	}

	void pop_back()
	{	
		if (empty())
		{
        throw std::out_of_range("Can't pop from empty list");
		}

		if (m_size == 1)
		{
			delete m_first;
			m_first = nullptr;
	    	m_last = nullptr;
	    	m_size -= 1;
		}
		
		else
		{
	        auto *n = m_last->m_prev;
	        n->m_next = nullptr;

	        delete m_last;

	        m_last = n;
	        m_size -= 1;
    	}
    }

	void clear()
	{
		while (!empty())
	    {	
		    pop_front();
	    }           
    }


   iterator insert(iterator pos, const T& value )
   {

		ListNode<T>* v1 = new ListNode<T>(value, pos.m_node->m_prev, pos.m_node);
		pos.m_node->m_prev->m_next = v1;
		pos.m_node->m_prev = v1;
		m_size+=1;
		return ListIterator<T> (v1);
	}

	void reverse()
	{	
		for (iterator i = begin(); i != end(); --i)
		{	
			std::swap(i.m_node->m_prev, i.m_node->m_next);
		}
		std::swap(m_first, m_last);
	};
	


	T const& front() const
	{
		return m_first->m_value;
	}

	T const& back() const
	{
		return m_last->m_value;
	}

	T& front()
	{
		return m_first->m_value;
	}

	T& back()
	{
		return m_last->m_value;
	}

	iterator begin() const
	{
		return ListIterator<T>(m_first);
	}

	iterator end() const
	{
		return ListIterator<T>();
	}


// not implemented yet
private:
	std::size_t m_size = 0;
	ListNode<T>* m_first = nullptr ;
	ListNode<T>* m_last = nullptr ;
};

# endif 	// # define BUW_LIST_HPP