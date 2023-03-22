int main() {
	asm volatile("int $0x80");
	
	return 0;
}
