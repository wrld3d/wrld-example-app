import fileinput
import sys

filename = "ProjectSwallowApp.xcodeproj/project.pbxproj"

framework_guid = "3A8D81F31F8E629100325BF3"
embed_framework_guid = "3A8D81F41F8E629100325BF3"
link_phase_guid = "3A8D81F51F8E629100325BF3"
embed_phase_guid = "3A8D81F61F8E629100325BF3"

def find_framework_ref(filename, line_to_find):
	framework_ref = ""

	project_file = open(filename)

	for line in project_file:
		if line.find(line_to_find) != -1:
			framework_ref = line.split(" ")[0].strip("\t")

	project_file.close()

	return framework_ref

def replace_line_in_file(filename, line_to_find, line_to_add):
	project_file = fileinput.FileInput(filename, inplace=True)

	for line in project_file:
		if line.find(line_to_find) != -1:
			sys.stdout.write(line.replace(line_to_find, line_to_add))
		else:
			sys.stdout.write(line)

	project_file.close()

def add_framework_ref(framework_ref):
	line_to_find = "/* End PBXBuildFile section */\n"
	line_to_add = ("\t\t" + framework_guid + " /* StepInsideSdk.framework in Frameworks */ = {isa = PBXBuildFile; fileRef = " + framework_ref + " /* StepInsideSdk.framework */; };\n"
					"\t\t" + embed_framework_guid + " /* StepInsideSdk.framework in Embed Frameworks */ = {isa = PBXBuildFile; fileRef = " + framework_ref + " /* StepInsideSdk.framework */; settings = {ATTRIBUTES = (CodeSignOnCopy, RemoveHeadersOnCopy, ); }; };\n"
					"/* End PBXBuildFile section */\n")

	replace_line_in_file(filename, line_to_find, line_to_add)

def add_link_framework_build_phase():
	line_to_find = "/* End PBXFileReference section */\n"
	line_to_add = ("/* End PBXFileReference section */\n"
					"\n"
					"/* Begin PBXFrameworksBuildPhase section */\n"
					"\t\t" + link_phase_guid + " /* Frameworks */ = {\n"
					"\t\t\tisa = PBXFrameworksBuildPhase;\n"
					"\t\t\tbuildActionMask = 2147483647;\n"
					"\t\t\tfiles = (\n"
					"\t\t\t\t" + framework_guid + " /* StepInsideSdk.framework in Frameworks */,\n"
					"\t\t\t);\n"
					"\t\t\trunOnlyForDeploymentPostprocessing = 0;\n"
					"\t\t};\n"
					"/* End PBXFrameworksBuildPhase section */\n")

	replace_line_in_file(filename, line_to_find, line_to_add)

def add_embed_framework_build_phase():
	line_to_find = "/* End PBXContainerItemProxy section */\n"
	line_to_add = ("/* End PBXContainerItemProxy section */\n"
					"\n"
					"/* Begin PBXCopyFilesBuildPhase section */\n"
					"\t\t" + embed_phase_guid + " /* Embed Frameworks */ = {\n"
					"\t\t\tisa = PBXCopyFilesBuildPhase;\n"
					"\t\t\tbuildActionMask = 2147483647;\n"
					"\t\t\tdstPath = \"\";\n"
					"\t\t\tdstSubfolderSpec = 10;\n"
					"\t\t\tfiles = (\n"
					"\t\t\t\t" + embed_framework_guid + " /* StepInsideSdk.framework in Embed Frameworks */,\n"
					"\t\t\t);\n"
					"\t\t\tname = \"Embed Frameworks\";\n"
					"\t\t\trunOnlyForDeploymentPostprocessing = 0;\n"
					"\t\t};\n"
					"/* End PBXCopyFilesBuildPhase section */\n")

	replace_line_in_file(filename, line_to_find, line_to_add)

def add_framework_build_phases():
	project_file = fileinput.FileInput(filename, inplace=True, backup='.bak')

	pbx_native_target_section = False

	for line in project_file:
		found = False
		if line.find("/* Begin PBXNativeTarget section */\n") != -1:
			pbx_native_target_section = True

		if pbx_native_target_section and line.find("Sources */,\n") != -1:
			found = True

		sys.stdout.write(line)

		if found:
			sys.stdout.write("\t\t\t\t" + link_phase_guid + " /* Frameworks */,\n")
			sys.stdout.write("\t\t\t\t" + embed_phase_guid + " /* Embed Frameworks */,\n")

	project_file.close()

framework_ref = find_framework_ref(filename, "Include/SenionLab/StepInsideSdk.framework */,\n")
add_framework_ref(framework_ref)
add_link_framework_build_phase()
add_embed_framework_build_phase()
add_framework_build_phases()