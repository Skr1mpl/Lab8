#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>
#include <conio.h>
#include <iomanip>

using namespace std;

int writeNumbers();
int chooseMenu();
int chooseUr(string*, int);

template <typename T>
class Urav {
private:
	T a, b, c;
	T disk;
	T x1;
	T x2;
public:
	Urav() {
		a = b = c = x1 = x2 = disk = 0;
	}
	Urav(T a1, T b1, T c1) {
		a = a1;
		b = b1;
		c = c1;
		disk = b * b - 4 * a * c;
		x1 = (-b + sqrt(disk)) / (2 * a);
		x2 = (-b - sqrt(disk)) / (2 * a);
	}
	void show() {
		disk = b * b - 4 * a * c;
		x1 = (-b + sqrt(disk)) / (2 * a);
		x2 = (-b - sqrt(disk)) / (2 * a);
		cout << a << "x^2";
		if (b < 0) cout << b << "x";
		else cout << "+" << b << "x";
		if (c < 0) cout << c;
		else cout << "+" << c;
		cout << endl;
		cout << "D = b^2-4ac" << endl;
		T rav = 4 * a * c;
		if (rav < 0) cout << "D = " << b * b << "+" << -rav;
		else cout << "D = " << b * b << "-" << rav;
		cout << " = " << disk << endl;
		cout << "x1,2 = (-b + sqrt(D))/2a" << endl;
		cout << "x1 = " << x1 << endl;
		cout << "x2 = " << x2 << endl;
	}
	Urav<T>& operator*=(int abc) {
		a *= abc;
		b *= abc;
		c *= abc;
		return*this;
	}
	string getUrav() {
		string s;
		s = to_string(a) + "x^2";
		if (b < 0) s = s + to_string(b) + "x";
		else s = s + "+" + to_string(b) + "x";
		if (c < 0) s = s + to_string(c);
		else s = s + "+" + to_string(c);
		return s;
	}
	void setKeff() {
		cout << "Введите коэффицент a: ";
		a = writeNumbers();
		cout << "Введите коэффицент b: ";
		b = writeNumbers();
		cout << "Введите коэффицент c: ";
		c = writeNumbers();
	}
	T getA() {
		return a;
	}
	T getB() {
		return b;
	}
	T getC() {
		return c;
	}
	void changeA(T w) {
		a = w;
	}
	void changeB(T w) {
		b = w;
	}
	void changeC(T w) {
		c = w;
	}
};

template <typename T>
class Tranzktion {
public:
	Urav<T>* that;
	Urav<T>* previos;
public:
	Tranzktion() :previos(NULL), that(new Urav<T>) {};
	Tranzktion(const Tranzktion<T>& _st):that(new Urav<T>(*(_st.that))), previos(NULL) {};
	~Tranzktion() { 
		delete that; 
		delete previos; 
	};
	Tranzktion<T>& operator=(const Tranzktion<T>& _st){
		if (this != &_st)
		{
			delete that;
			that = new Urav<T>(*(_st.that));
		}
		return *this;
	};
	void BeginTrans()
	{
		delete previos;
		previos = that;
		that = new Urav<T>(*previos);
	};
	void Commit()
	{
		delete previos;
		previos = NULL;
	};
	void Rollback()
	{
		if (previos != NULL)
		{
			delete that;
			that = previos;
			previos = NULL;
		}
	};
	Urav<T>* operator->() { return that; };
};

