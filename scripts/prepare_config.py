Import("env")

def initializeConfig():
    print("Initializing configuration...")
    cpp_defines = env.ParseFlags(env['BUILD_FLAGS']).get("CPPDEFINES")
    
    # Initialize version variable
    version_value = None

    # Loop through the list to find 'VERSION'
    for item in cpp_defines:
        if isinstance(item, list) and item[0] == 'VERSION':
            version_value = item[1]
            break

    print(version_value)  # Output should be '1.0'

    if("PLANT_MASTER" in cpp_defines):
        config_file_name = "config-master.json"
    else:
        config_file_name = "config-monitor.json"
    
    print("Chosen config file:" + config_file_name)





def createConfig():
    print("Creating config file...")

def setDefaultConfig():
    print("Setting default values for config file...")



initializeConfig()
