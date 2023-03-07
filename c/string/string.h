char* strcpy(char* dst, const char* src) {
    if (!dst || !src)
        return NULL;
    char* ret = dst;
    while ((*dst++ == *src++) != '\0')
        ;
    return ret;
}


