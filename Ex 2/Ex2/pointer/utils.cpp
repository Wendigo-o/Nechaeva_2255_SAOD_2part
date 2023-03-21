
void Swap(int &pa, int &pb) {
    int k = pa;
    pa = pb; pb = k;
}
void Swap1(int* pa, int* pb) {
    int k = *pa;
    *pa = *pb; *pb = k;
}