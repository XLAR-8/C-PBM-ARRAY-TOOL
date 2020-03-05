#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>

using namespace std;

void GetInt(int& value, string stream)
{
    char temp[40];
    sscanf(stream.c_str(), "%s %s %d", temp, temp, &value);
}

void GetCArray(const char* file_name, string& c_array, int& width, int& height)
{
    fstream file;
    file.open(file_name,    std::ios::in);
    
    if (!file)
	{
		cout << "Error :: Could'nt open file to Read : " << file_name;
		return;
	}
	
	string temp;
	
	//get width 
	getline(file, temp);
	GetInt(width, temp);
	
	//get height
	getline(file, temp);
	GetInt(height, temp);
	
	//Skip the 3rd line
	getline(file, temp);
	
	//read the c_array from the file
	while (file) 
	{
	    getline(file, temp);
	    c_array += "\n" + temp;
	}
	
	file.close();
	
	c_array.pop_back();
	c_array.pop_back();
}

void WriteToFile(const char* file_name, char* payload){    
	ofstream file;
	file.open(file_name);
	
	if (!file)
	{
		cout<<"Error :: Could'nt open file to Write : " << file_name << std::endl;
		return;
	}
	
	file << payload;
	
	file.close();
}

int main()
{
    
	string fileFormat = 
	"#include <stdint.h>\n"
	"\nstatic const struct\n"
	"{\n"
	"    uint16_t width;\n"
	"    uint16_t height;\n"
	"    uint8_t pixel_data[];\n"
	"}\n"
	"apertus_logo_part_1 = {\n"
	"%d, %d, \n"
	" {%s}\n"
	",apertus_logo_part_2 = { \n"
	"%d, %d, \n"
	" {%s};";
	
	string c_array_1, c_array_2;
	int width_1, height_1, width_2, height_2;
	
	GetCArray("apertus_logo_part_1.xbm", c_array_1, width_1, height_1);
	GetCArray("apertus_logo_part_2.xbm", c_array_2, width_2, height_2);
	
	int final_length = snprintf(NULL, 0, fileFormat.c_str(), width_1, height_1,
	  c_array_1.c_str(), width_2, height_2, c_array_2.c_str());
	
	char* cstr = new char[final_length + 1];
	
	sprintf(cstr, fileFormat.c_str(), width_1, height_1, c_array_1.c_str(),
	  width_2, height_2, c_array_2.c_str());
	
	WriteToFile("ApertusLogo.h", cstr);
	
	return 0;
}
