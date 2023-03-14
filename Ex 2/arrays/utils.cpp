void rotate(int a[], int n, bool clockwise = false) {

    if (clockwise) {
        int x = a[n - 1];
        for (int i = n - 1; i > 0; i--)
            a[i] = a[i - 1];
        //cout << "true" << endl;
        a[0] = x;
    }
    else {
        int x = a[0];
        for (int i = 1; i < n; i++)
            a[i - 1] = a[i];
        a[n - 1] = x;

        //cout << "false" << endl;
    }
}
