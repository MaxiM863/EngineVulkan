#include "Scene.h"

using namespace VulkanCookbook;

Scene::Scene()
{
	m_camera = VulkanCookbook::OrbitingCamera(Vector3{ 0.0f, 0.6f, 0.0f }, 4.0f);
	m_Model = ModelClass("testMaxim");
}

Scene::Scene(ModelClass model)
{
	m_camera = VulkanCookbook::OrbitingCamera(Vector3{ 0.0f, 0.6f, 0.0f }, 4.0f);
	m_Model = model;
}

ModelClass* Scene::getModel()
{
	return &m_Model;
}

VulkanCookbook::OrbitingCamera* Scene::getCamera()
{
	return &m_camera;
}


