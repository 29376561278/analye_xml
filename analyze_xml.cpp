
#include"analyze_xml.h"

using namespace std;

bool ProcessesBool()
{
	TCHAR name[] = L"analyze_xml.exe";
	DWORD aProcesses[1024], cbNeeded, cProcesses;
	unsigned int i;
	int num = 0;
	//打开进程列表
	if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
	{
		return false;
	}
	// 获取进程数量
	cProcesses = cbNeeded / sizeof(DWORD);

	for (i = 0; i < cProcesses; i++)
	{

		if (aProcesses[i] != 0)
		{
			// 将所有szProcessName数组都改为<unknown>
			TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");
			//打开进程，返回句柄
			HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
				PROCESS_VM_READ,
				FALSE, aProcesses[i]);

			if (NULL != hProcess)
			{
				HMODULE hMod;
				DWORD cbNeeded;
				// 获取进程下所有模块的句柄
				if (EnumProcessModules(hProcess, &hMod, sizeof(hMod),
					&cbNeeded))
				{
					// 获取模块名
					GetModuleBaseName(hProcess, hMod, szProcessName,
						sizeof(szProcessName) / sizeof(TCHAR));
				}
			}
			// 判断两个字段是否一样，如果一样num+1
			if (_tcscmp(name, szProcessName) == 0)
			{
				num += 1;
			}
			//关闭进程句柄
			CloseHandle(hProcess);
			
		}
	}
	// 判断num如果存在两个或以上返回true，反之返回false
	if (num >= 2) 
	{
		return true;
	}
	else 
	{
		return false;
	}
	
}




void CreateNewArray(tinyxml2::XMLDocument* tinyXmlDoc, std::vector<std::string> files, const char* first_path) 
{
	tinyxml2::XMLElement* root = tinyXmlDoc->RootElement();//创建根目录对象
	tinyxml2::XMLElement* Library = root->FirstChildElement("123");//创建根目录下的123子节点对象
	std::vector<std::string> RenodeList;//创建字符串数组进行存放每一个文件中的报错信息
	std::vector<std::string> FileList;//创建字符串数组进行存放每一个文件
	// 循环遍历每个文件，调用GetScriptSection函数进行错误收集
	for (const auto& file : files) {
		GetScriptSection(RenodeList, file);
		if (RenodeList.empty()) {
			std::cout << "该文件123，123， 123字段全部为空" << file << endl;
			FileList.push_back(file);
			continue;
		}
		else
		{
			tinyxml2::XMLElement* ScriptException = CombineScript(Library, RenodeList);
			RenodeList.clear();
			Library->LinkEndChild(ScriptException);//将子节点对象存入到123节点下
		}
	}
	if (FileList.size() == files.size()) {
		std::cout << "所有文件都未在十分钟之内" << endl;
		return;
	}
	if (Library)
	{
		Library->SetName("ScriptExceptions");//将节点名字改为123，并删除原数组的ErrorTitle、StackTrace、ScriptLanguage
		tinyxml2::XMLElement* ErrorTitle = Library->FirstChildElement("123");
		Library->DeleteChild(ErrorTitle);
		tinyxml2::XMLElement* StackTrace = Library->FirstChildElement("123");
		Library->DeleteChild(StackTrace);
		tinyxml2::XMLElement* ScriptLanguage = Library->FirstChildElement("123");
		Library->DeleteChild(ScriptLanguage);
		bool result = tinyXmlDoc->SaveFile(first_path);//写入文件中
		printf("文件写入成功！\n");
		printf("原有数组已删除");

	}
}


tinyxml2::XMLElement* CombineScript(tinyxml2::XMLElement* Library, std::vector<std::string > node_list)
{
	tinyxml2::XMLElement* ScriptException = Library->InsertNewChildElement("123");
	//创建一个123子节点，并将三个元素传入进去，并返回子节点
	ScriptException->SetAttribute("123", node_list[0].c_str());
	ScriptException->SetAttribute("123", node_list[1].c_str());
	ScriptException->SetAttribute("123", node_list[2].c_str());
	//root->InsertEndChild(child);
	return ScriptException;
}


std::time_t ConvertToSeconds(tinyxml2::XMLElement* Library) {
	tinyxml2::XMLElement* Exception = Library->FirstChildElement("123");//根据根指针获取123子节点中的123节点对象
	tinyxml2::XMLElement* Time = Exception->FirstChildElement("123");
	const char* Current_time = Time->GetText();//获取报错时间
	int CurrentTime = std::atoi(Current_time);	//将字符串指针转为int类型
	std::time_t NewTime = std::time(nullptr);//获取当前时间
	return static_cast<int>(NewTime) - CurrentTime;// 算出距离当前时间秒数
}


