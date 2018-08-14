#ifndef Vector_H
#define Vector_H
#include <iostream>
#include <memory>
#include <algorithm>

template <class T, class Allocator = std::allocator<T>> class Vector {
public:
	typedef T                   value_type;
	typedef value_type*         iterator;
	typedef const value_type*   const_iterator;
	typedef value_type&         reference;
	typedef value_type*         pointer;
	typedef size_t              size_type;
	typedef ptrdiff_t           difference_type;
protected:
	std::allocator<value_type> _alloc;
	iterator _begin;
	iterator _end;
	iterator _end_of_storage;
public:
	Vector(): _begin(0),_end(0),_end_of_storage(0){};
	Vector(size_type n,const T& value);
	Vector(size_type n);
	Vector(iterator first,iterator last);
	Vector(const Vector& v);
	Vector& operator=(const Vector& ass);
	~Vector(){_destroy();}
	
	iterator begin() {return _begin;}
	iterator end() {return _end;}
	const_iterator kbegin() {return _begin;}
	const_iterator kend() {return _end;}
	
	size_type size() {return size_type(end() - begin());};
	size_type capacity() {return size_type(_end_of_storage - begin());}
	bool empty() {return begin() == end();}
	void swap(Vector &other_element);
	
	reference front() {return *begin();}
	reference back() {return *(end() - 1);}
	reference operator[](size_type index) {return *(begin() + index);}
	reference at(size_type index) {return *(begin() + index);}
	
	void insert_auxiliary(iterator position, const T& x);
	void push_back(const T& value);
	void pop_back();
	void insert(iterator position,size_type n,const T& x);
	
	iterator erase(iterator position);
	iterator erase(iterator first,iterator last);
	void clear() {erase(begin(),end());}
	
	void _destroy();
};



Vector<T,Allocator>::Vector(size_type n,const T& value) {
	_begin = _alloc.allocate(n);
	std::uninitialized_fill(_begin, _begin + n, value);
	_end = _end_of_storage = _begin + n;
}


Vector<T,Allocator>::Vector(size_type n) {
	_begin = _alloc.allocate(n);
	std::uninitialized_fill(_begin, _begin + n, 0);
	_end = _end_of_storage = _begin + n;
}



void Vector<T,Allocator>::swap(Vector &other_element) {
	std::swap(_begin, other_element.begin());
	std::swap(_end, other_element.end());
	std::swap(_end_of_storage, other_element._end_of_storage);
}


Vector<T,Allocator> &Vector<T,Allocator>::operator=(const Vector& ass) {
	if (this == &ass) {
		return *this;
	}
	size_type n = ass.kend() - ass.kbegin();
	_begin = _alloc.allocate(n);
	_end = _end_of_storage = std::uninitialized_copy(ass.kbegin(), ass.kend(), _begin);
}


void Vector<T,Allocator>::insert(iterator position,
								 size_type n,const T& x) {
	if (n >= 0) {
		if (_end_of_storage - _end >= n) {
			T x_copy = x;
			const size_type element_after = _end - position;
			iterator old_end = _end;
			if (element_after > n) {
				uninitialized_copy(_end - n,old_end - n,_end);
				_end = _end + n;
				copy_backward(position,old_end - n,old_end);
				fill(position,position + n,x_copy);
			} else {
				uninitialized_fill_n(_end,n - element_after,x_copy);
				_end += n - element_after;
				uninitialized_copy(position,old_end,_end);
				_end += element_after;
				fill(position,old_end,x_copy);
			}
		}
	} else {
		const size_type old_size = size();
		const size_type length = old_size + std::max(old_size,n);
		iterator new_begin = _alloc.allocate(length);
		iterator new_end = new_begin;
		new_end = uninitialized_copy(_begin,position,new_begin);
		new_end = uninitialized_fill_n(position,_end,new_end);
		_destroy();
		_begin = new_begin;
		_end = new_end;
		_end_of_storage = new_begin + length;
	}
}


void Vector<T,Allocator>::insert_auxiliary(iterator position, const T& x) {
	if (_end != _end_of_storage) {
		//pass
	} else {
		const size_type old_size = size();
		const size_type length = old_size ? 2 * old_size : 1;
		iterator new_begin = _alloc.allocate(length);
		iterator new_end = new_begin;
		new_end = uninitialized_copy(_begin,position,new_begin);
		_alloc.construct(new_end, x);
		++new_end;
		new_end = uninitialized_copy(position,_end,new_end);
		
		_destroy();
		
		_begin = new_begin;
		_end = new_end;
		_end_of_storage = new_begin + length;
		
	}
}


void Vector<T,Allocator>::push_back(const T& value) {
	if (_end != _end_of_storage) {
		_alloc.construct(_end, value);
		++_end;
	} else {
		insert_auxiliary(end(), value);
	}
}


typename Vector<T,Allocator>::iterator
Vector<T,Allocator>::erase(iterator first,iterator last) {
	difference_type left = _end - last;
	std::copy(last, _end, first);
	iterator now(first + left);
	while (_end != now) {
		_alloc.destroy(--_end);
	}
	return first;
}


void Vector<T,Allocator>::_destroy() {
	if (_begin) {
		iterator it(_end);
		while (it != _begin) {
			_alloc.destroy(--it);
		}
	}
	_alloc.deallocate(_begin, _end_of_storage - _begin);
	_begin = _end_of_storage = _end = NULL;
}

#endif
