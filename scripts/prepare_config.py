Import("env")
import os
import shutil
import json

# Constants
CONFIG_NAME = "config.json"
CONFIG_NAME_MASTER = "config-master.json"
CONFIG_NAME_MONITOR = "config-monitor.json"

DHT_PIN = "dhtPin"
WATER_PUMP_PIN = "waterPumpPin"
READER_PINS = "readerPins"
VALVE_PINS = "valvePins"
THRESHOLDS = "thresholds"

MIN_PIN = 1
MAX_PIN = 34

MIN_THRESHOLD = 0
MAX_THRESHOLD = 4095

DEFAULT_THRESHOLD = 4095
DEFAULT_PINS = {
    DHT_PIN: 21,
    WATER_PUMP_PIN: 18,
    READER_PINS: [34],
    VALVE_PINS: [15]
}

PLANT_MASTER_FIELDS = [READER_PINS, VALVE_PINS, THRESHOLDS]
PLANT_MONITOR_FIELDS = [DHT_PIN, WATER_PUMP_PIN, READER_PINS, VALVE_PINS]

def handle_config():
    print("Initializing configuration...")
    cpp_defines = env.ParseFlags(env['BUILD_FLAGS']).get("CPPDEFINES")

    if os.path.isfile(CONFIG_NAME):
        validate_config(CONFIG_NAME)
    else:
        print(f"{CONFIG_NAME} not found.")
        generate_default_config()

    if "PLANT_MASTER" in cpp_defines:
        generate_output_config(CONFIG_NAME_MASTER, PLANT_MASTER_FIELDS, cpp_defines)
    else:
        generate_output_config(CONFIG_NAME_MONITOR, PLANT_MONITOR_FIELDS, cpp_defines)

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
    default_config = {key: value for key, value in DEFAULT_PINS.items()}
    default_config[THRESHOLDS] = [DEFAULT_THRESHOLD]
    with open(CONFIG_NAME, 'w') as file:
        json.dump(default_config, file, indent=4)

def generate_output_config(output_config_name, fields, cpp_defines):
    print(f"Generating {output_config_name}...")
    version = get_version(cpp_defines)
    with open(CONFIG_NAME, 'r') as file:
        config_data = json.load(file)

    output_data = {"version": version}
    for field in fields:
        if field in config_data:
            output_data[field] = config_data[field]

    move_config(output_config_name, output_data)

def validate_config(config_file_path):
    data = load_and_validate_json(config_file_path)
    if data:
        inspect_fields(data)
        with open(config_file_path, 'w') as file:
            json.dump(data, file, indent=4)
    else:
        remove_existing_config(config_file_path)
        generate_default_config()

def add_default_value(key):
    if key in DEFAULT_PINS:
        return DEFAULT_PINS[key]
    elif key == THRESHOLDS:
        return DEFAULT_THRESHOLD
    return None

def remove_existing_config(config_file_path):
    print("Removing existing configuration...")
    os.remove(config_file_path)

def move_config(output_config_path, data):
    print(f"Moving configuration to {output_config_path}...")
    data_dir = os.path.join(os.getcwd(), "data")

    if not os.path.exists(data_dir):
        os.makedirs(data_dir)

    dest_path = os.path.join(data_dir, output_config_path)

    with open(dest_path, 'w') as file:
        json.dump(data, file, indent=4)
    print(f"Modified {output_config_path} copied as {dest_path}")

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
        keys_to_delete = []
        for key, value in data.items():
            if key in DEFAULT_PINS:
                if isinstance(value, list):
                    for i, val in enumerate(value):
                        if isinstance(val, int) and MIN_PIN <= val <= MAX_PIN:
                            print(f"{key} is valid: {val}")
                        else:
                            print(f"{key} is not valid. Setting to default value: {DEFAULT_PINS[key]}")
                            value[i] = DEFAULT_PINS[key]
                elif isinstance(value, int) and MIN_PIN <= value <= MAX_PIN:
                    print(f"{key} has a valid pin number: {value}.")
                else:
                    print(f"{key} is not valid. Setting to default value: {DEFAULT_PINS[key]}")
                    data[key] = DEFAULT_PINS[key]
            elif key == THRESHOLDS:
                if isinstance(value, list):
                    for i, val in enumerate(value):
                        if MIN_THRESHOLD <= val <= MAX_THRESHOLD:
                            print("Threshold is fine")
                        else:
                            print(f"Threshold is not valid. Setting to default value: {DEFAULT_THRESHOLD}")
                            value[i] = DEFAULT_THRESHOLD
            else:
                print(f"{key} is not a valid field. Removing...")
                keys_to_delete.append(key)

        for key in keys_to_delete:
            del data[key]
    else:
        print("The JSON data is not an object (dictionary).")

print("---------------------")
handle_config()
print("---------------------")
