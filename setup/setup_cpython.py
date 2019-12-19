import os
import sys


template = """<?xml version="1.0" encoding="utf-8"?>
<Project ToolsVersion="4.0" xmlns="http://schemas.microsoft.com/developer/msbuild/2003">
  <ImportGroup Label="PropertySheets" />
  <PropertyGroup Label="UserMacros">
    <CPythonPath>{cpython_path}</CPythonPath>
  </PropertyGroup>
  <PropertyGroup />
  <ItemDefinitionGroup />
  <ItemGroup>
    <BuildMacro Include="CPythonPath">
      <Value>$(CPythonPath)</Value>
    </BuildMacro>
  </ItemGroup>
</Project>
"""


target_path = os.path.join(os.path.dirname(__file__), '..', 'kNN_NBC', 'pynbc', 'cpython.props')


def setup_cpython():
    print('Writing CPython path...')

    cpython_path = os.path.dirname(sys.executable)
    with open(target_path, 'w') as file:
        file.write(template.format(cpython_path=cpython_path))

    print('Done')


if __name__ == '__main__':
    setup_cpython()
