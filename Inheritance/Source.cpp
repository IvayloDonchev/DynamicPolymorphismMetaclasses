#include <iostream>
#include <vector>

class Vehicle
{
public:
	virtual void accelerate() const = 0;
};

class Car : public Vehicle
{
	virtual void accelerate() const override
	{
		std::cout << "It is Car accelerating...\n";
	}
};

class Truck : public Vehicle
{
	virtual void accelerate() const override
	{
		std::cout << "It is Truck accelerating...\n";
	}
};

int main()
{
	std::vector<Vehicle*> vehicles{ new Car{}, new Truck{}, new Truck{}, new Car{} };
 
	for (auto&& v : vehicles)
	{
		v->accelerate();
	}
}