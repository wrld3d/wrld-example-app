from xml.dom.minidom import parse
import sys

def poke_version(filename, version_code, version_name):
       document_dom = parse(filename)
       manifest_tag = document_dom.getElementsByTagName("manifest")[0]
       manifest_tag.attributes["android:versionCode"].nodeValue = str(version_code)
       manifest_tag.attributes["android:versionName"].nodeValue = str(version_name)
       print document_dom.toxml()

if __name__ == '__main__':
       if len(sys.argv) is not 4:
           print "usage: poke_manifest.py <filename> <versionCode> <versionName>"
           sys.exit(-1)

       poke_version(sys.argv[1], sys.argv[2], sys.argv[3])
