void string_copy(char* d, char* s) {
	for (char* pd = d, *ps = s; *pd++ = *ps++;);
};

int len(const char* s) {
	int sum = 0;
	int i = 0;
	while (s[i] != 0) {
		sum++;
		i++;
	}
	return sum;
}

int compare(const char* s, const char* t) {
	if (len(s) > len(t)) {
		return 1;
	}
	if (len(s) < len(t)) {
		return -1;
	}
	if (len(s) == len(t)) {
		return 0;
	}
}
//Функция должна возвращать целое > 0, если s > t, 
//< 0, если s < t 
//и 0, если s == t;