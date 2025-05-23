#ifndef VESSEL
#define VESSEL

#include <iostream>
#include <fstream>
#include "CookbookSampleFramework.h"
#include "OrbitingCamera.h"
#include "LoadFile.hpp"

class vessel
{

  VkDestroyer(VkDeviceMemory)         VertexBufferMemory;
  VkDestroyer(VkDeviceMemory)         ImageMemory;
  VkDestroyer(VkBuffer)               VertexBuffer;

  VkDestroyer(VkDeviceMemory)         StagingBufferMemory;
  VkDestroyer(VkBuffer)               StagingBuffer;

  VkDestroyer(VkDeviceMemory)         UniformBufferMemory;
  VkDestroyer(VkBuffer)               UniformBuffer;
  
  VkDestroyer(VkImage)                Image;
  VkDestroyer(VkImageView)            ImageView;
    
  VkDestroyer(VkSampler)              Sampler;
  
  VkDestroyer(VkDescriptorSetLayout)  DescriptorSetLayout;
  VkDestroyer(VkDescriptorPool)       DescriptorPool;
  std::vector<VkDescriptorSet>        DescriptorSets;
  
  VkDestroyer(VkRenderPass)           RenderPass;
  VkDestroyer(VkPipelineLayout)       PipelineLayout;
  VkDestroyer(VkPipeline)             Pipeline;
  
  Mesh                                Model;

  OrbitingCamera Camera;

  public: Mesh getMesh() {return Model;}

  bool UpdateUniformBuffer;

    public:
    
        vessel(){};   
    
        VkPipelineLayout getPipelineLayout() { return PipelineLayout.Object.Handle; };

        VkPipeline getGraphicsPipeline() { return Pipeline.Object.Handle; };

        VkDescriptorSetLayout getDescriptorSetLayout() { return DescriptorSetLayout.Object.Handle; };

        VkDescriptorPool getDescriptorPool() { return DescriptorPool.Object.Handle; };

        std::vector<VkDescriptorSet> getDescriptorSet() { return DescriptorSets; };

        VkBuffer getVertexBuffer() { return VertexBuffer.Object.Handle; };

        VkBuffer getUniformBuffer() { return UniformBuffer.Object.Handle; };

        VkBuffer getStagingBuffer() { return StagingBuffer.Object.Handle; };

        VkRenderPass getRenderPass() { return RenderPass.Object.Handle; };
    
