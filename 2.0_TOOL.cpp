#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <cmath>
#include <stdlib.h>

using namespace std;


int* getSize(fstream& f){
	int *size = new int[2];
	string s;
	for (int i=0;i<2;++i){ 
		getline(f, s, '\n');
		if (s[0] == '#')
			--i;
	}
	cout<<s << "\n";
	sscanf(s.c_str(), "%d %d", &size[0], &size[1]);
	return size;
}
/* bit manipulation
int getBit(fstream& f){
	static int pos = 8;
	static char c;
	if (pos == 8){
		f.get(c);
		pos = 0;
	}
	return ((c>>(7-(pos++)))&1);
}
*/

int* blow(string &s, string f_name){
	fstream f ;
	f.open(f_name.c_str(), std::ios::binary|std::ios::in);
	if (!f)
		cout<<"\n oops!! file does not exit";
	else
		cout<<"\n ready to go!!";
	unsigned char buf[3];
	int* size = getSize(f);
	//printf("size : [%d, %d]", size[0], size[1]);
	char c;
	bool first = true;
	while(f.get(c)) s.push_back(c);
	f.close();
	return size;
}

int main(){  

string fileFormat = "#include <stdint.h>\n\
\n\
static const struct\n\
{\n\
    uint16_t width;\n\
    uint16_t height;\n\
    uint8_t pixel_data_raw[((%d * %d)/8) + 1];\n\
} apertus_logo_part_1 = { \n\
%d, %d, \n R\"\"\"\"(";
string fileFormat_2 = ")\"\"\"\"};\n\
static const struct\n\
{\n\
    uint16_t width;\n\
    uint16_t height;\n\
    uint8_t pixel_data_raw[((%d * %d)/8) + 1];\n\
} apertus_logo_part_2 = { \n\
%d, %d, \n R\"\"\"\"(";
//\"};";
	string s_1;
	int *size_1 = blow(s_1, "../data1.pbm"); //name of image containing apertus
	string s_2;
	int *size_2 = blow(s_2, "../data2.pbm"); //name of image containing 0
	char* cstr = new char[fileFormat.length() + s_1.length()];
	char* cstr_2 = new char[fileFormat.length() + s_1.length()];
	cout << s_1.c_str();
	sprintf(cstr, fileFormat.c_str(), size_1[0], size_1[1], size_1[0], size_1[1]);
	sprintf(cstr_2, fileFormat_2.c_str(), size_2[0], size_2[1], size_2[0], size_2[1]);
	//cout << cstr;
	string fin = cstr + s_1 + cstr_2 + s_2 + ")\"\"\"\"};";
	ofstream fout;
	fout.open("../header2.h");
	fout << fin;
	fout.close();
	return 0;
}
