#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
	FILE* infile, *outfile;
	fopen_s(&outfile, "file.txt", "wb");
	char buf1[4] = "123";
	cout << fwrite(buf1, 1, sizeof(buf1), outfile) << endl;
	fclose(outfile);


	fopen_s(&infile, "file.txt", "rb");

	if (!infile) return 0;

	fseek(infile, 0, SEEK_END);
	int len = ftell(infile);
	cout << len << endl;	fseek(infile, 0, SEEK_SET);
	char buf2[4] = "";
	fread(buf2, 1, len, infile);
	fclose(infile);

	FILE* outfile2;
	fopen_s(&outfile2, "file.txt", "ab");
	fseek(infile, 3, SEEK_SET);
	char buf3[4] = "456";
	cout << fwrite(buf3, 1, sizeof(buf3), outfile2) << endl;
	fclose(outfile2);


	return 0;
}
