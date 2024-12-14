#pragma once

#include "CookbookSampleFramework.h"
#include "OrbitingCamera.h"
#include "ModelClass.h"

class Scene
{
public:

	Scene();
	Scene(ModelClass model);

	ModelClass* getModel();
	VulkanCookbook::OrbitingCamera* getCamera();

private:

	

private:

	ModelClass m_Model;
	VulkanCookbook::OrbitingCamera m_camera;
};

