#ifndef INTER
#define INTER

#include "CookbookSampleFramework.h"

//using namespace VulkanCookbook;

class interGraph : public VulkanCookbook::VulkanCookbookSample
{

    public:

    
    
    interGraph(VulkanCookbook::VulkanCookbookSample* oop){

        *Instance = *oop->Instance;
        PhysicalDevice = oop->PhysicalDevice;
        *LogicalDevice = *oop->LogicalDevice;
        *PresentationSurface = *oop->PresentationSurface;
        GraphicsQueue = oop->GraphicsQueue;
        ComputeQueue = oop->ComputeQueue;
        PresentQueue = oop->PresentQueue;
        //Swapchain.Format = oop->Swapchain.Format;
        /**Swapchain.Handle = *oop->Swapchain.Handle;
        Swapchain.Images = oop->Swapchain.Images;
        Swapchain.ImageViews = oop->Swapchain.ImageViews;
        Swapchain.ImageViewsRaw = oop->Swapchain.ImageViewsRaw;
        Swapchain.Size = oop->Swapchain.Size;*/
        *CommandPool = *oop->CommandPool;
        //DepthImages = oop->DepthImages;
        //DepthImagesMemory = oop->DepthImagesMemory;
        //FramesResources = oop->FramesResources;
    }

    bool  Initialize( WindowParameters window_parameters ) override {

        return true;
    }
    
    bool  Draw() override {

        return true;
    }

    bool  Resize() override {

        return true;
    }

    void  Deinitialize() override {

        
    }

};

#endif