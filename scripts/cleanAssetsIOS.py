'''
Checks through source files for references to image files and identifies unused images.
It removes those images and updates the CMakeLists.txt.
'''


import os

def parseImageNamesInResources():
    ignorePrefixes = ["icon1","Icon1","IPAexGothic","FrankBold","yelp","DejaVuSansBold","opensans_semibold"]
    imageFiles = os.listdir("./Resources")
    imageNames = set()
    for fileName in imageFiles:
        if any(fileName.startswith(prefix) for prefix in ignorePrefixes):
            continue
        if fileName.endswith(".png"):
            fileName = fileName[:-4]
            fileName = fileName.split("@")[0]
            imageNames.add(fileName)
    return imageNames 


def searchImageNames(filePath):
    contents = open(filePath).read()
    found = set()
    for imageName in unfoundImages:
        if imageName in contents:
            found.add(imageName)
    for image in found:
        foundImages.add(image)
        unfoundImages.remove(image)


def moveImages(images):
    directory = "./Resources/UnusedImages"
    if not os.path.exists(directory):
        os.makedirs(directory)
    for imageName in images:
        suffixes = [".png", "@2x.png","@3x.png","@4x.png","@0.75x.png","@1.5x.png"]
        for suffix in suffixes:
            name = imageName + suffix
            
            fname = os.path.join("./Resources", name)
            if os.path.isfile(fname):
                removedImagenames.add(name)
                os.rename(fname, os.path.join(directory, name))


def searchAllSourceFiles(path):
    for root, subFolders, files in os.walk(path):
            for fileName in files:
                if fileName.endswith(".mm") or fileName.endswith(".m") or fileName.endswith(".cpp") or fileName.endswith(".json") or  fileName.endswith(".xib") or fileName.endswith(".storyboard"):
                    print(fileName)
                    searchImageNames(os.path.join(root, fileName))


def countLines(path):
    f = open(path,"r")
    lines = f.readlines()
    f.close()
    return len(lines)


def updateCMakeList():
    cmakelist = open("./Resources/CMakeLists.txt","r")
    lines = cmakelist.readlines()
    cmakelist.close()

    cmakelist = open("./Resources/CMakeLists.txt","w")
    removed = open("./Resources/UnusedImages/LinesRemovedFromCMakeLists.txt","w")
    
    for line in lines:
        if imageHasBeenRemoved(line):
            removed.write(line)
        else:
            cmakelist.write(line)

    cmakelist.close()
    removed.close()


def imageHasBeenRemoved(line):
    return  any(imageName in line for imageName in removedImagenames)


def main():

    os.chdir("../ios/")

    global unfoundImages
    global foundImages
    global removedImagenames

    unfoundImages = parseImageNamesInResources()
    foundImages = set()
    removedImagenames = set()

    print("---------------------------------------")

    searchAllSourceFiles("./ios_src/")
    searchAllSourceFiles("./Resources")
    searchAllSourceFiles("../src")

    print("---------------------------------------")

    print( "Total images: {}".format(len(unfoundImages)))
    print( "Total found: {}".format(len(foundImages)))
    print( "Total not found: {}".format(len(unfoundImages)))

    print("---------------------------------------")
    print("Unused Image Names:")
    for img in unfoundImages:
        print(img)

    print("---------------------------------------")
    moveImages(unfoundImages)
    print( "Total removed: {}".format(len(removedImagenames)))
    print("cmake lines before: {}".format(countLines("./Resources/CMakeLists.txt")))
    updateCMakeList()
    print("cmake lines after: {}".format(countLines("./Resources/CMakeLists.txt")))
    print("cmake lines removed: {}".format(countLines("./Resources/UnusedImages/LinesRemovedFromCMakeLists.txt")))
    
    
main()





        
        