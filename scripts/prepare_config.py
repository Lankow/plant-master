import os

def verifyConfig(defines):
    print(defines)
    print("Verifying config file...")

def moveConfig():
    print("Moving config file...")

def createConfig():
    print("Creating config file...")

def setDefaultConfig():
    print("Setting default values for config file...")

build_flags = os.getenv('BUILD_FLAGS')
print(build_flags)