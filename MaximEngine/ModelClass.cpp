#include "ModelClass.h"

ModelClass::ModelClass()
{
}

ModelClass::ModelClass(std::string modelName)
{
	m_ModelName = modelName;

	m_model = getModelFromLoader();

	m_map = getMap();
}

VulkanCookbook::Mesh* ModelClass::getMeshModel()
{
	return &m_model;
}

VulkanCookbook::Mesh* ModelClass::getMapModel()
{
	return &m_map;
}

VulkanCookbook::Mesh ModelClass::getModelFromLoader()
{
	VulkanCookbook::Mesh Model;

	// Vertex data
	bool success = Load3DModelFromObjFile("zep.obj", true, false, false, true, Model);

	if (!success) std::cout << "Le model ne peut etre charge !!!" << std::endl;

	return Model;
}

VulkanCookbook::Mesh ModelClass::getMap()
{
	VulkanCookbook::Mesh Model;
	// Vertex data
	bool success = Load3DModelFromObjFile("Data/Models/plane.obj", false, true, false, false, Model);
	
	if (!success) std::cout << "map non loade !!" << std::endl;

	return Model;
}
