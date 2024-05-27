# build_script.py
import os
import shutil

def createClientApp():
    # delete existing folder
    script_dir = os.getcwd()
    data_dir_path = os.path.join(script_dir, 'data')
    
    if os.path.exists(data_dir_path):
        print('Rename: Deleting the old data directory ' + data_dir_path)
        shutil.rmtree(data_dir_path)
    print('Rename: Creating an empty data directory ' + data_dir_path)
    os.mkdir(data_dir_path)
    
    # Build the React web application
    react_proj_dir = "plant-master-client"
    os.chdir(react_proj_dir)
    print('\nReact build: Starting the build process for the Client App...\n')
    
    print('\nRunning `npm install`')
    if os.system("npm install") != 0:
        print(f"Error installing dependencies for Client App in ./{react_proj_dir}")
        return
    print('\nRunning `npm run build`')
    if os.system("npm run build") != 0:
        print(f"Error building Client App in ./{react_proj_dir}")
        return    
    os.chdir('..')

createClientApp()