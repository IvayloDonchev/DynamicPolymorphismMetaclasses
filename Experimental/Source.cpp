#include <iostream>
#include <vector>

struct VTable
{
	void (*accelerate)(void* ptr);
	void (*destruct)(void* ptr);
	void* (*copy_)(void* ptr);
	void* (*move_)(void* ptr);
};

template<typename T>
VTable vtable_for
{
	[](void* p) { static_cast<T*>(p)->accelerate(); },
	[](void* p) { delete static_cast<T*>(p); },
	[](void* p) -> void*{ return new T(*static_cast<T*>(p)); },
	[](void* p) -> void*{ return new T(std::move(*static_cast<T*>(p))); }
};

class Vehicle
{
public:
	void* p_obj;
	VTable const* p_vtable;
	void accelerate() { p_vtable->accelerate(p_obj); }
	~Vehicle() { p_vtable->destruct(p_obj); }
	template<typename T>
	Vehicle(T const& other) :
		p_obj(new T(other)),
		p_vtable(&vtable_for<T>)
	{}
	Vehicle(Vehicle const& other) :
		p_obj(other.p_vtable->copy_(other.p_obj)),
		p_vtable(other.p_vtable)
	{}
	Vehicle(Vehicle&& other) noexcept :
		p_obj(other.p_vtable->move_(other.p_obj)),
		p_vtable(other.p_vtable) 
	{}
	Vehicle& operator=(Vehicle const& other)
	{
		p_obj = other.p_vtable->copy_(other.p_obj);
		p_vtable = other.p_vtable;
		return *this;
	}
	Vehicle& operator=(Vehicle&& other) noexcept
	{
		p_obj = other.p_vtable->move_(other.p_obj);
		p_vtable = other.p_vtable; return *this;
	}
};

class Car
{
public:
	void accelerate()
	{
		std::cout << "It is car accelerating...\n";
	}
};

class Truck 
{
public:
	void accelerate()
	{
		std::cout << "It is truck accelerating...\n";
	}
};

int main() {
	Vehicle v = Car{};
	v.accelerate();
	v = Truck{};
	v.accelerate();

	Vehicle c{ v };
	c.accelerate();
	
	std::cout << "------------------\n";
	std::vector<Vehicle> vehicles{ Car{}, Truck{} };
	for (auto&& a : vehicles) {
		a.accelerate();
	}
}

