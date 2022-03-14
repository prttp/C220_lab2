#pragma once
template<typename T>
class MyQueue {
	const size_t delta = 5; //на сколько увеличиваем емкость при перераспределении памяти
	T* m_p{ new T[delta]{} }; //указатель на начало динамического массива
	size_t m_size{}; //актуальное количество элементов в очереди
	size_t m_cap{delta}; //емкость (сколько выделено памяти)
	size_t m_begin{}; //индекс первого элемента в очереди (это тот элемент, который можно извлечь из очереди с помощью pop())
	size_t m_end{}; // индекс первого свободного элемента в очереди (это тот элемент, в который можно присвоить новое значение с помощью push())
public:
	template <typename T> class MyQueueIterator
	{
		const MyQueue<T>* m_c{};
		int m_ind{};

	public:
		MyQueueIterator() = default;

		MyQueueIterator(const MyQueue<T>* c_ptr, int index) :
			m_c(c_ptr),
			m_ind(index)
		{
		}

		T& operator*()
		{
			return m_c->m_p[m_ind];
		}

		bool operator !=(const MyQueueIterator<T>& it) const
		{
			return (it.m_ind != this->m_ind) || (it.m_c != this->m_c);
		}

		bool operator ==(const MyQueueIterator<T>& it) const
		{
			return (it.m_ind == this->m_ind) && (it.m_c == this->m_c);
		}

		MyQueueIterator<T>& operator++()
		{
			++m_ind;

			if (m_ind == m_c->m_cap)
				m_ind = 0;

			return *this;
		}

		MyQueueIterator<T> operator++(int)
		{
			MyQueueIterator<T> res(m_c, m_ind);
			++res.m_ind;

			if (res.m_ind == m_c->m_cap)
				res.m_ind = 0;

			return this;
		}

	};

	MyQueue() = default;
	MyQueue(const std::initializer_list<T>& data) {
		
		m_size = data.size();
		m_cap = m_size + delta;
		m_p = new T[m_cap];
		m_begin = 0;
		m_end = 0;
		for (const auto& e : data)
		{
			m_p[m_end] = e;
			m_end++;
		}
	};
	MyQueue(const MyQueue& s)
	{
		this->m_size = s.m_size;
		this->m_cap = this->m_size + delta;
		m_p = new T[m_cap];

		int i = 0;
		for (const auto& e : s)
		{
			m_p[i] = e;
			++i;
		};

		this->m_begin = 0;
		this->m_end = i;
	};
	MyQueue(MyQueue&& s) : m_begin(s.m_begin), m_end(s.m_end),m_size(s.m_size), m_cap(s.m_cap) {
		m_p = s.m_p;

		s.m_begin = 0;
		s.m_end = 0;
		s.m_size = 0;
		s.m_cap = 0;
		s.m_p = nullptr;
	}

	void push(const T& val) {
		
		m_p[m_end] = val;
		++m_end;
		++m_size;
		if (m_end == m_cap) m_end = 0;
		if (m_size == m_cap)
			resize();
		
	};
	void push(T&& val)
	{
		m_p[m_end] = std::move(val);
		++m_end;
		++m_size;
		if (m_end == m_cap) m_end = 0;
		if (m_size == m_cap)
			resize();
	}
	void resize() {
		m_cap +=delta;

		T* new_m_p = new T[m_cap];

		size_t ni = m_begin;
		for (int i = 0; i < m_size; ++i)
		{
			new_m_p[i] = std::move(m_p[ni]);
			ni++;
			if (ni == m_cap)
				ni = 0;
		}

		delete[] m_p;
		m_p = new_m_p;
		m_begin = 0;
		m_end = m_size;
	};
	T pop()
	{
		m_size = m_size - 1;

		T result = m_p[m_begin];

		/*if (m_begin == m_cap)
		{
			m_begin = 0;
		}
		else
		{
			m_begin++;
		}*/
		m_begin++;
		return result;
	}
	MyQueue& operator=(const MyQueue& s)
	{
		if (this == &s)
			return *this;

		if (this->m_cap < s.m_size)
		{
			delete[] this->m_p;

			m_p = new T[s.m_size+delta];
		}

		int i = 0;
		for (const auto& e : s)
		{
			m_p[i] = e;
			i++;
			if (i == s.m_size) { break; }
		}

		this->m_cap = s.m_size+delta;
		this->m_size = s.m_size;
		this->m_begin = s.m_begin;
		this->m_end = s.m_end;

		return *this;
	}
	MyQueue& operator=(MyQueue&& s)
	{
		if (this == &s)
			return *this;

		delete[] this->m_p;

		this->m_p = s.m_p;
		s.m_p = nullptr;
		this->m_cap = s.m_cap;
		s.m_cap = 0;
		this->m_size = s.m_size;
		s.m_size = 0;
		this->m_begin = s.m_begin;
		s.m_begin = 0;
		this->m_end = s.m_end;
		s.m_end = 0;

		return *this;
	}
	~MyQueue()
	{
		delete[] m_p;
	}
	MyQueueIterator<T> begin()
	{
		return  MyQueueIterator<T>(this, m_begin);
	}

	MyQueueIterator<T> begin() const
	{
		return  MyQueueIterator<T>(this, m_begin);
	}


	const MyQueueIterator<T> cbegin() const
	{
		return  MyQueueIterator<T>(this, m_begin);
	}

	MyQueueIterator<T> end()
	{
		return  MyQueueIterator<T>(this, m_end);
	}

	MyQueueIterator<T> end() const
	{
		return  MyQueueIterator<T>(this, m_end);
	}

	const MyQueueIterator<T> cend() const
	{
		return  MyQueueIterator<T>(this, m_end);
	}
	MyQueue(const int num, const T& e)
	{
		m_size = num;
		m_cap = m_size + delta;
		m_p = new T[m_cap];
		m_begin = 0;

		for (m_end = 0; m_end < num; ++m_end)
		{
			m_p[m_end] = e;
		}
	}
};