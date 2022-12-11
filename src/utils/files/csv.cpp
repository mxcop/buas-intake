#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

typedef unsigned char byte;

/// Load a .csv file from the given path.
/// Source : https://www.folkstalk.com/tech/how-to-read-a-comma-delimited-file-into-an-array-c-with-code-examples/
std::vector<byte> ldcsv(const std::string path, const unsigned int capacity = 256)
{
	std::vector<byte> bytes;
	std::ifstream fin(path);
	bytes.reserve(capacity);
	if (fin.is_open())
	{
		std::string line;
		while (std::getline(fin, line))
		{
			std::stringstream ss(line);
			std::string course;
			while (std::getline(ss, course, ','))
			{
				std::stringstream strValue;
				strValue << course;

				unsigned int c_byte;
				strValue >> c_byte;

				bytes.push_back(static_cast<byte>(c_byte));
			}
		}
	}
	else {
		throw std::invalid_argument("csv file not found...");
	}

	return bytes;
}