#include <iostream>
#include <vector>

class Vehicle
{
public:
	virtual void Accelerate() const = 0;
};

class Car : public Vehicle
{
	virtual void Accelerate() const override
	{
		std::cout << "It is Car accelerating...\n";
	}
};

class Truck : public Vehicle
{
	virtual void Accelerate() const override
	{
		std::cout << "It is Truck accelerating...\n";
	}
};

namespace LibOne {
	class Base {
	public:
		virtual void Foo() {};
	};
}

namespace LibTwo {
	class Other : public LibOne::Base{
	public:
		virtual void Foo() {};
	};
}

int main()
{
	LibOne::Base* b = new LibTwo::Other{};

	Vehicle *vehicle = new Car{};
	vehicle->Accelerate();
	delete vehicle;
	vehicle = new Truck{};
	vehicle->Accelerate();
	std::vector<Vehicle*> vehicles{
		new Car{}, 
		new Truck{}, 
		new Truck{}, 
		new Car{} 
	};
	for (auto&& v : vehicles){
		v->Accelerate();
	}

	
}