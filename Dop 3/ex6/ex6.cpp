#include <chrono>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>


long fibonacci(unsigned n) {
	return n < 2 ? n : fibonacci(n - 1) + fibonacci(n - 2);
}

template <typename T>
class Timer {
public:
	static void reset();
	static T elapsed_nanoseconds();
	static T elapsed_microseconds();
	static T elapsed_milliseconds();
	static T elapsed_seconds();
	static T elapsed_minutes();
private:
	typedef std::chrono::high_resolution_clock clock_;
	static std::chrono::time_point<std::chrono::high_resolution_clock> beg_;
};

template <typename T>
void Timer<T>::reset() {
	beg_ = clock_::now();
}

template <typename T>
T Timer<T>::elapsed_seconds() {
	return std::chrono::duration_cast<std::chrono::duration<T, std::ratio<1> >>(clock_::now() - beg_).count();
}
template <typename T>
T Timer<T>::elapsed_milliseconds() {
	return std::chrono::duration_cast<std::chrono::duration<T, std::milli >>(clock_::now() - beg_).count();
}
template <typename T>
T Timer<T>::elapsed_microseconds() {
	return std::chrono::duration_cast<std::chrono::duration<T, std::micro >>(clock_::now() - beg_).count();
}
template <typename T>
T Timer<T>::elapsed_nanoseconds() {
	return std::chrono::duration_cast<std::chrono::duration<T, std::nano >>(clock_::now() - beg_).count();
}
template <typename T>
T Timer<T>::elapsed_minutes() {
	return std::chrono::duration_cast<std::chrono::duration<T, std::ratio<60> >>(clock_::now() - beg_).count();
}

template<typename T>
std::chrono::time_point<std::chrono::high_resolution_clock> Timer<T>::beg_ = std::chrono::high_resolution_clock::now();


template <typename T>
class BoxPlot{
public:
	static T mean(std::vector<T> vector);
	static T lq(std::vector<T> vector);
	static T uq(std::vector<T> vector);
	static T min(std::vector<T> vector);
	static T max(std::vector<T> vector);
	static T median(std::vector<T> vector);
	static T stddev(std::vector<T> vector);
	static void out(std::vector<T> vector);

};
template <typename T>
T BoxPlot<T>::mean(std::vector<T> vector) {
	sort(vector.begin(), vector.end());
	size_t size = vector.size();
	return std::accumulate(vector.begin(), vector.end(), 0.0) / size;
}
template <typename T>
T BoxPlot<T>::lq(std::vector<T> vector) {

	sort(vector.begin(), vector.end());
	size_t size = vector.size();
	return vector[size * 0.25];
}
template <typename T>
T BoxPlot<T>::uq(std::vector<T> vector) {

	sort(vector.begin(), vector.end());
	size_t size = vector.size();
	return vector[size * 0.75];
}
template <typename T>
T BoxPlot<T>::min(std::vector<T> vector) {
	T lq = BoxPlot<double>::lq(vector);
	T uq = BoxPlot<double>::uq(vector);
	return lq - (uq-lq) * 1.5;
}
template <typename T>
T BoxPlot<T>::max(std::vector<T> vector) {
	T lq = BoxPlot<double>::lq(vector);
	T uq = BoxPlot<double>::uq(vector);
	return uq + (uq - lq) * 1.5;
}
template <typename T>
T BoxPlot<T>::median(std::vector<T> vector) {

	double median;
	sort(vector.begin(), vector.end());
	size_t size = vector.size();

	if (size % 2 != 0) {
		median = vector[size / 2];
	}
	else {
		median = (vector[size / 2] + vector[size / 2 - 1]) / 2;
	}
	return median;
}
template <typename T>
T BoxPlot<T>::stddev(std::vector<T> vector) {

	sort(vector.begin(), vector.end());
	size_t size = vector.size();

	T D = NULL;
	T mean = BoxPlot<double>::mean(vector);
	for (size_t i = 0; i < size; i++) {
		D += pow(vector[i] - mean, 2);
	}
	return pow(D/ (size - 1), 0.5);
}
template <typename T>
void BoxPlot<T>::out(std::vector<T> vector) {

	T min = BoxPlot<T>::min(vector);
	T max = BoxPlot<T>::max(vector);
	std::for_each(vector.cbegin(), vector.cend(),
		[&min, &max](T x) {
			if ((x > max) || (x < min)) {
				std::cout << x << " ";
			}
		}
	);
}


int main() {
	Timer<double>::reset();
	std::cout << "f(42) = " << fibonacci(20) << '\n';
	std::cout << Timer<double>::elapsed_minutes() << " minute" << std::endl;
	std::cout << Timer<double>::elapsed_seconds() << " s" << std::endl;
	std::cout << Timer<double>::elapsed_milliseconds() << " mili s" << std::endl;
	std::cout << Timer<double>::elapsed_microseconds() << " micro s" << std::endl;
	std::cout << Timer<double>::elapsed_nanoseconds() << " nano s" << std::endl;


	std::cout << "---------- " << '\n';

	std::vector<double> x = { 0.0855298042e+00,1.4513241053e+00,1.3237277269e+00,1.0128350258e+00,1.4122089148e+00,6.5826654434e-01,2.0795986652e+00,1.0230206251e+00,1.4231411219e+00,1.1091691256e+00,1.7714337111e+00,1.3986129761e+00,1.0640757084e+00,1.4216910601e+00,1.2402026653e+00 };
	std::cout.precision(2);
	std::cout << std::scientific << "min:    " << BoxPlot<double>::min(x) << std::endl;
	std::cout << std::scientific << "lq:     " << BoxPlot<double>::lq(x) << std::endl;
	std::cout << std::scientific << "median: " << BoxPlot<double>::median(x) << std::endl;
	std::cout << std::scientific << "mean:   " << BoxPlot<double>::mean(x) << std::endl;
	std::cout << std::scientific << "stddev: " << BoxPlot<double>::stddev(x) << std::endl;
	std::cout << std::scientific << "uq:     " << BoxPlot<double>::uq(x) << std::endl;
	std::cout << std::scientific << "max:    " << BoxPlot<double>::max(x) << std::endl;
	BoxPlot<double>::out(x);

	return 0;
}
