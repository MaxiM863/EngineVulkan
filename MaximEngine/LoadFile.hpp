#ifndef LOADFILE_HPP
#define LOADFILE_HPP


#include <string>
#include <fstream>
#include <iostream>

#include "CookbookSampleFramework.h"


class Load {

    public: bool Load3DModelFromTxtFile(std::string filename, std::vector<VulkanCookbook::Mesh>& mesh) {

        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Unable to open file\n";
            return false;
        }

        std::string line;

        int cntr = 0;

        int nbr_mesh = 0;

        bool meshName = true;
        bool indices = true;
        bool norms = false;

        std::vector<float> dataVertices;
        std::vector<float> dataNorms;
        std::vector<int> dataFaces;

        while (std::getline(file, line)) { // Read word by word
            
            
            if(cntr == 0)
            {
                nbr_mesh = atoi(line.c_str());

                mesh.reserve(nbr_mesh);

                cntr++;
            }
            else
            {
                if(!meshName)
                {
                    if(indices)
                    {
                        cntr = 10;
                        
                        char separator = ' ';
                        int i = 0;
                        
                        // Temporary string used to split the string.
                        std::string s; 
                        while (line[i] != '\0') {
                            if (line[i] != separator) {
                                // Append the char to the temp string.
                                s += line[i]; 
                            } else {
                                dataVertices.push_back(atof(s.c_str()));
                                s.clear();
                            }
                            i++;

                        }

                        indices = false;
                    }
                    else if(!norms)
                    {
                        norms = true;

                        cntr = 10;
                        
                        char separator = ' ';
                        int i = 0;
                        
                        // Temporary string used to split the string.
                        std::string s; 
                        while (line[i] != '\0') {
                            if (line[i] != separator) {
                                // Append the char to the temp string.
                                s += line[i]; 
                            } else {
                                dataNorms.push_back(atof(s.c_str()));
                                s.clear();
                            }
                            i++;

                        }
                        
                        indices = false;
                    }
                    else
                    {
                        cntr = 10;
                        
                        char separator = ' ';
                        int i = 0;
                        
                        // Temporary string used to split the string.
                        std::string s; 
                        while (line[i] != '\0') {
                            if (line[i] != separator) {
                                // Append the char to the temp string.
                                s += line[i]; 
                            } else {
                                dataFaces.push_back(atoi(s.c_str()));
                                s.clear();
                            }
                            i++;

                        }
                        
                        indices = false;

                        indices = true;
                        norms = false;

                        VulkanCookbook::Mesh m;

                        for(int i = 0; i < dataFaces.size(); i++)
                        {
                            m.Data.push_back(dataVertices[3*dataFaces[i]+0]);
                            m.Data.push_back(dataVertices[3*dataFaces[i]+1]);
                            m.Data.push_back(dataVertices[3*dataFaces[i]+2]);

                            m.Data.push_back(dataNorms[3*dataFaces[i]+0]);
                            m.Data.push_back(dataNorms[3*dataFaces[i]+1]);
                            m.Data.push_back(dataNorms[3*dataFaces[i]+2]);

                            m.Data.push_back(0.0f);
                            m.Data.push_back(1.0f);                           
                        }

                        std::vector<VulkanCookbook::Mesh::Part> parts;

                        VulkanCookbook::Mesh::Part P;

                        P.VertexCount = dataFaces.size();
                        P.VertexOffset = 0;

                        parts.push_back(P);

                        m.Parts = parts;

                        mesh.push_back(m);

                        dataVertices.clear();
                        dataFaces.clear();

                        meshName = true;
                    }
                }
                else
                {
                    meshName = false;

                    if(line.substr(0, 3) == "GUN")
                    {
                        
                        break;
                    }
                } 
            }     
        }

        file.close();

        return true;
    }

    public: float* Load3DModelFromBinFile(std::string filename, long long& size) {

        
        //if (!file) {
            /*std::cerr << "Unable to open file\nCreating it...\n";

            Mesh m;

            std::ofstream fileOut(filename.substr(0, filename.find_last_of('.')) + ".bin",  std::ios::binary);
            
            Load3DModelFromObjFile("Data/Models/map.obj", true, true, false, false, m);

            // Write mesh data to the file
            fileOut.write(reinterpret_cast<const char*>(m.Data.data()), m.Data.size() * sizeof(float));

            fileOut.close();*/
        //}
        size = getFileSize(filename);

        std::ifstream file(filename, std::ios::binary);
        
        float* mesh = new float[size / sizeof(float)];

        file.read(reinterpret_cast<char*>(&mesh[0]), size);

        file.close();

        float test = mesh[0];

        return mesh;
    }

    std::streamsize getFileSize(const std::string& filename) {
        std::ifstream file(filename, std::ios::binary | std::ios::ate); // open at end
        if (!file) {
            throw std::runtime_error("Cannot open file: " + filename);
        }

        long long size = file.tellg(); // position at end = size
        
        file.close();
        
        return size;
    }
};

#endif // LOADFILE_HPP