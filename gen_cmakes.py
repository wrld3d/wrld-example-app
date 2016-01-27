import os
import os.path
import fnmatch
import sys
import StringIO

class CMakeList:
    def __init__(self, base_path, full_path):
        self.__files = []
        self.__basepath = base_path
        self.__path = full_path
        self.__childpaths = []

    @property
    def path(self):
        return self.__path

    @property
    def source_group(self):
        potential_path = self.__path.replace("%s" % self.__basepath, "").replace("/", "\\\\")
        if not potential_path:
            return "/"
        else:
            return potential_path

    @property
    def filename(self):
        return os.path.join(self.path, "CMakeLists.txt")

    @property
    def is_gated(self):
        gates = ['IOS', 'ANDROID', 'OSX', 'WINDOWS']
        for g in gates:
            if g.lower() in self.__path.lower():
                return True
        return False

    @property
    def gate(self):
        gates = ['IOS', 'ANDROID', 'OSX', 'WINDOWS']
        for g in gates:
            if g.lower() in self.__path.lower():
                return g
        raise Exception("Not gated")

    def add_child(self, child):
        self.__childpaths.append(child)

    def add_file(self, file):
        self.__files.append(file)

    def dump(self):
        output = StringIO.StringIO()
        if self.is_gated:
            self.__start_gate(output)
        self.__contents(output)
        if self.is_gated:
            self.__end_gate(output)
        value = output.getvalue()
        output.close()
        return value

    def __start_gate(self, output):
        output.write("if(${%s})\n" % self.gate)

    def __end_gate(self, output):
        output.write("endif(${%s})\n" % self.gate)

    def __contents(self, output):
        output.write("set(headers ${headers} %s\n)\n" % (self.__path))
        output.write("set(currsources\n")
        for f in self.__files:
            output.write("  %s\n" % f)
        output.write(")\n")
        output.write("set(sources ${sources} ${currsources})\n")
        output.write("source_group(%s FILES ${currsources})\n" % self.source_group)

        for c in self.__childpaths:
            output.write("include(%s/CMakeLists.txt)\n" % c)

def produce_cmake_lists(path):
    cmakelists = []
    matches = ['*.cpp', '*.c', '*.cxx', '*.cc', '*.mm', '*.m', '*.h', '*.hpp', "CMakeLists.txt"]
    for root, dirs, files in os.walk(path, topdown=True):
        cmakelist = CMakeList(path, root)
        for name in files:
            for match in matches:
                if fnmatch.fnmatch(name, match):
                    cmakelist.add_file(os.path.join(root, name))
                    break
        for name in dirs:
            cmakelist.add_child(os.path.join(root, name))
        cmakelists.append(cmakelist)
    return cmakelists

def write_cmake_lists(lists):
    for list in lists:
        with open(list.filename, "w") as f:
            f.write(list.dump())

if __name__ == '__main__':
    cmakelists = produce_cmake_lists(sys.argv[1])
    write_cmake_lists(cmakelists)
