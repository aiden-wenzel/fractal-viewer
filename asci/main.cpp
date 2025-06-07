#include <iostream>
#include <vector>
#include <cmath>

struct Complex_Num {
	double real;
	double imag;
};

struct Complex_Num compute_complex_num(size_t i, size_t j, size_t n);
double cabs(struct Complex_Num c);
Complex_Num cadd(Complex_Num a, Complex_Num b);
Complex_Num cmult(Complex_Num a, Complex_Num b);
bool diverges(size_t div_lim, size_t num_itterations, struct Complex_Num c);
void print_complex_num(struct Complex_Num c);

int main() {
	size_t n = 101;
	size_t div_lim = 5000000000000;
	size_t itterations = 100;
	int lower = -2, upper = 2;
	std::vector<std::vector<char>> grid(n, std::vector<char>(n, ' '));

	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < n; j++) {
			Complex_Num c = compute_complex_num(i, j, n);
			if (!diverges(div_lim, itterations, c)) {
				grid[i][j] = '*';
			}
		}
	}

	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < n; j++) {
			std::cout << grid[i][j] << ' ';
		}
		std::cout << '\n';
	}

	return 0;
}

struct Complex_Num compute_complex_num(size_t i, size_t j, size_t n) {
	double x = j;
	double y = -1.0*(double)i;
	
	double scale = (n-1) / 2.0;
	x = x / scale;
	y = y / scale;

	x = x - 1.0;
	y = y + 1.0;

	x *= 2;
	y *= 2;

	return {x, y};
}

double cabs(struct Complex_Num c) {
	return sqrt(c.real*c.real + c.imag*c.imag);
}

Complex_Num cadd(Complex_Num a, Complex_Num b) {
	return {a.real + b.real, a.imag + b.imag};
}

Complex_Num cmult(Complex_Num a, Complex_Num b) {
	double first = a.real * b.real;
	double inner = (a.imag * b.real) + (b.imag * a.real);
	double last = -1 * (a.imag * b.imag);

	return {first+last, inner};
}

bool diverges(size_t div_lim, size_t num_itterations, struct Complex_Num c) {
	Complex_Num z_curr = {0.0, 0.0};

	for (size_t i = 0; i < num_itterations; i++) {
		z_curr = cadd(cmult(z_curr, z_curr), c);
		
		if (cabs(z_curr) > div_lim) {
			return true;
		}
	}
	return false;
}

void print_complex_num(struct Complex_Num c) {
	std::cout << "(" << c.real << "," << c.imag <<") ";
}
