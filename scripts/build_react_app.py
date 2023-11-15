Import("env")
import os

def before_build_spiffs(source, target, env):
    print("Building plant-master-react...") 

env.AddPreAction("$BUILD_DIR/spiffs.bin", before_build_spiffs)