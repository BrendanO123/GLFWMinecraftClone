#include <string.h>
#include <iostream>

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <stdexcept>
#include <cstdlib>

using namespace std;

const vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};
const bool enableValidationLayers = true;

class Application{
    public:
        GLFWwindow* window;
        int width = 640, height = 480;

        Application(){init();}
        int run(){
            int returnVal = mainLoop();
            if(returnVal){return returnVal;}
            return cleanUp();
        }

        bool checkValidationLayerSupport() {
            uint32_t layerCount;
            vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

            std::vector<VkLayerProperties> availableLayers(layerCount);
            vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());


            for(const char* layerName : validationLayers){
                bool layerFound = false;

                for(const VkLayerProperties& layerProperties : availableLayers){
                    if(strcmp(layerName, layerProperties.layerName) == 0){
                        layerFound = true; break;
                    }
                }
                if(!layerFound){return false;}
            }

            return true;
        }

    private:
        VkInstance instance;

        int init(){
            glfwInit();
            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
            glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

            if (!glfwVulkanSupported()){return EXIT_FAILURE;}

            window = glfwCreateWindow(width, height, "Vulkan Port", nullptr, nullptr);
            return createInstance();
        }
        int createInstance(){
            VkApplicationInfo appInfo{};
                appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
                appInfo.pApplicationName = "Hello Triangle";
                appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
                appInfo.pEngineName = "No Engine";
                appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
                appInfo.apiVersion = VK_API_VERSION_1_0;

            VkInstanceCreateInfo createInfo{};
                createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
                createInfo.pApplicationInfo = &appInfo;


            uint32_t extensionCount = 0;
                vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

            vector<VkExtensionProperties> extensions(extensionCount);
                vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());


            vector<const char*> totalRequiredExtensions;
            uint32_t requiredExtensionCount = 0;
            const char** requiredExtensions = 
                glfwGetRequiredInstanceExtensions(&requiredExtensionCount);

            for(uint32_t i = 0; i < requiredExtensionCount; i++) {
                totalRequiredExtensions.emplace_back(requiredExtensions[i]);
            }

            totalRequiredExtensions.emplace_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
            createInfo.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;

            if(totalRequiredExtensions.size() > extensionCount){
                printf("Extension Retrival Failed", stderr);
                return EXIT_FAILURE;
            }
            
            createInfo.enabledExtensionCount = static_cast<uint32_t>(totalRequiredExtensions.size());
            createInfo.ppEnabledExtensionNames = totalRequiredExtensions.data();

            if (enableValidationLayers && !checkValidationLayerSupport()) {
                printf("Validation Layers Requested, but not Available!", stdout);
                return EXIT_FAILURE;
            }

            VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
            if (enableValidationLayers) {
                createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
                createInfo.ppEnabledLayerNames = validationLayers.data();

                debugCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
                debugCreateInfo.messageSeverity = 
                    VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | 
                    VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | 
                    VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
                debugCreateInfo.messageType = 
                    VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | 
                    VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | 
                    VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;

                
            } else {
                createInfo.enabledLayerCount = 0;
                createInfo.pNext = nullptr;
            }

            //Finish up
            if(vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS){
                printf("Instance Creation Failed", stdout);
                return EXIT_FAILURE;
            }
            return EXIT_SUCCESS;
        }


        int mainLoop(){
            while(!glfwWindowShouldClose(window)){
                glfwPollEvents();
            }
            return EXIT_SUCCESS;
        }


        int cleanUp(){
            vkDestroyInstance(instance, nullptr);
            glfwDestroyWindow(window);
            glfwTerminate();
            return EXIT_SUCCESS;
        }
};

int main() {
    Application app = Application();
    int returnVal = app.run();
    if(returnVal){return returnVal;}
    return EXIT_SUCCESS;
}