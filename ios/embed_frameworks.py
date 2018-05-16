import fileinput
import sys


def embed_frameworks(projectName):
    project_file_name = projectName + '.xcodeproj/project.pbxproj'
    link_phase_guid = '52712FB4208DE9360088D080'
    embed_phase_guid = '52712FB5208DE9360088D080'
    path = 'ios/Include'
    frameworks = [
        {
            'name': 'WRLDSearchWidget.framework',
            'guid': '266A140D20A4544B0078E39E',
            'embed_guid': '266A140E20A454600078E39E',
            'path_in_project': 'Include/WrldSearchWidget/WRLDSearchWidget.framework'
        }
    ]

    for framework in frameworks:
        framework['reference'] = _find_framework_ref(
            project_file_name, framework['path_in_project'])
        _add_framework_ref(project_file_name, framework)

    _add_link_framework_build_phase(project_file_name, link_phase_guid, frameworks)
    _add_embed_framework_build_phase(project_file_name, embed_phase_guid, frameworks)
    _add_framework_build_phases(project_file_name, link_phase_guid, embed_phase_guid)


def _find_framework_ref(project_file_name, framework_location):
    line_to_find = '{} */,\n'.format(framework_location)
    with open(project_file_name, 'r') as project_file:
        for line in project_file:
            if line.find(line_to_find) != -1:
                return line.split(' ')[0].strip('\t')


def _replace_line_in_file(project_file_name, to_replace, replace_with):
    project_file = fileinput.FileInput(project_file_name, inplace=True)
    for line in project_file:
        if line.find(to_replace) != -1:
            sys.stdout.write(line.replace(to_replace, replace_with))
        else:
            sys.stdout.write(line)
    project_file.close()


def _add_framework_ref(project_file_name, framework):
    to_replace = '/* End PBXBuildFile section */\n'
    replace_with = ''.join(['\t\t{} /* {} in Frameworks */ = {}isa = PBXBuildFile; fileRef = {} /* {} */; {};\n'.format(framework['guid'], framework['name'], '{', framework['reference'], framework['name'], '}'),
                            '\t\t{} /* {} in Embed Frameworks */ = {}isa = PBXBuildFile; fileRef = {} /* {} */; settings = {}ATTRIBUTES = (CodeSignOnCopy, RemoveHeadersOnCopy, ); {}; {};\n'.format(framework['embed_guid'], framework['name'], '{', framework['reference'], framework['name'], '{', '}', '}'),
                            to_replace])

    _replace_line_in_file(project_file_name, to_replace, replace_with)


def _add_link_framework_build_phase(project_file_name, link_phase_guid, frameworks):
    to_replace = '/* End PBXFileReference section */\n'

    container_top = ''.join([to_replace,
                             '\n',
                             '/* Begin PBXFrameworksBuildPhase section */\n',
                             '\t\t{} /* Frameworks */ = {}\n'.format(link_phase_guid, '{'),
                             '\t\t\tisa = PBXFrameworksBuildPhase;\n',
                             '\t\t\tbuildActionMask = 2147483647;\n',
                             '\t\t\tfiles = (\n'])
    container_bottom = ''.join(['\t\t\t);\n',
                                '\t\t\trunOnlyForDeploymentPostprocessing = 0;\n',
                                '\t\t{};\n'.format('}'),
                                '/* End PBXFrameworksBuildPhase section */\n'])
    framework_links = []
    for framework in frameworks:
        framework_links.append('\t\t\t\t{} /* {} in Frameworks */,\n'.format(framework['guid'], framework['name']))
    replace_with = ''.join([container_top, ''.join(framework_links), container_bottom])

    _replace_line_in_file(project_file_name, to_replace, replace_with)


def _add_embed_framework_build_phase(project_file_name, embed_phase_guid, frameworks):
    to_replace = '/* End PBXContainerItemProxy section */\n'

    container_top = ''.join([to_replace,
                             '\n',
                             '/* Begin PBXCopyFilesBuildPhase section */\n',
                             '\t\t{} /* Embed Frameworks */ = {}\n'.format(embed_phase_guid, '{'),
                             '\t\t\tisa = PBXCopyFilesBuildPhase;\n',
                             '\t\t\tbuildActionMask = 2147483647;\n',
                             '\t\t\tdstPath = \'\';\n',
                             '\t\t\tdstSubfolderSpec = 10;\n',
                             '\t\t\tfiles = (\n'])
    container_bottom = ''.join(['\t\t\t);\n',
                                '\t\t\tname = \'Embed Frameworks\';\n',
                                '\t\t\trunOnlyForDeploymentPostprocessing = 0;\n',
                                '\t\t{};\n'.format('}'),
                                '/* End PBXCopyFilesBuildPhase section */\n'])
    framework_links = []
    for framework in frameworks:
        framework_links.append('\t\t\t\t{} /* {} in Embed Frameworks */,\n'.format(framework['embed_guid'], framework['name']))
    replace_with = ''.join([container_top, ''.join(
        framework_links), container_bottom])

    _replace_line_in_file(project_file_name, to_replace, replace_with)


def _add_framework_build_phases(project_file_name, link_phase_guid, embed_phase_guid):
    project_file = fileinput.FileInput(project_file_name, inplace=True, backup='.bak')
    pbx_native_target_section = False
    for line in project_file:
        found = False
        if line.find('/* Begin PBXNativeTarget section */\n') != -1:
            pbx_native_target_section = True
        if pbx_native_target_section and line.find('Sources */,\n') != -1:
            found = True
        sys.stdout.write(line)
        if found:
            sys.stdout.write('\t\t\t\t{} /* Frameworks */,\n'.format(link_phase_guid))
            sys.stdout.write('\t\t\t\t{} /* Embed Frameworks */,\n'.format(embed_phase_guid))
    project_file.close()


if __name__ == '__main__':
    if len(sys.argv) > 1:
        embed_frameworks(sys.argv[1])   # expecting an alternate Xcode project name, like PrivateExampleApp
    else:
        embed_frameworks('ExampleApp')
