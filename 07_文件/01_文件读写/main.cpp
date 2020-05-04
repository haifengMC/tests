#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
	FILE* infile, *outfile;
	fopen_s(&outfile, "file", "wb");
	char buf1[4] = "123";
	cout << fwrite(buf1, 1, sizeof(buf1), outfile) << endl;
	fclose(outfile);


	fopen_s(&infile, "file", "rb");

	if (!infile) return 0;

	fseek(infile, 0, SEEK_END);
	int len = ftell(infile);
	cout << len << endl;
	fseek(infile, 0, SEEK_SET);
	char buf2[4] = "";
	cout << fread(buf2, 1, len, infile) << endl;
	fclose(infile);

	return 0;
}
