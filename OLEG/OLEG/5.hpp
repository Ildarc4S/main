#pragma once

#include <iostream>

// unique_ptr
// shared_ptr
// weak_ptr

template <typename T>
class SmartPtr
{
public:
	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;
	typedef unsigned int count_type;

	SmartPtr();
	SmartPtr(pointer const obj);
	SmartPtr(const SmartPtr& sp);
	~SmartPtr();

	pointer get() const;
	count_type count() const;

	void swap(SmartPtr& sp);
	void reset();

	SmartPtr& operator=(const SmartPtr& sp);
	operator bool() const;

private:
	pointer obj_;
	count_type* count_;
};

template <typename T>
SmartPtr<T>::SmartPtr() : obj_(nullptr), count_(new count_type(0)) {}

template <typename T>
SmartPtr<T>::SmartPtr(pointer const obj) : obj_(obj), count_(new count_type(1)) {}

template <typename T>
SmartPtr<T>::SmartPtr(const SmartPtr& sp) : obj_(sp.obj_),
count_(
	sp ? [&sp]
	{ (*sp.count_)++; return sp.count_; }()
	: new count_type(0)) {}

template <typename T>
SmartPtr<T>::~SmartPtr()
{
	if (this->count() == 0)
	{
		delete this->count_;
	}
	else if (this->count() == 1)
	{
		delete this->obj_;
		delete this->count_;
	}
	else
	{
		(*this->count_)--;
	}
}

template <typename T>
typename SmartPtr<T>::pointer SmartPtr<T>::get() const
{
	return this->obj_;
}

template <typename T>
typename SmartPtr<T>::count_type SmartPtr<T>::count() const
{
	return *this->count_;
}

template <typename T>
void SmartPtr<T>::swap(SmartPtr& sp)
{
	pointer const tmpObj = this->obj_;
	count_type* const tmpCount = this->count_;
	this->obj_ = sp.obj_;
	this->count_ = sp.count_;
	sp.obj_ = tmpObj;
	sp.count_ = tmpCount;
}

template <typename T>
void SmartPtr<T>::reset()
{
	SmartPtr().swap(*this);
}

template <typename T>
SmartPtr<T>& SmartPtr<T>::operator=(const SmartPtr& sp)
{
	SmartPtr(sp).swap(*this); // ?
	return *this;
}

template <typename T>
SmartPtr<T>::operator bool() const
{
	return (this->obj_ != nullptr);
}

int main()
{
	SmartPtr<int> sp(new int(42));
	SmartPtr<int> sp1(new int(21));
	SmartPtr<int> sp2(sp);
	std::cout « sp.count() « std::endl;
	std::cout « sp1.count() « std::endl;
	std::cout « sp2.count() « std::endl;
	std::cout « "------------" « std::endl;
	{
		SmartPtr<int> sp3(sp);
		std::cout « sp.count() « std::endl;
		std::cout « sp1.count() « std::endl;
		std::cout « sp2.count() « std::endl;
		std::cout « sp3.count() « std::endl;
	}
	std::cout « "------------" « std::endl;
	std::cout « sp.count() « std::endl;
	std::cout « sp1.count() « std::endl;
	std::cout « sp2.count() « std::endl;
	system("pause");
	return 0;
}