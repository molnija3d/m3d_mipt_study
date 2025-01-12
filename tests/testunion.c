union my_union{
    int digit;
    float bigfl;
    char letter;
}; 
int main() {
    union my_union test;
    test.digit = 23;
    test.bigfl = 2.0;
    test.letter = 'h';

    return 0;
}