        bool Initialize(VkDevice LogicalDevice, VkPhysicalDevice PhysicalDevice, QueueParameters& GraphicsQueue, VkCommandBuffer& CommandBuffer, SwapchainParameters& Swapchain, Mesh m)
        {
            uint32_t stride = 32;
        
            // Vertex data
        Model = m;
 
        // Vertex data
        /*if( !Load3DModelFromObjFile( "Data/Models/suzane.obj", true, true, false, false, Model ) ) {
            return false;
        }*/


        InitVkDestroyer( LogicalDevice, VertexBuffer );
        if( !CreateBuffer( LogicalDevice, 4 * Model.Data.size(),
            VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, *VertexBuffer ) ) {
            return false;
        }
    
        InitVkDestroyer( LogicalDevice, VertexBufferMemory );
        if( !AllocateAndBindMemoryObjectToBuffer( PhysicalDevice, LogicalDevice, *VertexBuffer, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, *VertexBufferMemory ) ) {
            return false;
        }
    
        if( !UseStagingBufferToUpdateBufferWithDeviceLocalMemoryBound( PhysicalDevice, LogicalDevice,  4 * Model.Data.size(),
            &Model.Data[0], *VertexBuffer, 0, 0, VK_ACCESS_VERTEX_ATTRIBUTE_READ_BIT, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_VERTEX_INPUT_BIT,
            GraphicsQueue.Handle, CommandBuffer, {} ) ) {
            return false;
        }
    
        // Staging buffer
        InitVkDestroyer( LogicalDevice, StagingBuffer );
        if( !CreateBuffer( LogicalDevice, 3 * 16 * sizeof(float), VK_BUFFER_USAGE_TRANSFER_SRC_BIT, *StagingBuffer ) ) {
            return false;
        }
        InitVkDestroyer( LogicalDevice, StagingBufferMemory );
        if( !AllocateAndBindMemoryObjectToBuffer( PhysicalDevice, LogicalDevice, *StagingBuffer, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, *StagingBufferMemory ) ) {
            return false;
        }
    
        // Uniform buffer
        InitVkDestroyer( LogicalDevice, UniformBuffer );
        InitVkDestroyer( LogicalDevice, UniformBufferMemory );
        if( !CreateUniformBuffer( PhysicalDevice, LogicalDevice, 3 * 16 * sizeof( float ), VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
            *UniformBuffer, *UniformBufferMemory ) ) {
            return false;
        }
    
        if( !UpdateStagingBuffer( true, LogicalDevice, static_cast<float>(Swapchain.Size.width) / static_cast<float>(Swapchain.Size.height), 0.0f, 0.0f) ) {
            return false;
        }
    
        // Descriptor set with uniform buffer
        VkDescriptorSetLayoutBinding descriptor_set_layout_binding = {
            0,                                          // uint32_t             binding
            VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,          // VkDescriptorType     descriptorType
            1,                                          // uint32_t             descriptorCount
            VK_SHADER_STAGE_VERTEX_BIT,                 // VkShaderStageFlags   stageFlags
            nullptr                                     // const VkSampler    * pImmutableSamplers
        };
        //InitVkDestroyer( LogicalDevice, DescriptorSetLayout );
        if( !CreateDescriptorSetLayout( LogicalDevice, { descriptor_set_layout_binding }, *DescriptorSetLayout ) ) {
            return false;
        }
    
        VkDescriptorPoolSize descriptor_pool_size = {
            VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,          // VkDescriptorType     type
            1                                           // uint32_t             descriptorCount
        };
        
        //InitVkDestroyer( LogicalDevice, DescriptorPool );
        if( !CreateDescriptorPool( LogicalDevice, false, 1, { descriptor_pool_size }, *DescriptorPool ) ) {
            return false;
        }
    
        if( !AllocateDescriptorSets( LogicalDevice, *DescriptorPool, { *DescriptorSetLayout }, DescriptorSets ) ) {
            return false;
        }
    
        BufferDescriptorInfo buffer_descriptor_update = {
            DescriptorSets[0],                          // VkDescriptorSet                      TargetDescriptorSet
            0,                                          // uint32_t                             TargetDescriptorBinding
            0,                                          // uint32_t                             TargetArrayElement
            VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,          // VkDescriptorType                     TargetDescriptorType
            {                                           // std::vector<VkDescriptorBufferInfo>  BufferInfos
            {
                *UniformBuffer,                           // VkBuffer                             buffer
                0,                                        // VkDeviceSize                         offset
                VK_WHOLE_SIZE                             // VkDeviceSize                         range
            }
            }
        };
    
        UpdateDescriptorSets( LogicalDevice, {}, { buffer_descriptor_update }, {}, {} );
    
        // Render pass
        std::vector<VkAttachmentDescription> attachment_descriptions = {
            {
            0,                                                // VkAttachmentDescriptionFlags     flags
            Swapchain.Format,                                 // VkFormat                         format
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
            VK_FORMAT_D16_UNORM,                                      // VkFormat                         format
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
    
        InitVkDestroyer( LogicalDevice, RenderPass );
        if( !CreateRenderPass( LogicalDevice, attachment_descriptions, subpass_parameters, subpass_dependencies, *RenderPass ) ) {
            return false;
        }
    
        // Graphics pipeline
    
        InitVkDestroyer( LogicalDevice, PipelineLayout );
        if( !CreatePipelineLayout( LogicalDevice, { *DescriptorSetLayout }, {}, *PipelineLayout ) ) {
            return false;
        }
    
        std::vector<unsigned char> vertex_shader_spirv;
        if( !GetBinaryFileContents( "Data/Shaders/11 Lighting/01 Rendering a geometry with vertex diffuse lighting/vert.spv", vertex_shader_spirv ) ) {
            return false;
        }
    
        VkDestroyer(VkShaderModule) vertex_shader_module;
        InitVkDestroyer( LogicalDevice, vertex_shader_module );
        if( !CreateShaderModule( LogicalDevice, vertex_shader_spirv, *vertex_shader_module ) ) {
            return false;
        }
    
        std::vector<unsigned char> fragment_shader_spirv;
        if( !GetBinaryFileContents( "Data/Shaders/11 Lighting/01 Rendering a geometry with vertex diffuse lighting/frag.spv", fragment_shader_spirv ) ) {
            return false;
        }
        VkDestroyer(VkShaderModule) fragment_shader_module;
        InitVkDestroyer( LogicalDevice, fragment_shader_module );
        if( !CreateShaderModule( LogicalDevice, fragment_shader_spirv, *fragment_shader_module ) ) {
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
            32,          // uint32_t                     stride
            VK_VERTEX_INPUT_RATE_VERTEX   // VkVertexInputRate            inputRate
            }
        };
    
        std::vector<VkVertexInputAttributeDescription> vertex_attribute_descriptions = {
            {
            0,                                                                        // uint32_t   location
            0,                                                                        // uint32_t   binding
            VK_FORMAT_R32G32B32_SFLOAT,                                               // VkFormat   format
            0                                                                         // uint32_t   offset
            },
            {
            1,                                                                        // uint32_t   location
            0,                                                                        // uint32_t   binding
            VK_FORMAT_R32G32B32_SFLOAT,                                               // VkFormat   format
            3 * sizeof(float)                                                                         // uint32_t   offset
            },
            {
            2,                                                                        // uint32_t   location
            0,                                                                        // uint32_t   binding
            VK_FORMAT_R32G32_SFLOAT,                                               // VkFormat   format
            6 * sizeof(float)                                                       // uint32_t   offset
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
        if( !CreateGraphicsPipelines( LogicalDevice, { pipeline_create_info }, VK_NULL_HANDLE, pipeline ) ) {
            return false;
        }
        InitVkDestroyer( LogicalDevice, Pipeline );
        *Pipeline = pipeline[0];
    
        return true;
        }

        bool UpdateStagingBuffer( bool force, VkDevice LogicalDevice, float ratio, float vertical_angle, float horizontal_angle) {
    
            UpdateUniformBuffer = true;
            
        
            Matrix4x4 rotationMatrix = PrepareRotationMatrix( vertical_angle, { 1.0f, 0.0f, 0.0f } ) * PrepareRotationMatrix( horizontal_angle, { 0.0f, -1.0f, 0.0f } );

            Matrix4x4 translationMatrix = PrepareTranslationMatrix(0.0f, 0.0f, -30.0f);

            Matrix4x4 model_view_matrix = translationMatrix * rotationMatrix;
    
            if( !MapUpdateAndUnmapHostVisibleMemory( LogicalDevice, *StagingBufferMemory, 0, sizeof( model_view_matrix[0] ) * model_view_matrix.size(), &model_view_matrix[0], true, nullptr ) ) {
            return false;
            }
    
            Matrix4x4 perspective_matrix = PreparePerspectiveProjectionMatrix( ratio, 90.0f, 1.0f, 100.0f );
    
            if( !MapUpdateAndUnmapHostVisibleMemory( LogicalDevice, *StagingBufferMemory, sizeof( model_view_matrix[0] ) * model_view_matrix.size(),
            sizeof( perspective_matrix[0] ) * perspective_matrix.size(), &perspective_matrix[0], true, nullptr ) ) {
            return false;
            }

            if( !MapUpdateAndUnmapHostVisibleMemory( LogicalDevice, *StagingBufferMemory, 2 * sizeof( model_view_matrix[0] ) * model_view_matrix.size(),
            sizeof( perspective_matrix[0] ) * perspective_matrix.size(), &rotationMatrix[0], true, nullptr ) ) {
            return false;
            }

            return true;
        }       
    };

#endif