int main() {
	setlocale(0, "rus");
	int nUr = 0;
	Tranzktion<double>* ur = new Tranzktion<double>[1];
	while (true) {
		int choose = chooseMenu();
		if (choose == 0) {
			nUr++;
			Tranzktion<double>* ptr = new Tranzktion<double>[nUr];
			for (int i = 0; i < nUr - 1; i++)
				ptr[i] = ur[i];
			ur = ptr;
			ptr = NULL;
			delete[]ptr;
			ur[nUr - 1]->setKeff();
		}
		else
			if (choose == 1) {
				for (int i = 0; i < nUr; i++) {
					ur[i]->show();
					cout << endl;
				}
				system("pause");
				system("cls");
			}
			else
				if (choose == 2) {
					string* aa = new string[nUr];
					for (int i = 0; i < nUr; i++)
						aa[i] = ur[i]->getUrav();
					int choose1 = chooseUr(aa, nUr);
					delete[]aa;
					if (choose1 == nUr) continue;
					cout << "Введите число на которое умножить коэффиценты: ";
					int a = writeNumbers();
					ur[choose1].BeginTrans();
					ur[choose1]->operator*=(a);
				}
				else
					if (choose == 3) {
						string* aa = new string[nUr];
						for (int i = 0; i < nUr; i++)
							aa[i] = ur[i]->getUrav();
						int choose1 = chooseUr(aa, nUr);
						delete[]aa;
						if (choose1 == nUr) continue;
						cout << "Было: " << ur[choose1]->getUrav() << endl;
						ur[choose1].Rollback();
						cout << "Стало: " << ur[choose1]->getUrav() << endl;
						system("pause");
						system("cls");
					}
					else
						if (choose == 4) {
							string* aa = new string[nUr];
							for (int i = 0; i < nUr; i++)
								aa[i] = ur[i]->getUrav();
							int choose1 = chooseUr(aa, nUr);
							if (choose1 == nUr) continue;
							int choose2 = chooseUr(aa, nUr);
							if (choose2 == nUr) continue;
							ur[choose1].BeginTrans();
							ur[choose1]->changeA(ur[choose1]->getA() - ur[choose2]->getA());
							ur[choose1]->changeB(ur[choose1]->getB() - ur[choose2]->getB());
							ur[choose1]->changeC(ur[choose1]->getC() - ur[choose2]->getC());
							delete[]aa;
							cout << "Вычетание прошло успешно!" << endl;
							system("pause");
							system("cls");
						}
						else break;
	}
	delete[]ur;
	return 0;
}

int chooseMenu() {
	int choose_menu = 0, key = 0;
	system("cls");
	while (true) {
		choose_menu = (choose_menu + 6) % 6;

		if (choose_menu == 0) cout << "-> Добавить уравнение" << endl;
		else cout << " Добавить уравнение" << endl;

		if (choose_menu == 1) cout << "-> Посмотреть уравнения и решить" << endl;
		else cout << " Посмотреть уравнения и решить" << endl;

		if (choose_menu == 2) cout << " -> Умножить коэфиценты на число" << endl;
		else cout << " Умножить коэфиценты на число" << endl;

		if (choose_menu == 3) cout << " -> Откатить уравнение на предыдущее" << endl;
		else cout << " Откатить уравнение на предыдущее" << endl;

		if (choose_menu == 4) cout << " -> Отнять одно уравнения от другого" << endl;
		else cout << " Отнять одно уравнения от другого" << endl;

		if (choose_menu == 5) cout << " -> Выход" << endl;
		else cout << " Выход" << endl;

		key = _getch();
		if (key == 224) {
			key = _getch();
			if (key == 72) choose_menu--;
			if (key == 80) choose_menu++;
		}
		if (key == 13) {
			system("cls");
			return choose_menu;
		}
		system("cls");
	}
}

int writeNumbers() {
	string numbers;
	int d = 0;
	while (true) {
		int key;
		key = _getch();
		if (key == 224) {
			key = _getch();
		}
		else
			if (key == 8) {
				if (numbers.length() != 0) {
					cout << '\b' << " " << '\b';
					if (numbers[numbers.length() - 1] == ',') d = 0;
					numbers.erase(numbers.length() - 1);
				}
			}
			else
				if (key == 13 && numbers.length() != 0 && numbers != "-") break;
				else
					if ((key >= '0' && key <= '9') || (key == '-' && numbers.length() == 0) || (key == ',')) {
						if (key == ',' && numbers.length() != 0 && d == 0) {
							d = 1;
							numbers = numbers + (char)key;
							cout << (char)key;
						}
						else 
							if (key != ',') {
								numbers = numbers + (char)key;
								cout << (char)key;
							}
					}
	}
	cout << endl;
	return stoi(numbers);
}

int chooseUr(string* a, int nUr) {
	int choose_menu = 0, keyboard_button = 0;
	while (true) {
		cout << "Стрелочками ВВЕРХ и ВНИЗ выберите уравнение" << endl;
		choose_menu = (choose_menu + (nUr + 1)) % (nUr + 1);

		for (int i = 0; i < nUr; i++)
			if (i == choose_menu) { cout << " -> " << i + 1 << " - " << a[i] << endl; }
			else { cout << " " << i + 1 << " - " << a[i] << endl; }

		if (choose_menu == nUr) { cout << " -> Выйти с выбора" << endl; }
		else cout << " Выйти с выбора" << endl;

		keyboard_button = _getch();
		if (keyboard_button == 224) {
			keyboard_button = _getch();
			if (keyboard_button == 72) choose_menu--;
			if (keyboard_button == 80) choose_menu++;
		}
		if (keyboard_button == 13) { system("cls"); return choose_menu; }
		system("cls");
	}
}