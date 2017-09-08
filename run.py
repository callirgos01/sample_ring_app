#this file simply takes all the C files in the project
#builds them using gcc
#then links them together
#then tries to run the output program
#these are helper functions to make building the whole project less tedious in the command line
import os
import string
import shutil 

EXCLUDE_SOURCE_FILES = [ ]
EXCLUDE_LIBS = [ ] 
SOURCE_DIRS = [
    'source/functional/hal',
    'source/functional/lib',
    'source/functional/os',
    'source/config',
    'source/platform/testplatform/hal'
]

INCLUDE_DIRS = [
    'source/config',
    'source/functional',
    'source/platform/testplatform/soup',
    'source/platform/testplatform/soup/boost',
    'source/platform/testplatform',
]
def dir_entries(dir_name, *args):
    file_list = []
    for file in os.listdir(dir_name):
        dir_file = os.path.join(dir_name, file)
        if os.path.isfile(dir_file):
            if not args:
                file_list.append(string.replace(dir_file, "\\", "/"))
            else:
                if os.path.splitext(dir_file)[1][1:] in args:
                    file_list.append(string.replace(dir_file, "\\", "/"))
        elif os.path.isdir(dir_file):
            if len([match for match in EXCLUDE_LIBS if ("/" + match + "/") in string.replace(dir_file, "\\", "/")]) == 0:
                #print "Accessing directory:", dir_file
                file_list.extend(dir_entries(dir_file, *args))
    return file_list

source_files = []
for dir in SOURCE_DIRS:
    source_files += dir_entries(dir, 'c','cpp')

source_files = [f for f in source_files if f not in EXCLUDE_SOURCE_FILES and "/test_" not in f]

#clean up previous build
if os.path.exists('build'):
    shutil.rmtree('build') 

#create build folder
os.makedirs('build')
output_files = []
#build all available files
for source_file in source_files:
    output_file = "build/{0}".format(source_file.replace(".c",".o")).replace(".opp",".o")
    output_files.append(output_file)
    if not os.path.exists(os.path.dirname(output_file)):
        os.makedirs(os.path.dirname(output_file))
    #print "gcc -I source/platform/testplatform/ -c {0} -o {1}".format(source_file, output_file)
    gcc_command = "gcc"
    print os.path.splitext( source_file )[1]
    if os.path.splitext( source_file )[1] == ".cpp":
        gcc_command = 'g++'
    build_command =  "{gcc_command} -I {includes} -c {source_file} -o {output_file}".format(includes=" -I ".join(INCLUDE_DIRS), gcc_command=gcc_command,source_file=source_file, output_file=output_file)
    print build_command
    os.system(build_command)

#linker command. Join all the output files with spaces in between them, and link them into out program file
#print output_files
link_command = "gcc -I {includes} -o build/program {output_files}".format(includes=" -I ".join(INCLUDE_DIRS), output_files=" ".join(output_files))
print link_command
os.system( link_command )

os.system("./build/program")
