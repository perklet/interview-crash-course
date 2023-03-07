int myAtoi(char* str) {
    int result = 0;
    int sign = 1;

    if (str == NULL) 
        return 0;

    while (isspace(*str))
        ++str;

    if (*str == '-') {
        sign = -1;
        str++;
    } else if (*str == '+') {
        str++;
    }

    while (*str != '\0') {
        if (!isdigit(*str)) break;
        if (result > INT_MAX / 10 ||
                result == INT_MAX / 10 && (*str - '0' > INT_MAX % 10))
            return sign == -1 ? INT_MIN : INT_MAX;
        result = 10 * result + *str - '0';
        ++str;
    }

    return result * sign;
}
