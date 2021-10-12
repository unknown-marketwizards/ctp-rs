#pragma  once
#include "stdafx.h"
#include "getconfig.h"
#include <wtypes.h>
#include <conio.h>
#include <iostream>
#include <locale>
#include <string>
#include <fstream>
#include <conio.h>
#include <string>
#include <time.h>
#include <sstream>
#include <locale.h>
#include <vector>

/*函数名称：getConfig()
函数功能：获取配置文件ini中相应大标题title下指定配置字段cfgname的值
参数1：string title		大标题[***]
参数2：string cfgName		大标题下的配置字段
返回值：配置文件ini中相应大标题title下指定配置字段cfgname的值
*/
string getConfig(string title, string cfgName)
{
	const char* INIFile = "config.ini";
	ifstream inifile(INIFile);
	if (!inifile.is_open())
	{
		cerr << "Could not open " << INIFile << endl;
		inifile.clear();
		_getch();
		exit(-1);
	}
	string strtmp, strtitle, strcfgname, returnValue;
	int flag = 0;
	while (getline(inifile, strtmp, '\n'))
	{
		if (strtmp.substr(0, 1) == "#")	continue;	//过滤注释		
		if (flag == 0)
		{
			if (strtmp.find(title) != string::npos)
			{
				if (strtmp.substr(0, 1) == "[")
				{
					if (strtmp.find("]") == string::npos) 	break;	//缺失“]”退出
					strtitle = strtmp.substr(1);
					strtitle = strtitle.erase(strtitle.find("]"));
					if (strtitle == title)		//找到大标题设置标志位为1，这样就不再找下一个大标题了
					{
						flag = 1;
						continue;
					}
				}
			}
		}
		if (flag == 1)
		{
			if (strtmp.substr(0, 1) == "[")	break;	//如果遇到下一个[]号说明当前大标题对应的配置字段搜索完毕，结束搜索。
			if (strtmp.find(cfgName) != string::npos)
			{
				if (strtmp.find("=") == string::npos)	break;	//缺失“=”退出
				strcfgname = strtmp;
				strcfgname = strcfgname.erase(strcfgname.find("="));
				if (strcfgname == cfgName)		//找到大标题相应的字段后，返回值
				{
					returnValue = strtmp.substr(strtmp.find("=") + 1);
					return returnValue;
				}
				else continue;
			}
		}
	}
	cout << "配置文件错误：没找到" << title << "对应配置项" << cfgName << "！" << endl;
	_getch();
	exit(-1);
}