void GetScriptSection(std::vector<std::string >& node_list, std::string file_dir)
{
	tinyxml2::XMLDocument tinyXmlDoc;//创建xml文件对象
	tinyxml2::XMLError error = tinyXmlDoc.LoadFile(file_dir.c_str());//进行读取判断
	if (error != tinyxml2::XML_SUCCESS) {
		std::cout << "读取 xml 失败 ：GetScriptSection" << tinyXmlDoc.ErrorStr() << endl;
		return;
	}
	tinyxml2::XMLElement* Library = tinyXmlDoc.RootElement();//创建根节点对象
	tinyxml2::XMLElement* pItem = Library->FirstChildElement("123");//创建子节点对象
	//调用ConvertToSeconds函数用来判断文件中的报错信息距离现在的时间，将Library指针传进去以获取文件中的时间
	int Current_time = ConvertToSeconds(Library);
	int Final_time = (Current_time / 60);
	if (pItem) {
		for (; pItem != NULL; pItem = pItem->NextSiblingElement("123")) {//NextSiblingElement()方法的作用是获取当前节点的下一个同级元素节点。
			if (Final_time <= 10)//进行十分钟判断
			{
				// 解析123的子节点，并将他们存入node_list中
				tinyxml2::XMLElement* ErrorTitle = pItem->FirstChildElement("123");
				node_list.push_back(std::string(ErrorTitle->GetText()));
				tinyxml2::XMLElement* StackTrace = pItem->FirstChildElement("123");
				node_list.push_back(std::string(StackTrace->GetText()));
				tinyxml2::XMLElement* ScriptLanguage = pItem->FirstChildElement("123");
				node_list.push_back(std::string(ScriptLanguage->GetText()));
			}
			else
			{
				std::cout << "时间未在十分钟之内" << endl;
				return;
			}
		}
	}
	else {
		std::cout << "数据获取错误，没有相应字段" << endl;
		return;
	}
	return;
}


void GetFileNum(const std::string& inPath, vector<string>& files, std::string format)
{
	intptr_t hFile = 0;//文件句柄，过会儿用来查找
	struct _finddata_t fileinfo;//文件信息，声明一个存储文件信息的结构体 
	string p;
	if ((hFile = _findfirst(p.assign(inPath).append("//*" + format).c_str(), &fileinfo)) != -1)
		//如果查找到第一个文件
	{
		do
		{
			//如果是文件夹，迭代（即文件夹内还有文件夹）
			if ((fileinfo.attrib & _A_SUBDIR))
			{
				//文件名不等于"."&&文件名不等于".."
				//.表示当前目录
				//..表示当前目录的父目录
				//判断时，两者都要忽略，不然就无限递归跳不出去了！
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					GetFileNum(p.assign(inPath).append("\\").append(fileinfo.name), files, format);
			}
			else//如果是文件，加入数组
			{
				files.push_back(p.assign(inPath).append("\\").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);    //能寻找到其他文件

		_findclose(hFile);    //结束查找，关闭句柄


	}
}


int main(int argc, char* argv[])
{//VsDebugConsole
	
	bool szbool = ProcessesBool();
	if (szbool) {
		std::cout << "该模块禁止重复开启" << endl;
		return 0;
	}
	else 
	{
		std::string name_extension = ".xml";// 读取文件夹下的后缀名
		vector<std::string> files;// 创建一个存储所有文件路径的列表
		std::string files_path = "C:\\Users\\admin\\Downloads";	// 文件夹路径
		GetFileNum(files_path, files, name_extension);//调用方法获取所有文件路径
		std::string first_path = files[0];
		tinyxml2::XMLDocument tinyXmlDoc;//创建xml对象
		tinyxml2::XMLError error = tinyXmlDoc.LoadFile(first_path.c_str());//进行读取
		if (error != tinyxml2::XML_SUCCESS) {//做读取成功判断
			std::cout << "main:读取xml 失败：" << tinyXmlDoc.ErrorStr() << endl;
			return EXIT_FAILURE;
		}
		CreateNewArray(&tinyXmlDoc, files, first_path.c_str());// 创建新的数组,放到原来的数组中
		bool result = tinyXmlDoc.SaveFile(first_path.c_str());//写入到文件中
		printf("文件写入成功！\n");
		printf("崩溃信息存放在         %s", first_path.c_str());
		files.clear();
		tinyXmlDoc.Clear();
	}
	

}


