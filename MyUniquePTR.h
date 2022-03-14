#pragma once
template <typename T> class MyUniquePTR
{
	T* m_ptr{};
public:
	MyUniquePTR() = default;

	MyUniquePTR(T* ptr) :
		m_ptr(ptr)
	{
	}

	T* operator->()
	{
		return m_ptr;
	}

	T& operator*()
	{
		return *m_ptr;
	}

	const T* operator->() const
	{
		return m_ptr;
	}

	const T& operator*() const
	{
		return *m_ptr;
	}

	operator bool() const
	{
		return m_ptr != nullptr;
	}

	MyUniquePTR& operator=(const MyUniquePTR&) = delete;

	MyUniquePTR(const MyUniquePTR&) = delete;

	MyUniquePTR(MyUniquePTR&& p) noexcept
	{
		if (p.m_ptr != m_ptr)
		{
			m_ptr = p.m_ptr;
			p.m_ptr = nullptr;
		}
	}
	

	MyUniquePTR& operator=(MyUniquePTR&& p) noexcept
	{
		if (p.m_ptr != m_ptr)
		{
			if (m_ptr) { delete m_ptr; }

			m_ptr = p.m_ptr;
			p.m_ptr = nullptr;
		}
		return *this;
	}

	~MyUniquePTR() { delete m_ptr; }
	std::string GetString() {
		return std::string(*m_ptr);
	}
};