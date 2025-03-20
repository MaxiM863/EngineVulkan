// Maxim Thibodeau: do not use without consent
//
// Base on MIT Vulkan cookbook
// 
// ******************************************************************************
//
// Copyright( c ) 2017 Packt
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files( the "Software" ), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// Vulkan Cookbook
// ISBN: 9781786468154
// � Packt Publishing Limited
//
// Author:   Pawel Lapinski
// LinkedIn: https://www.linkedin.com/in/pawel-lapinski-84522329
//
// Chapter: 11 Lighting
// Recipe:  02 Rendering a geometry with fragment specular lighting

#include "CookbookSampleFramework.h"
#include "Graphics.cpp"

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>

using namespace VulkanCookbook;
using namespace std;

std::vector<std::string> get_filenames( std::filesystem::path path )
{
	std::vector<std::string> data;

    namespace fs = std::filesystem;

	const fs::path pathToShow{ "." };

	for (const auto& entry : fs::directory_iterator(pathToShow)) {
		const auto filenameStr = entry.path().filename().string();
		if (entry.is_directory()) {
			//std::cout << "dir:  " << filenameStr << '\n';
		}
		else if (entry.is_regular_file()) {
			data.push_back(filenameStr);
		}
		//else
        	//std::cout << "??    " << filenameStr << '\n';
	}							
	
	return data;
}

int main(void) {

	Graphics engine;

	WindowFramework window("Maxim Engine 1_0", 100, 100, 500, 500, engine);

	window.Render();

	return 0;
}