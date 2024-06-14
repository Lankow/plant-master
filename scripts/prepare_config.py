Import("env")
import os
import shutil

def handle_config():
    print("Initializing configuration...")
    cpp_defines = env.ParseFlags(env['BUILD_FLAGS']).get("CPPDEFINES")
    version = get_version(cpp_defines)
    config_file_path = "config.json"

    if os.path.isfile(config_file_path):
        validate_config()
    else:
        print(f"{config_file_path} not found in parent directory.")
        generate_default_config()

    # Determine the config file name based on a specific define
    if "PLANT_MASTER" in cpp_defines:
        output_config_path = "config-master.json"
    else:
        output_config_path = "config-monitor.json"
    print("Config File: " + output_config_path)

    move_config()


def get_version(cpp_defines):
    version_value = None

    for item in cpp_defines:
        if isinstance(item, list) and item[0] == 'VERSION':
            version_value = item[1]
            print("Config Version: " + version_value)
            break

    print("Config Version not found.")
    return version_value


def generate_default_config():
    print("Generating default configuration...")


def validate_config():
    print("Validating configuration...")


def move_config(output_config_path):
    print("Moving configuration...")
    data_dir = os.path.join(os.getcwd(), "data")

    if not os.path.exists(data_dir):
        os.makedirs(data_dir)

    dest_path = os.path.join(data_dir, output_config_path)

    shutil.copy(config_file_path, dest_path)
    print(f"Modified {config_file_path} copied as {dest_path}")

print("---------------------")
handle_config()
print("---------------------")

