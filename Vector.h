#pragma once
#include <memory>
using std::allocator;
using std::size_t;
template <class item>
class Vector {
public:
	class iterator {
	public:
		
	};
	allocator<item> allo;
public:
	iterator begin() {}
	iterator end() {}
	size_t size() { return len; }
	item at(size_t pos) { return buff[pos]; }
	bool isempty() { return len == 0; }
	void clear(){}
	void push_back(const item& it);
	void pop_back();
	size_t capacity() { return capa; }
	Vector(size_t sz,const item & it);
	Vector();
	~Vector(){ allo.deallocate(buff, len); }
	item operator [](size_t pos) {
		return buff[pos];
	}
private:	
	size_t capa=15;
	size_t len;
	item* buff;
private:
	void expand();
	void reduce();
};
template <class item>
void Vector<item>::pop_back()
{
	len--;
	if (2 * len < capa)
		reduce();
}
template <class item>
void Vector<item>::expand()
{
	item* newbuff = allo.allocate(2 * capa);
	for (int i = 0; i < capa; i++)
		newbuff[i] = buff[i];
	allo.deallocate(buff, capa);
	buff = newbuff;
	capa *= 2;
}
template <class item>
void Vector<item>::reduce()
{
	item *newbuff = allo.allocate(len);
	for (int i = 0; i < len; i++)
		newbuff[i] = buff[i];
	allo.deallocate(buff,capa);
	buff = newbuff;
	capa = len;
}
template <class item>
void Vector<item>::push_back(const item& it)
{
	if (len == capa)
		expand();
	buff[len++] = it;
}
template <class item>
Vector<item>::Vector(size_t sz, const item & it)
{
	buff = allo.allocate(capa);
	len = sz;
	for (int i = 0; i < sz; i++)
		buff[i] = it;
}
template <class item>
Vector<item>::Vector()
{
	buff = allo.allocate(capa);
	len = 0;
}
