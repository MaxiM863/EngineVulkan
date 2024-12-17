#include<iostream>
#include<string.h>

#include "CookbookSampleFramework.h"

class ModelClass
{
public:

	ModelClass();
	ModelClass(std::string modelName);

	VulkanCookbook::Mesh* getMeshModel();
	VulkanCookbook::Mesh* getMapModel();

private:

	VulkanCookbook::Mesh getModelFromLoader();
	VulkanCookbook::Mesh getMap();

private:

	std::string m_ModelName;
	VulkanCookbook::Mesh m_model;
	VulkanCookbook::Mesh m_map;
};
