struct {
	long long first : 64;
}	flags;

int main()
{
	flags.first = 1;
	flags.first <<= 1;
	printf("%d", flags);
	return 0;
}