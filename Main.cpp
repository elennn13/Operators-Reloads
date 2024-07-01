#include <iostream>


class Point {
public:
	double x;
	double y;
	Point() : Point(0., 0.) {}
	Point(double x, double y) : x(x), y(y) {}
	Point(const Point& oP) : Point(oP.x, oP.y) {}

	void print() const {
		std::cout << '(' << x << "; " << y << ")\n";
	}

	double distanceTo(const Point oP) const {//точка сравнения расстояний
		return sqrt(
			pow(oP.x - x, 2) +
			pow(oP.y - y, 2)
		);//
	}


	Point operator+(double num) const {//перегруз бинарного оператора
		return Point(x + num, y + num);
	}
	Point operator+(const Point oP) const {
		return Point(x + oP.x, y + oP.y);// (12, 15)
	}
	Point& operator++() {//ПРЕДинкримент увеличивает на 1 и возвращает этот элемент ++n нужно добавить& -ссылка на область памяти 
		++x; ++y;
		return *this; // * нужно разыменовать 
	}
	Point operator++(int) { //ПОСТинкремент
		Point tmp = *this; //копия точки разыменование
		++x; ++y;
		return tmp;
	}
	bool operator==(const Point oP) const { //логические операции
		return x == oP.x && y == oP.y; //сравнение  если x=y
	}
	bool operator!=(const Point oP) const {
		return x != oP.x || y != oP.y; // сравнение x не равно x и y не равно  y
		// return !(*this == oP) или этот вариант
	}
	bool operator>(const Point oP) const {
		return distanceTo(Point()) > oP.distanceTo(Point());
	}
	bool operator<(const Point oP) const {
		return distanceTo(Point()) < oP.distanceTo(Point());
	}
};


class Array {//создание динамического массива
private:
	int* pointer;
	size_t length;
public:
	Array() : pointer(nullptr), length(0) {}
	Array(size_t length) {
		if (length == 0) {
			this->pointer = nullptr;
			this->length = 0;
			return;
		}
		this->pointer = new int[length] {};
		this->length = length;
	}
	Array(const Array& other) {//конструктор копирования
		length = other.length;
		if (other.pointer == nullptr) {
			pointer = nullptr;
			return;
		}
		pointer = new int[length] {};
		for (size_t i = 0; i < length; ++i)
			pointer[i] = other[i];
	}
	~Array() {//диструктор
		delete[] pointer;
	}

	void app(int num) {//метод добавления нового элемента в дин массив
		if (pointer == nullptr) {
			pointer = new int[1] { num };
			length = 1;
			return;
		}

		int* tmp = new int[length + 1]; //созд. новый дин массив
		for (size_t i = 0; i < length; ++i)
			tmp[i] = pointer[i];
		tmp[length] = num;

		delete[] pointer;
		pointer = tmp;
		++length;
	}

	size_t size() const { return length; }

	int& operator[](size_t index) {
		return pointer[index];
	}
	int operator[](size_t index) const {
		return pointer[index];
	}
	void operator=(const Array& other) {
		delete[] pointer;
		length = other.length;
		if (other.pointer == nullptr) {
			pointer = nullptr;
			return;
		}
		pointer = new int[length];
		for (size_t i = 0; i < length; ++i)
			pointer[i] = other[i];
	}
};


int main() {
	setlocale(LC_ALL, "ru");
	int n;

	//перегрузка базовых операторов
	/*
	Point p1(4, 5), p2(8, 10);
	p1.print();
	p2.print();
	(p1 + 1).print(); //перегрузка операторов + с числом с объектом класса
	(p1 + p2).print(); //перегрузка операторов + с объектом класса
	Point p3(2, 1);
	(++p3).print(); //(3, 2) получится
	(p3++).print(); //(3, 2) получится
	p3.print(); //(4, 3) получится

	if (p1 > p2)
		std::cout << "Первая точка дальше!\n";
	else
		std::cout << "Первая точка не дальше!\n";
*/

	Array arr1(3);
	Array arr2;
	for (size_t i = 0; i < arr1.size(); ++i)
		arr1[i] = (i + 1) * 10;

	std::cout << " Массив №1:\n";
	for (size_t i = 0; i < arr1.size(); ++i)
		std::cout << arr1[i] << ' ';
	std::cout << std::endl;

	arr2 = arr1;
	arr1[1] = 100;

	std::cout << " Массив №2:\n";
	for (size_t i = 0; i < arr2.size(); ++i)
		std::cout << arr2[i] << ' ';
	std::cout << std::endl;


	return 0;
}