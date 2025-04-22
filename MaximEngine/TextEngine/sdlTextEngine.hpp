#ifndef SDL_ENGINE
#define SDL_ENGINE

#include <windows.h>
#include <gdiplus.h>
#include <vector>
#pragma comment(lib, "gdiplus.lib")

#include <iostream>
#include <fstream>
#include "CookbookSampleFramework.h"
#include "OrbitingCamera.h"

using namespace Gdiplus;
//using namespace VulkanCookbook;

#pragma pack(push, 1)
struct BMPFileHeader {
    uint16_t fileType{0x4D42}; // 'BM'
    uint32_t fileSize{0};
    uint16_t reserved1{0};
    uint16_t reserved2{0};
    uint32_t offsetData{54};
};
#pragma pack(pop)

struct BMPInfoHeader {
    uint32_t size{40}; // Header size
    int32_t width{0};
    int32_t height{0};
    uint16_t planes{1};
    uint16_t bitCount{32}; // Bits per pixel
    uint32_t compression{0};
    uint32_t sizeImage{0};
    int32_t xPixelsPerMeter{0};
    int32_t yPixelsPerMeter{0};
    uint32_t colorsUsed{0};
    uint32_t colorsImportant{0};
};



class sdlTextEngine
{
    VkDestroyer(VkBuffer)               VertexBuffer;
    VkDestroyer(VkDeviceMemory)         VertexBufferMemory;

    VkDestroyer(VkImage)                Image;
    VkDestroyer(VkDeviceMemory)         ImageMemory;
    VkDestroyer(VkImageView)            ImageView;
    VkDestroyer(VkSampler)              Sampler;

    VkDestroyer(VkRenderPass)               RenderPass;
    VkDestroyer(VkPipelineLayout)           PipelineLayout;
    VkDestroyer(VkPipeline)                 Pipeline;

    VkDestroyer(VkDescriptorSetLayout)  DescriptorSetLayout;
    VkDestroyer(VkDescriptorPool)       DescriptorPool;
    std::vector<VkDescriptorSet>        DescriptorSets;

    VkDestroyer(VkBuffer)               UniformBuffer;
    VkDestroyer(VkDeviceMemory)         UniformBufferMemory;

    VulkanCookbook::Mesh                Model;

    VkDestroyer(VkBuffer)               StagingBuffer;
    VkDestroyer(VkDeviceMemory)         StagingBufferMemory;

    OrbitingCamera Camera;

    public:
    
        sdlTextEngine(){};   
    
        std::vector<BYTE> sdlTextEngineT() {

            GdiplusStartupInput gdiplusStartupInput;
            ULONG_PTR gdiplusToken;
            GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);
        
            // Create a font
            tagLOGFONTW logfont = {0};
            logfont.lfHeight = 48; // Font height
            wcscpy_s(logfont.lfFaceName, 6, L"Arial"); // Font name
        
            HFONT hFont = CreateFontIndirectW(&logfont);
        
            // Create a memory device context
            HDC hdc = CreateCompatibleDC(nullptr);
            SelectObject(hdc, hFont);
        
            // Create a bitmap
            HBITMAP hBitmap = CreateCompatibleBitmap(hdc, 300, 100);
            SelectObject(hdc, hBitmap);
        
