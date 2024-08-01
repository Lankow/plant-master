Import("env") # type: ignore
import os
import shutil

def createClientApp():
    """
    This function deletes the existing 'data' directory, if it exists, and creates an empty 'data' directory.
    It then builds the React web application by navigating to the 'plant-master-client' directory,
    running 'npm install' to install dependencies, and 'npm run build' to build the client app.
    """
    # Delete existing 'data' folder
    script_dir = os.getcwd()
    data_dir_path = os.path.join(script_dir, 'data')
    
    if os.path.exists(data_dir_path):
        print(f'Rename: Deleting the old data directory {data_dir_path}')
        shutil.rmtree(data_dir_path)
    print(f'Rename: Creating an empty data directory {data_dir_path}')
    os.mkdir(data_dir_path)
    
    # Build the React web application
    react_proj_dir = "plant-master-client"
    os.chdir(react_proj_dir)
    print('\nReact build: Starting the build process for the Client App...\n')
    
    # Run 'npm install'
    print('\nRunning `npm install`')
    if os.system("npm install") != 0:
        print(f"Error installing dependencies for Client App in ./{react_proj_dir}")
        return
    
    # Run 'npm run build'
    print('\nRunning `npm run build`')
    if os.system("npm run build") != 0:
        print(f"Error building Client App in ./{react_proj_dir}")
        return
    
    # Change back to the original directory
    os.chdir('..')

program_args = env['PROGRAM_ARGS'] # type: ignore
if('runExtraScripts' in program_args):
    createClientApp()
