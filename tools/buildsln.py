import globals
import os , subprocess , sys

args = globals.ProcessArguments(sys.argv)
print(args)
CONFIG = globals.GetArgValue(args , "config" , "debug")

print("Building Machine Y in [{}] Configuration".format(CONFIG))
print("\n")

ret = 0

if globals.IsWindows():
    VS_BUILD_PATH = os.environ["VS_BUILD_PATH"][8:-1]
    VS_BUILD_PATH = "C:\\\\" + VS_BUILD_PATH
    ret = subprocess.call(["cmd.exe" , "/c" , VS_BUILD_PATH , "{}.sln".format(globals.MAIN_NAME) , "/property:Configuration={}".format(CONFIG)])

if globals.IsLinux():
    ret = subprocess.call(["make" , "config={}".format(CONFIG)])

if globals.IsMac():
    ret = subprocess.call(["make" , "config={}".format(CONFIG)])

sys.exit(ret)