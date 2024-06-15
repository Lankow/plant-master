Import("env")
import os
import shutil
import json

# Constants
DHT_PIN = "dhtPin"
WATER_PUMP_PIN = "waterPumpPin"
READER_PIN = "readerPin"
VALVE_PIN = "valvePin"
PIN_NAMES = [DHT_PIN, WATER_PUMP_PIN, READER_PIN, VALVE_PIN]

DEFAULT_PINS = {
    DHT_PIN: 21,
    WATER_PUMP_PIN: 18,
    READER_PIN: 34
}

MIN_PIN = 1
MAX_PIN = 34

def handle_config():
    print("Initializing configuration...")
    cpp_defines = env.ParseFlags(env['BUILD_FLAGS']).get("CPPDEFINES")
    config_file_path = "config.json"

    if os.path.isfile(config_file_path):
        validate_config(config_file_path)
    else:
        print(f"{config_file_path} not found in parent directory.")
        generate_default_config()

    generate_output_config(cpp_defines)
    # move_config()

def get_version(cpp_defines):
    version_value = None

    for item in cpp_defines:
        if isinstance(item, list) and item[0] == 'VERSION':
            version_value = item[1]
            print("Config Version: " + version_value)
            break

    if version_value is None:
        print("Config Version not found.")
    return version_value

def generate_default_config():
    print("Generating default configuration...")

def generate_output_config(cpp_defines):
    print("Generating output configuration...")
    version = get_version(cpp_defines)

    if "PLANT_MASTER" in cpp_defines:
        output_config_path = "config-master.json"
    else:
        output_config_path = "config-monitor.json"

def validate_config(config_file_path):
    data = load_and_validate_json(config_file_path)
    if data:
        inspect_fields(data)
    else:
        remove_existing_config(config_file_path)
        generate_default_config()

def add_default_value(value):
    if value == "humidityPins":
        print("Humidity Pins")
    elif value == "dhtPin":
        print("DHT Pin")
    elif value == "waterPumpPin":
        print("Water Pump Pin")

def remove_existing_config():
    print("Removing existing configuration...")

def move_config(config_file_path, output_config_path):
    print("Moving configuration...")
    data_dir = os.path.join(os.getcwd(), "data")

    if not os.path.exists(data_dir):
        os.makedirs(data_dir)

    dest_path = os.path.join(data_dir, output_config_path)

    shutil.copy(config_file_path, dest_path)
    print(f"Modified {config_file_path} copied as {dest_path}")

def load_and_validate_json(file_path):
    try:
        with open(file_path, 'r') as file:
            data = json.load(file)
        print("The JSON file is valid.")
        return data
    except json.JSONDecodeError as e:
        print(f"Invalid JSON file: {e}")
        return None
    except Exception as e:
        print(f"An error occurred: {e}")
        return None

def inspect_fields(data):
    if isinstance(data, dict):
        for key, value in data.items():
            if isinstance(value, dict):
                print(f"Nested object found at key: {key}")
                inspect_fields(value)  # Recursive call for nested objects
            else:
                inspect_field(data, key, value)
                print(f"Field: {key}, Value: {value}, Type: {type(value)}")
    else:
        print("The JSON data is not an object (dictionary).")

def inspect_field(data, key, value):
    if key in PIN_NAMES:
        if isinstance(value, int) and MIN_PIN <= value <= MAX_PIN:
            print(f"{key} has a valid pin number: {value}.")
        else:
            default_pin = DEFAULT_PINS.get(key, None)
            if default_pin is not None:
                print(f"{key} must be a number between {MIN_PIN} and {MAX_PIN}. Setting to default value {default_pin}.")
                data[key] = default_pin
            else:
                print(f"No default value available for {key}.")
    else:
        print(f"Field {key} is not a recognized pin.")

print("---------------------")
handle_config()
print("---------------------")