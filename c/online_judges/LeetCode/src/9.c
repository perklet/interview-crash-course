bool isPalindrome(int n) {
    if (n < 0) return false;

    bool ret = true;
    int len = 1;
    int high_factor = 1;
    int n_ = n;
    while (n_ /= 10) len++, high_factor *= 10;
    int high = n;
    int low = n;
    if (len > 6) high /= 1000, high_factor /= 1000;
    for (int i = 0; i < len / 2; i++) {
        int h = high / high_factor;
        high = (high % high_factor) * 10;
        int l = low % 10;
        low /= 10;
        if (h != l) {
            ret = false;
            break;
        }
    }
    return ret;
}

