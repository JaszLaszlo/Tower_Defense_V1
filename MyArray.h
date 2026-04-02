#ifndef MYARRAY_H
#define MYARRAY_H
#include <iostream>

template<typename T>
class MyArray {
	T** data;
	int count;
	int capacity;
	void copyfrom(const MyArray& a)
	{
		count = a.count;
		capacity = a.capacity;
		data = new T * [capacity];
		for (int i = 0; i < capacity; i++)
		{
			if (i < count && a.data[i] != nullptr)
			{
				data[i] = a.data[i]->clone();
			}
			else
			{
				data[i] = nullptr;
			}
		}
	}
	void clear()
	{
		for (int i = 0; i < count; i++)
		{
			delete data[i];
		}
		delete[] data;
	}
public:
	MyArray(int cap) : count(0), capacity(cap)
	{
		data = new T * [capacity];
		for (int i = 0; i < capacity; i++)
		{
			data[i] = nullptr;
		}
	}
	MyArray(const MyArray& a)
	{
		copyfrom(a);
	}
	MyArray& operator=(const MyArray& a)
	{
		if (this != &a)
		{
			clear();
			copyfrom(a);
		}
		return *this;
	}
	~MyArray()
	{
		clear();
	}
	void Add(T* item)
	{
		if (count < capacity)
			data[count++] = item;
		else
		{
			throw"Megtelt a tomb";
		}
	}
	void Remove(int idx)
	{
		if (idx < 0 || idx >= count)
			return;
		delete data[idx];
		data[idx] = data[count - 1];
		data[count - 1] = nullptr;
		count--;
	}
	T* operator[](int idx)
	{
		return data[idx];
	}
	const T* operator[](int idx) const
	{
		return data[idx];
	}
	int size() const
	{
		return count;
	}
};

#endif
