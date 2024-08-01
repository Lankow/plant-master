Import("env") # type: ignore
import os
import shutil


def cleanDataFolder():    
    script_dir = os.getcwd()
    data_dir_path = os.path.join(script_dir, 'data')
    
    if not os.path.exists(data_dir_path):
        print(f'Rename: Creating an empty data directory {data_dir_path}')
        os.mkdir(data_dir_path)
    else:
        print(f'Rename: Deleting the old data directory {data_dir_path}')
        shutil.rmtree(data_dir_path)

program_args = env['PROGRAM_ARGS'] # type: ignore
if('runExtraScripts' in program_args):
    cleanDataFolder()