            // Set text color and background
            SetTextColor(hdc, RGB(0, 0, 0));
            SetBkColor(hdc, RGB(255, 255, 255));
            RECT rect = {0, 0, 300, 100};
            FillRect(hdc, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));
        
            // Draw text
            const wchar_t* text = L"Hello, World!";
            DrawTextW(hdc, text, -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        
            // Save the bitmap to a file
            std::vector<BYTE> dataR = HBitmapToArray(hBitmap);
        
            // Cleanup
            DeleteObject(hBitmap);
            DeleteObject(hFont);
            DeleteDC(hdc);
            GdiplusShutdown(gdiplusToken);
        
        return dataR;        
    }

    std::vector<BYTE> HBitmapToArray(HBITMAP hBitmap) {
        BITMAP bmp;
        GetObjectW(hBitmap, sizeof(BITMAP), &bmp);
    
        BITMAPINFOHEADER bi;
        ZeroMemory(&bi, sizeof(BITMAPINFOHEADER));
        bi.biSize = sizeof(BITMAPINFOHEADER);
        bi.biWidth = bmp.bmWidth;
        bi.biHeight = bmp.bmHeight; // Negative to indicate top-down bitmap
        bi.biPlanes = 1;
        bi.biBitCount = 32; // Assuming 24-bit bitmap
        bi.biCompression = BI_RGB;
    
        int imageSize = bmp.bmWidth * bmp.bmHeight * 4; // 3 bytes per pixel for 24-bit
        std::vector<BYTE> buffer(imageSize);
    
        HDC hdc = GetDC(NULL);
        GetDIBits(hdc, hBitmap, 0, bmp.bmHeight, buffer.data(), (BITMAPINFO*)&bi, DIB_RGB_COLORS);
        ReleaseDC(NULL, hdc);

        createBMP(buffer, 300, 100, "output.bmp");
    
        return buffer;
    }

    

    void createBMP(const std::vector<uint8_t>& pixelData, int width, int height, const std::string& filename) {

        BMPFileHeader fileHeader;
        BMPInfoHeader infoHeader;
    
        infoHeader.width = width;
        infoHeader.height = height;
        fileHeader.fileSize = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + pixelData.size();
        infoHeader.sizeImage = pixelData.size();
    
        // Write the header to a file
        FILE *file = fopen("output.bmp", "wb");
        if (file == NULL) {
            perror("Failed to open file");
        }

        fwrite(&fileHeader, sizeof(BMPFileHeader), 1, file);
        fwrite(&infoHeader, sizeof(BMPInfoHeader), 1, file);
        fwrite(&pixelData[0], pixelData.size(), 1, file);

        fclose(file);
        printf("BMP header written to output.bmp\n");
    }    

    bool Init(BYTE* imageData, OrbitingCamera Camera)
    {
        this->Camera = Camera;

        return true;
    }

    bool Draw(VkCommandBuffer& command_buffer) 
    {

        BufferTransition pre_transfer_transition = {
        *UniformBuffer,               // VkBuffer         Buffer
        VK_ACCESS_UNIFORM_READ_BIT,   // VkAccessFlags    CurrentAccess
        VK_ACCESS_TRANSFER_WRITE_BIT, // VkAccessFlags    NewAccess
        VK_QUEUE_FAMILY_IGNORED,      // uint32_t         CurrentQueueFamily
        VK_QUEUE_FAMILY_IGNORED       // uint32_t         NewQueueFamily
        };

        SetBufferMemoryBarrier( command_buffer, VK_PIPELINE_STAGE_VERTEX_SHADER_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, { pre_transfer_transition } );

        std::vector<VkBufferCopy> regions = {
        {
            0,                        // VkDeviceSize     srcOffset
            0,                        // VkDeviceSize     dstOffset
            2 * 16 * sizeof( float )  // VkDeviceSize     size
        }
        };

        CopyDataBetweenBuffers( command_buffer, *StagingBuffer, *UniformBuffer, regions );

        BufferTransition post_transfer_transition = {
        *UniformBuffer,               // VkBuffer         Buffer
        VK_ACCESS_TRANSFER_WRITE_BIT, // VkAccessFlags    CurrentAccess
        VK_ACCESS_UNIFORM_READ_BIT,   // VkAccessFlags    NewAccess
        VK_QUEUE_FAMILY_IGNORED,      // uint32_t         CurrentQueueFamily
        VK_QUEUE_FAMILY_IGNORED       // uint32_t         NewQueueFamily
        };

        SetBufferMemoryBarrier( command_buffer, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_VERTEX_SHADER_BIT, { post_transfer_transition } );
    
        BindVertexBuffers( command_buffer, 0, { {*VertexBuffer, 0} } );

        VkPipelineLayout a = *PipelineLayout;
            
        BindDescriptorSets( command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, *PipelineLayout, 0, { DescriptorSets }, { } );
           
        BindPipelineObject( command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, *Pipeline );

        DrawGeometry( command_buffer, Model.Data.size(), 1, Model.Parts[0].VertexOffset, 0 );
        
        return true;
    }


    bool Initialize(WindowParameters window_parameters, interGraph* a, VkCommandBuffer& CommandBuffer)
    {
        // Combined image sampler
        int width = 300;
        int height = 100;
        
        std::vector<unsigned char> image_data = sdlTextEngineT();

        InitVkDestroyer( a->LogicalDevice, Sampler );
        InitVkDestroyer( a->LogicalDevice, Image );
        InitVkDestroyer( a->LogicalDevice, ImageMemory );
        InitVkDestroyer( a->LogicalDevice, ImageView );
        if( !CreateCombinedImageSampler( a->PhysicalDevice, *a->LogicalDevice, VK_IMAGE_TYPE_2D, VK_FORMAT_R8G8B8A8_UNORM, { (uint32_t)width, (uint32_t)height, 1 },
            1, 1, VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT, false, VK_IMAGE_VIEW_TYPE_2D, VK_IMAGE_ASPECT_COLOR_BIT, VK_FILTER_LINEAR,
            VK_FILTER_LINEAR, VK_SAMPLER_MIPMAP_MODE_NEAREST, VK_SAMPLER_ADDRESS_MODE_REPEAT, VK_SAMPLER_ADDRESS_MODE_REPEAT,
            VK_SAMPLER_ADDRESS_MODE_REPEAT, 0.0f, false, 1.0f, false, VK_COMPARE_OP_ALWAYS, 0.0f, 1.0f, VK_BORDER_COLOR_FLOAT_OPAQUE_BLACK,
            false, *Sampler, *Image, *ImageMemory, *ImageView ) ) {
            return false;
        }

        VkImageSubresourceLayers image_subresource_layer = {
            VK_IMAGE_ASPECT_COLOR_BIT,    // VkImageAspectFlags     aspectMask
            0,                            // uint32_t               mipLevel
            0,                            // uint32_t               baseArrayLayer
            1                             // uint32_t               layerCount
        };

        if( !UseStagingBufferToUpdateImageWithDeviceLocalMemoryBound( a->PhysicalDevice, *a->LogicalDevice, static_cast<VkDeviceSize>(image_data.size()),
            &image_data[0], *Image, image_subresource_layer, { 0, 0, 0 }, { (uint32_t)width, (uint32_t)height, 1 }, VK_IMAGE_LAYOUT_UNDEFINED,
            VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, 0, VK_ACCESS_SHADER_READ_BIT, VK_IMAGE_ASPECT_COLOR_BIT, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
            VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, a->GraphicsQueue.Handle, CommandBuffer, {} ) ) {
            return false;
        }            

        Load3DModelFromObjFile( "Data/Models/chess_fou.obj", false, true, false, true, Model );
            
        InitVkDestroyer( a->LogicalDevice, VertexBuffer );
        if( !CreateBuffer( *a->LogicalDevice, sizeof( float ) * Model.Data.size(),
            VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, *VertexBuffer ) ) {
            return false;
        }              

        InitVkDestroyer( a->LogicalDevice, VertexBufferMemory );
        if( !AllocateAndBindMemoryObjectToBuffer( a->PhysicalDevice, *a->LogicalDevice, *VertexBuffer, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, *VertexBufferMemory ) ) {
            return false;
        }

        if( !UseStagingBufferToUpdateBufferWithDeviceLocalMemoryBound( a->PhysicalDevice, *a->LogicalDevice, sizeof( Model.Data[0] ) * Model.Data.size(),
            &Model.Data[0], *VertexBuffer, 0, 0, VK_ACCESS_VERTEX_ATTRIBUTE_READ_BIT, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_VERTEX_INPUT_BIT,
            a->GraphicsQueue.Handle, CommandBuffer, {} ) ) {
            return false;
        }

        // Staging buffer
        InitVkDestroyer( a->LogicalDevice, StagingBuffer );
        if( !CreateBuffer( *a->LogicalDevice, 2 * 16 * sizeof(float), VK_BUFFER_USAGE_TRANSFER_SRC_BIT, *StagingBuffer ) ) {
            return false;
        }
        InitVkDestroyer( a->LogicalDevice, StagingBufferMemory );
        if( !AllocateAndBindMemoryObjectToBuffer( a->PhysicalDevice, *a->LogicalDevice, *StagingBuffer, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, *StagingBufferMemory ) ) {
            return false;
        }

        InitVkDestroyer( a->LogicalDevice, DescriptorSetLayout );

            // Uniform buffer
      InitVkDestroyer( a->LogicalDevice, UniformBuffer );
      InitVkDestroyer( a->LogicalDevice, UniformBufferMemory );
      if( !CreateUniformBuffer( a->PhysicalDevice, *a->LogicalDevice, 2 * 16 * sizeof( float ), VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
        *UniformBuffer, *UniformBufferMemory ) ) {
        return false;
      }

      if( !UpdateStagingBuffer( true, Camera, a ) ) {
        return false;
      }

            // Descriptor set with uniform buffer
      std::vector<VkDescriptorSetLayoutBinding> descriptor_set_layout_binding = {
        {
          0,                                          
          VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC,        
          1,                                          
          VK_SHADER_STAGE_VERTEX_BIT,                 
          nullptr
        }
        ,
        {
          1,                                          // uint32_t             binding
          VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,  // VkDescriptorType     descriptorType
          1,                                          // uint32_t             descriptorCount
          VK_SHADER_STAGE_FRAGMENT_BIT,               // VkShaderStageFlags   stageFlags
          nullptr                                     // const VkSampler    * pImmutableSamplers
        }
      };

      if( !CreateDescriptorSetLayout( *a->LogicalDevice, { descriptor_set_layout_binding }, *DescriptorSetLayout ) ) {
        return false;
      }

      std::vector<VkDescriptorPoolSize> descriptor_pool_sizes = {
        {
          VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC,          // VkDescriptorType     type
          1                                           // uint32_t             descriptorCount
        },
        {
          VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,  // VkDescriptorType     type
          1                                           // uint32_t             descriptorCount
        }
      };

      InitVkDestroyer( a->LogicalDevice, DescriptorPool );
      if( !CreateDescriptorPool( *a->LogicalDevice, true, 1, descriptor_pool_sizes, *DescriptorPool ) ) {
        return false;
      }

      if( !AllocateDescriptorSets( *a->LogicalDevice, *DescriptorPool, { *DescriptorSetLayout }, DescriptorSets) ) {
        return false;
      }

      BufferDescriptorInfo buffer_descriptor_update = {
        DescriptorSets[0],                          // VkDescriptorSet                      TargetDescriptorSet
        0,                                          // uint32_t                             TargetDescriptorBinding
        0,                                          // uint32_t                             TargetArrayElement
        VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC,          // VkDescriptorType                     TargetDescriptorType
        {                                           // std::vector<VkDescriptorBufferInfo>  BufferInfos
          {
            *UniformBuffer,                           // VkBuffer                             buffer
            0*2*16*sizeof(float),                                        // VkDeviceSize                         offset
            2*16*sizeof(float)                             // VkDeviceSize                         range
          }
        }
      };

      ImageDescriptorInfo image_descriptor_update = {
        DescriptorSets[0],                          // VkDescriptorSet                      TargetDescriptorSet
        1,                                          // uint32_t                             TargetDescriptorBinding
        0,                                          // uint32_t                             TargetArrayElement
        VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,  // VkDescriptorType                     TargetDescriptorType
        {                                           // std::vector<VkDescriptorImageInfo>   ImageInfos
          {
            *Sampler,                                 // VkSampler                            sampler
            *ImageView,                               // VkImageView                          imageView
            VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL  // VkImageLayout                        imageLayout
          }
        }
      };      

      UpdateDescriptorSets( *a->LogicalDevice, { image_descriptor_update }, { buffer_descriptor_update }, {}, {} );

      // Render pass
      std::vector<VkAttachmentDescription> attachment_descriptions = {
        {
          0,                                                // VkAttachmentDescriptionFlags     flags
          a->Swapchain.Format,                                 // VkFormat                         format
          VK_SAMPLE_COUNT_1_BIT,                            // VkSampleCountFlagBits            samples
          VK_ATTACHMENT_LOAD_OP_CLEAR,                      // VkAttachmentLoadOp               loadOp
          VK_ATTACHMENT_STORE_OP_STORE,                     // VkAttachmentStoreOp              storeOp
          VK_ATTACHMENT_LOAD_OP_DONT_CARE,                  // VkAttachmentLoadOp               stencilLoadOp
          VK_ATTACHMENT_STORE_OP_DONT_CARE,                 // VkAttachmentStoreOp              stencilStoreOp
          VK_IMAGE_LAYOUT_UNDEFINED,                        // VkImageLayout                    initialLayout
          VK_IMAGE_LAYOUT_PRESENT_SRC_KHR                   // VkImageLayout                    finalLayout
        },
        {
          0,                                                // VkAttachmentDescriptionFlags     flags
          a->DepthFormat,                                      // VkFormat                         format
          VK_SAMPLE_COUNT_1_BIT,                            // VkSampleCountFlagBits            samples
          VK_ATTACHMENT_LOAD_OP_CLEAR,                      // VkAttachmentLoadOp               loadOp
          VK_ATTACHMENT_STORE_OP_DONT_CARE,                 // VkAttachmentStoreOp              storeOp
          VK_ATTACHMENT_LOAD_OP_DONT_CARE,                  // VkAttachmentLoadOp               stencilLoadOp
          VK_ATTACHMENT_STORE_OP_DONT_CARE,                 // VkAttachmentStoreOp              stencilStoreOp
          VK_IMAGE_LAYOUT_UNDEFINED,                        // VkImageLayout                    initialLayout
          VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL  // VkImageLayout                    finalLayout
        }
      };

      VkAttachmentReference depth_attachment = {
        1,                                                // uint32_t                             attachment
        VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL  // VkImageLayout                        layout
      };

      std::vector<SubpassParameters> subpass_parameters = {
        {
          VK_PIPELINE_BIND_POINT_GRAPHICS,              // VkPipelineBindPoint                  PipelineType
          {},                                           // std::vector<VkAttachmentReference>   InputAttachments
          {                                             // std::vector<VkAttachmentReference>   ColorAttachments
            {
              0,                                          // uint32_t                             attachment
              VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,   // VkImageLayout                        layout
            }
          },
          {},                                           // std::vector<VkAttachmentReference>   ResolveAttachments
          &depth_attachment,                            // VkAttachmentReference const        * DepthStencilAttachment
          {}                                            // std::vector<uint32_t>                PreserveAttachments
        }
      };

      std::vector<VkSubpassDependency> subpass_dependencies = {
        {
          VK_SUBPASS_EXTERNAL,                            // uint32_t                   srcSubpass
          0,                                              // uint32_t                   dstSubpass
          VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,              // VkPipelineStageFlags       srcStageMask
          VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,  // VkPipelineStageFlags       dstStageMask
          VK_ACCESS_MEMORY_READ_BIT,                      // VkAccessFlags              srcAccessMask
          VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,           // VkAccessFlags              dstAccessMask
          VK_DEPENDENCY_BY_REGION_BIT                     // VkDependencyFlags          dependencyFlags
        },
        {
          0,                                              // uint32_t                   srcSubpass
          VK_SUBPASS_EXTERNAL,                            // uint32_t                   dstSubpass
          VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,  // VkPipelineStageFlags       srcStageMask
          VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,              // VkPipelineStageFlags       dstStageMask
          VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,           // VkAccessFlags              srcAccessMask
          VK_ACCESS_MEMORY_READ_BIT,                      // VkAccessFlags              dstAccessMask
          VK_DEPENDENCY_BY_REGION_BIT                     // VkDependencyFlags          dependencyFlags
        }
      };

      InitVkDestroyer( a->LogicalDevice, RenderPass );
      if( !CreateRenderPass( *a->LogicalDevice, attachment_descriptions, subpass_parameters, subpass_dependencies, *RenderPass ) ) {
        return false;
      }

      // Graphics pipeline

      std::vector<VkPushConstantRange> push_constant_ranges = {
        {
          VK_SHADER_STAGE_FRAGMENT_BIT,   // VkShaderStageFlags     stageFlags
          0,                              // uint32_t               offset
          sizeof( float ) * 4             // uint32_t               size
        }
      };

      InitVkDestroyer( a->LogicalDevice, PipelineLayout );
      if( !CreatePipelineLayout( *a->LogicalDevice, { *DescriptorSetLayout }, {}, *PipelineLayout ) ) {
        return false;
      }

      std::vector<unsigned char> vertex_shader_spirv;
      if( !GetBinaryFileContents( "Data/Shaders/11 Lighting/01 Rendering a geometry with vertex diffuse lighting/vert.spv", vertex_shader_spirv ) ) {
        return false;
      }

      VkDestroyer(VkShaderModule) vertex_shader_module;
      InitVkDestroyer( a->LogicalDevice, vertex_shader_module );
      if( !CreateShaderModule( *a->LogicalDevice, vertex_shader_spirv, *vertex_shader_module ) ) {
        return false;
      }

      std::vector<unsigned char> fragment_shader_spirv;
      if( !GetBinaryFileContents( "Data/Shaders/11 Lighting/01 Rendering a geometry with vertex diffuse lighting/frag.spv", fragment_shader_spirv ) ) {
        return false;
      }
      VkDestroyer(VkShaderModule) fragment_shader_module;
      InitVkDestroyer( a->LogicalDevice, fragment_shader_module );
      if( !CreateShaderModule( *a->LogicalDevice, fragment_shader_spirv, *fragment_shader_module ) ) {
        return false;
      }

      std::vector<ShaderStageParameters> shader_stage_params = {
        {
          VK_SHADER_STAGE_VERTEX_BIT,       // VkShaderStageFlagBits        ShaderStage
          *vertex_shader_module,            // VkShaderModule               ShaderModule
          "main",                           // char const                 * EntryPointName
          nullptr                           // VkSpecializationInfo const * SpecializationInfo
        },
        {
          VK_SHADER_STAGE_FRAGMENT_BIT,     // VkShaderStageFlagBits        ShaderStage
          *fragment_shader_module,          // VkShaderModule               ShaderModule
          "main",                           // char const                 * EntryPointName
          nullptr                           // VkSpecializationInfo const * SpecializationInfo
        }
      };

      std::vector<VkPipelineShaderStageCreateInfo> shader_stage_create_infos;
      SpecifyPipelineShaderStages( shader_stage_params, shader_stage_create_infos );

      std::vector<VkVertexInputBindingDescription> vertex_input_binding_descriptions = {
        {
          0,                            // uint32_t                     binding
          5 * sizeof(float),                // uint32_t                     stride
          VK_VERTEX_INPUT_RATE_VERTEX   // VkVertexInputRate            inputRate
        }
      };
  
      std::vector<VkVertexInputAttributeDescription> vertex_attribute_descriptions = {
        { // Position
          0,                                                                        // uint32_t   location
          0,                                                                        // uint32_t   binding
          VK_FORMAT_R32G32B32_SFLOAT,                                               // VkFormat   format
          0                                                                         // uint32_t   offset
        },        
        { // Texcoords
          1,                                                                        // uint32_t   location
          0,                                                                        // uint32_t   binding
          VK_FORMAT_R32G32_SFLOAT,                                                  // VkFormat   format
          3 * sizeof( float )                                                       // uint32_t   offset
        }
      };

      VkPipelineVertexInputStateCreateInfo vertex_input_state_create_info;
      SpecifyPipelineVertexInputState( vertex_input_binding_descriptions, vertex_attribute_descriptions, vertex_input_state_create_info );

      VkPipelineInputAssemblyStateCreateInfo input_assembly_state_create_info;
      SpecifyPipelineInputAssemblyState( VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST, false, input_assembly_state_create_info );

      ViewportInfo viewport_infos = {
        {                     // std::vector<VkViewport>   Viewports
          {
            0.0f,               // float          x
            0.0f,               // float          y
            500.0f,             // float          width
            500.0f,             // float          height
            0.0f,               // float          minDepth
            1.0f                // float          maxDepth
          }
        },
        {                     // std::vector<VkRect2D>     Scissors
          {
            {                   // VkOffset2D     offset
              0,                  // int32_t        x
              0                   // int32_t        y
            },
            {                   // VkExtent2D     extent
              500,                // uint32_t       width
              500                 // uint32_t       height
            }
          }
        }
      };

      VkPipelineViewportStateCreateInfo viewport_state_create_info;
      SpecifyPipelineViewportAndScissorTestState( viewport_infos, viewport_state_create_info );

      VkPipelineRasterizationStateCreateInfo rasterization_state_create_info;
      SpecifyPipelineRasterizationState( false, false, VK_POLYGON_MODE_FILL, VK_CULL_MODE_BACK_BIT, VK_FRONT_FACE_COUNTER_CLOCKWISE, false, 0.0f, 0.0f, 0.0f, 1.0f, rasterization_state_create_info );

      VkPipelineMultisampleStateCreateInfo multisample_state_create_info;
      SpecifyPipelineMultisampleState( VK_SAMPLE_COUNT_1_BIT, false, 0.0f, nullptr, false, false, multisample_state_create_info );

      VkPipelineDepthStencilStateCreateInfo depth_stencil_state_create_info;
      SpecifyPipelineDepthAndStencilState( true, true, VK_COMPARE_OP_LESS_OR_EQUAL, false, 0.0f, 1.0f, false, {}, {}, depth_stencil_state_create_info );

      std::vector<VkPipelineColorBlendAttachmentState> attachment_blend_states = {
        {
          false,                          // VkBool32                 blendEnable
          VK_BLEND_FACTOR_ONE,            // VkBlendFactor            srcColorBlendFactor
          VK_BLEND_FACTOR_ONE,            // VkBlendFactor            dstColorBlendFactor
          VK_BLEND_OP_ADD,                // VkBlendOp                colorBlendOp
          VK_BLEND_FACTOR_ONE,            // VkBlendFactor            srcAlphaBlendFactor
          VK_BLEND_FACTOR_ONE,            // VkBlendFactor            dstAlphaBlendFactor
          VK_BLEND_OP_ADD,                // VkBlendOp                alphaBlendOp
          VK_COLOR_COMPONENT_R_BIT |      // VkColorComponentFlags    colorWriteMask
          VK_COLOR_COMPONENT_G_BIT |
          VK_COLOR_COMPONENT_B_BIT |
          VK_COLOR_COMPONENT_A_BIT
        }
      };
      VkPipelineColorBlendStateCreateInfo blend_state_create_info;
      SpecifyPipelineBlendState( false, VK_LOGIC_OP_COPY, attachment_blend_states, { 1.0f, 1.0f, 1.0f, 1.0f }, blend_state_create_info );

      std::vector<VkDynamicState> dynamic_states = {
        VK_DYNAMIC_STATE_VIEWPORT,
        VK_DYNAMIC_STATE_SCISSOR
      };
      VkPipelineDynamicStateCreateInfo dynamic_state_create_info;
      SpecifyPipelineDynamicStates( dynamic_states, dynamic_state_create_info );

      VkGraphicsPipelineCreateInfo pipeline_create_info;
      SpecifyGraphicsPipelineCreationParameters( 0, shader_stage_create_infos, vertex_input_state_create_info, input_assembly_state_create_info,
        nullptr, &viewport_state_create_info, rasterization_state_create_info, &multisample_state_create_info, &depth_stencil_state_create_info, &blend_state_create_info,
        &dynamic_state_create_info, *PipelineLayout, *RenderPass, 0, VK_NULL_HANDLE, -1, pipeline_create_info );

      std::vector<VkPipeline> pipeline;
      if( !CreateGraphicsPipelines( *a->LogicalDevice, { pipeline_create_info }, VK_NULL_HANDLE, pipeline ) ) {
        return false;
      }
      InitVkDestroyer( a->LogicalDevice, Pipeline );
      *Pipeline = pipeline[0];

      return true;
    }

    bool UpdateStagingBuffer( bool force, OrbitingCamera Camera, ::interGraph* a ) {         
  
          if(true)
          {           
  
            
              Matrix4x4 rotation_matrix =  PrepareRotationMatrix( 15, { 1.0f, 1.0f, 0.0f } ) * PrepareRotationMatrix( 15, { 0.0f, -1.0f, -1.0f } );
              Matrix4x4 translation_matrix = PrepareTranslationMatrix(0,0,0); 
              Matrix4x4 scaling_matrix = PrepareScalingMatrix(1.0f,1.0f,1.0f);
              Matrix4x4 view = Camera.GetMatrix();
  
              Matrix4x4 model_view_matrix = view * scaling_matrix * rotation_matrix;
  
              if( !MapUpdateAndUnmapHostVisibleMemory( *a->LogicalDevice, *StagingBufferMemory, 0, sizeof( model_view_matrix[0] ) * model_view_matrix.size(), &model_view_matrix[0], true, nullptr ) ) {
                return false;
              }
  
              Matrix4x4 perspective_matrix = PreparePerspectiveProjectionMatrix( static_cast<float>(a->Swapchain.Size.width) / static_cast<float>(a->Swapchain.Size.height),
                90.0f, 0.1f, 100.0f );
  
              if( !MapUpdateAndUnmapHostVisibleMemory( *a->LogicalDevice, *StagingBufferMemory, sizeof( model_view_matrix[0] ) * model_view_matrix.size(),
                sizeof( perspective_matrix[0] ) * perspective_matrix.size(), &perspective_matrix[0], true, nullptr ) ) {
                return false;
              }
            } 
          
        
  
        return true;
      }
};

#endif