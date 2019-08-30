#include <iostream>

#include <fstream>


int main()
{
	std::fstream fs("fstream.txt", std::ios::in | std::ios::out | std::ios::trunc | std::ios::binary);
	if (!fs.bad())
	{
		// Write to the file.
		fs << "Writing to a basic_fstream object..." << std::endl;
		fs.close();


		char buf[100];
		// Dump the contents of the file to cout.
		fs.open("fstream.txt", std::ios::in);
		fs.getline(buf, strlen(buf));
		
		std::cout << buf;
		fs.close();
	}


	char arr[100] = "Test";
	char arr2[100];
	std::fstream fs3("fstream2.txt", std::ios::in | std::ios::out | std::ios::trunc | std::ios::binary);
	if (!fs.bad())
	{
		// Write to the file.fs1.open("fstream.aaa", std::ios::in | std::ios::out | std::ios::trunc | std::ios::binary);
		fs3.write(arr, sizeof(arr));
		fs3.close();

		// Dump the contents of the file to cout.
		std::fstream fs4("fstream2.txt", std::ios::in | std::ios::binary);
		fs4 >> arr2;
		std::cout << arr2 << std::endl;
		fs4.close();
	}


}