#include<io.h>
#include<vector>
#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include "tinyxml2.h"
#include <ctime>
#include <filesystem>
#include <regex>
#include <queue>
#include <fstream>
#include <psapi.h>
#include<chrono>
#include <tchar.h>
#ifndef CIRCLE_H
#define CIRCLE_H

void CreateNewArray(tinyxml2::XMLDocument* tinyXmlDoc, std::vector<std::string> files, const char* first_path);
tinyxml2::XMLElement* CombineScript(tinyxml2::XMLElement* Library, std::vector<std::string > node_list);
void GetScriptSection(std::vector<std::string>& node_list, std::string file_dir);
void GetFileNum(const std::string& inPath, std::vector<std::string>& files, std::string format);
std::time_t ConvertToSeconds(tinyxml2::XMLDocument* Library);
bool ProcessesBool();
#endif