
char *intToRoman(int num) {
    int digits[4] = {0};
    char* romans = (char*)malloc(sizeof(char));
    char* cursor = romans;
    // if num = 1234, then
    // digits = {1, 2, 3, 4};
    int base = 1000;
    for (int i = 0; i < 4; i++) {
        digits[i] = num / base;
        num = num % base;
        base /= 10;
    }
    doRoman(digits[0], '_', '_', 'M', &cursor); // '_' can be anything
    doRoman(digits[1], 'M', 'D', 'C', &cursor);
    doRoman(digits[2], 'C', 'L', 'X', &cursor);
    doRoman(digits[3], 'X', 'V', 'I', &cursor);
    *cursor = '\0';
    return romans;
}

void doRoman(int number, char ten, char five, char one, char** str) {

    switch (number) {
        case 9:
            (*str)[0] = one;
            (*str)[1] = ten;
            (*str) += 2;
            break;
        case 8:
            (*str)[0] = five;
            (*str)[1] = one;
            (*str)[2] = one;
            (*str)[3] = one;
            (*str) += 4;
            break;
        case 7:
            (*str)[0] = five;
            (*str)[1] = one;
            (*str)[2] = one;
            (*str) += 3;
            break;
        case 6:
            (*str)[0] = five;
            (*str)[1] = one;
            (*str) += 2;
            break;
        case 5:
            (*str)[0] = five;
            (*str) += 1;
            break;
        case 4:
            (*str)[0] = one;
            (*str)[1] = five;
            (*str) += 2;
            break;
        case 3:
            (*str)[0] = one;
            (*str)[1] = one;
            (*str)[2] = one;
            (*str) += 3;
            break;
        case 2:
            (*str)[0] = one;
            (*str)[1] = one;
            (*str) += 2;
            break;
        case 1:
            (*str)[0] = one;
            (*str) += 1;
            break;
        case 0:
        default:
            break;
    }
}

