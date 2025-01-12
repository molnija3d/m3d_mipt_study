int main() {
    int x = 4 + ({
        int y = 1; 
	int z = 5; 
	z+= y; 
	z % 4;
    });

    x = x > 5 ?:5;
    return 0;
}
