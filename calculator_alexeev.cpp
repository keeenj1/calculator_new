#include <iostream>
#include <cmath>
#include <stack>
#include <sstream>

struct Leksema
{
	char type; // 0 для чисел, "+"  для операции сложения и т.д.
	double value;
};

bool maths(std::stack <Leksema>& stack_n, std::stack <Leksema>& stack_o, Leksema& item) {
	double a, b, c;
	a = stack_n.top().value; // Берётся верхнее число из стэка с числами
	stack_n.pop(); // Удаляется верхнее число из стэка с числами
	switch (stack_o.top().type) { // Проверяется тип верхней операции из стека с операциями
		case '+': 
			b = stack_n.top().value;
			stack_n.pop();
			c = a + b;
			item.type = '0';
			item.value = c;
			stack_n.push(item); // Результат операции кладется обратно в стэк
			stack_o.pop();
			break;

		case '-':
			b = stack_n.top().value;
			stack_n.pop();
			c = b - a;
			item.type = '0';
			item.value = c;
			stack_n.push(item);
			stack_o.pop();
			break;

		case '^':
			b = stack_n.top().value;
			stack_n.pop();
			c = pow(b,a);
			item.type = '0';
			item.value = c;
			stack_n.push(item);
			stack_o.pop();
			break;

		case '*':
			b = stack_n.top().value;
			stack_n.pop();
			c = a * b;
			item.type = '0';
			item.value = c;
			stack_n.push(item);
			stack_o.pop();
			break;

		case '/':
			b = stack_n.top().value;
			if (a == 0) {
				std::cerr << "На 0 делить нельзя! " << std::endl;
				return false;
			}
			else {
				stack_n.pop();
				c = (b / a);
				item.type = '0';
				item.value = c;
				stack_n.push(item);
				stack_o.pop();
				break;
			}	

		default:
		std::cerr << "\nОшибка!\n";
		return false;
		break;
}
	return true;
}

int getrank(char ch) {
	if (ch == '+' || ch == '-')return 1;
	if (ch == '*' || ch == '/')return 2;
	if (ch == '^')return 3;
	else return 0;
}

int main()
{
	setlocale(LC_ALL, "RU");
	std::cout << "   Ку, это калькулятор!\n   Введи выражение: ";
	char ch;
	double value;
	bool flag = 1;
	std::stack<Leksema> stack_n;
	std::stack<Leksema> stack_o;
	Leksema item;
	while (1) {
		ch = std::cin.peek();
		// std::cout << ch << std::endl;
		if (ch == '\n')break; // Если конец строки достигнут, то выходим из цикла
		if (ch == ' ') {
			std::cin.ignore();
			continue;
		}
		if (ch >= '0' && ch <= '9' || ch == '-' && flag == 1) { // Если прочитано число 
			std::cin >> value;
			item.type = '0';
			item.value = value;
			stack_n.push(item);
			flag = 0;
			continue;
		}
		if (ch == '+' || ch == '-' && flag == 0 || ch == '*' || ch == '/' || ch == '^') { // Если прочитана операция (+-/*)
			if (stack_o.size() == 0) {
				item.type = ch;
				item.value = 0;
				stack_o.push(item); // Операция кладётся в стэк с операциями
				std::cin.ignore();
				continue;
			}
			if (stack_o.size() != 0 && getrank(ch) > getrank(stack_o.top().type)) {
				item.type = ch;
				item.value = 0;
				stack_o.push(item); // Операция кладётся в стэк с операциями
				std::cin.ignore();
				continue;
			}
			if (stack_o.size() != 0 && getrank(ch) <= getrank(stack_o.top().type)) {
				if (maths(stack_n, stack_o, item) == false) { // Если ф-ция false, то прекращаем работу
					system("pause");
					return 0;
				}
				continue;
			}
		}
		if (ch == '(') {
			item.type = ch;
			item.value = 0;
			stack_o.push(item); // Операция кладётся в стэк с операциями
			std::cin.ignore();
			flag = 1;
			continue;
		}
		if (ch == ')') {
			while (stack_o.top().type != '(') {
				if (maths(stack_n, stack_o, item) == false) { // Если ф-ция false, то прекращаем работу
					system("pause");
					return 0;
				}
				else continue; // Если всё ок, то выдаём ответ
			}
			stack_o.pop();
			std::cin.ignore();
			continue;
		}
		else {
			std::cout << "Неверно введено выражение!\n";
			system("pause");
			return 0;
		}
	}
	while (stack_o.size() != 0) {
		if (maths(stack_n, stack_o, item) == false) { // Если ф-ция false, то прекращаем работу
			system("pause");
			return 0;
		}
		else continue; // Если всё ок, то выдаём ответ
	}
	std::cout << "   Ответ: " << stack_n.top().value << std::endl;
	return 0;
}


