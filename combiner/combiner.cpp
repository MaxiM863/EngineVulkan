#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>

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

	/*Graphics engine;

	WindowFramework window("Maxim Engine 1_0", 100, 100, 500, 500, engine);

	window.Render();*/

	ofstream O("compacte.cppl");

	for( const auto& name : get_filenames( "." ) )
	{

		if(name.at(name.size()-1) == 'p')
		{
			// Open the text file named "input.txt"
			ifstream f(name);

			// Check if the file is successfully opened
			if (!f.is_open()) {
				cerr << "Error opening the file!";
				return 1;
			}

			// String variable to store the read data
			string s;

			// Read each line of the file and print it to the
			// standard output stream till the whole file is
			// completely read
			while (getline(f, s))
				if(s._Starts_with("#include \"01_Instance_and_Devices/"))
				{
					O << "#include \"01_Instance_and_Devices/compacte.h\"" << '\n';
				}
                else if(s._Starts_with("#include \"02_Image_Presentation/"))
                {
                    O << "#include \"02_Image_Presentation/compacte.h\"" << '\n';
                }
                else if(s._Starts_with("#include \"03_Command_Buffers_and_Synchronization/"))
                {
                    O << "#include \"03_Command_Buffers_and_Synchronization/compacte.h\"" << '\n';
                }
                else if(s._Starts_with("#include \"04_Resources_and_Memory/"))
                {
                    O << "#include \"04_Resources_and_Memory/compacte.h\"" << '\n';
                }
                else if(s._Starts_with("#include \"05_Descriptor_Sets/"))
                {
                    O << "#include \"05_Descriptor_Sets/compacte.h\"" << '\n';
                }
                else if(s._Starts_with("#include \"06_Render_Passes_and_Framebuffers/"))
                {
                    O << "#include \"06_Render_Passes_and_Framebuffers/compacte.h\"" << '\n';
                }
                else if(s._Starts_with("#include \"08_Graphics_and_Compute_Pipelines/"))
                {
                    O << "#include \"08_Graphics_and_Compute_Pipelines/compacte.h\"" << '\n';
                }
                else if(s._Starts_with("#include \"09_Command_Recording_and_Drawing/"))
                {
                    O << "#include \"09_Command_Recording_and_Drawing/compacte.h\"" << '\n';
                }
                else if(s._Starts_with("#include \"10_Helper_Recipes/"))
                {
                    O << "#include \"10_Helper_Recipes/compacte.h\"" << '\n';
                }
				else O << s << '\n';

			// Close the file
			f.close();
		}
	}

	O.close();

	return 0;
}