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

int getBit(fstream& f){
	static int pos = 8;
	static char c;
	if (pos == 8){
		f.get(c);
		pos = 0;
	}
	return ((c>>(7-(pos++)))&1);
}

int main(){  
//194, 191, 188)
uint16_t color = (((31*(194+4))/255)<<11) | 
               (((63*(191+2))/255)<<5) | 
               ((31*(188+4))/255);
               cout<< color;
/*
	fstream f ;
	string fileFormat = "#include <stdint.h>\n\
\n\
static const struct\n\
{\n\
    uint16_t width;\n\
    uint16_t height;\n\
    uint8_t pixel_data[%d * %d];\n\
} apertus_logo_part_2 = { \n\
%d, %d, \n {%s}};";
	f.open("./data2.pbm", std::ios::binary|std::ios::in);
	if (!f)
		cout<<"\n oops!! file does not exit";
	else
		cout<<"\n ready to go!!";
	unsigned char buf[3];
	int* size = getSize(f);
	//printf("size : [%d, %d]", size[0], size[1]);
	char c;
	string s = "";
	bool first = true;
	for(int i=0;i<(size[0]*size[1]);++i){
		c = getBit(f);
		if (first)
			first = false;
		else
			s += ", ";
		s += ((char)(c+'0'));
		cout<<((char)(c+'0'));
		if(i%size[0] == 0)
			cout<< '\n';
	}
	f.close();
	char* cstr = new char[fileFormat.length() + s.length()];
	sprintf(cstr, fileFormat.c_str(), size[0], size[1], size[0], size[1], s.c_str());
	//cout << cstr;
	ofstream fout;
	fout.open("header2.h");
	fout << cstr;
	fout.close();
	*/
	return 0;
}
