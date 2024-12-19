#include "VKApplication.h"

using namespace std;


int main() {
    Application app = Application();
    int returnVal = app.run();
    if(returnVal){return returnVal;}
    return EXIT_SUCCESS;
}



int Application :: init(){
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    if (!glfwVulkanSupported()){return EXIT_FAILURE;}

    window = glfwCreateWindow(width, height, "Vulkan Port", nullptr, nullptr);

    if(!createInstance()){return EXIT_FAILURE;}
    if(!pickPhysicalDevice()){return EXIT_FAILURE;}

    return EXIT_SUCCESS;
}

int Application :: createInstance(){
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
bool Application :: checkValidationLayerSupport() {
    uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    vector<VkLayerProperties> availableLayers(layerCount);
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

int Application :: pickPhysicalDevice(){
    uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

    if(deviceCount == 0){
        printf("Failed to Find GPUs with Vulkan Support!", stdout);
        return EXIT_FAILURE;
    }

    vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

    for(const VkPhysicalDevice device : devices){
        if(isDeviceSuitable(device)){
            physicalDevice = device; break;
        }
    }
    if(physicalDevice == VK_NULL_HANDLE){
        printf("Failed to Find a Suitable GPU!", stdout);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
bool Application :: isDeviceSuitable(VkPhysicalDevice device){
    //TODO
    VkPhysicalDeviceProperties deviceProperties;
        vkGetPhysicalDeviceProperties(device, &deviceProperties);
    VkPhysicalDeviceFeatures deviceFeatures;
        vkGetPhysicalDeviceFeatures(device, &deviceFeatures);
    
    return deviceFeatures.geometryShader;
}

QueueFamilyIndices Application :: findQueueFamilies(VkPhysicalDevice device){
    QueueFamilyIndices indicies;

    

    return indicies;
}



int Application :: mainLoop(){
    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();
    }
    return EXIT_SUCCESS;
}
