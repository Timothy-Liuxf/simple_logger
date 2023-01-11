# This file is part of simple_logger.
# Copyright (c) 2023, Timothy Liu. All rights reserved.
# License    : MIT License
# Project URL: https://github.com/Timothy-Liuxf/simple_logger

import re
import os
import sys
import json
import platform
import subprocess

test_result_dir = 'test/test_results'

def assertTrue(cond: bool, msg: str='Test failed!'):
    if not cond:
        print(f'[ERROR] {msg}', file=sys.stderr)
        exit(1)

def isPlatformWindows() -> bool:
    return platform.system() == 'Windows'

def getExecutionPath(test_name: str) -> str:
    if isPlatformWindows():
        return f'examples\Release\{test_name}.exe'
    else:
        return f'examples/{test_name}'

def main():
    prev_dir = os.getcwd()
    result_files = [
        f'{test_result_dir}/{file}' for file in os.listdir(test_result_dir)]
    result_files = [file for file in result_files if os.path.isfile(file)]
    for result_file in result_files:
        test_name = os.path.splitext(os.path.basename(result_file))[0]
        print(f'Running test {test_name}...')
        os.chdir('build')
        result = subprocess.Popen(getExecutionPath(test_name),
                                  shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        result = result.stdout.read().decode(sys.stdout.encoding)
        os.chdir(prev_dir)
        result = result.splitlines(keepends=False)
        with open(result_file, 'r') as f:
            expected = json.load(f)
        assertTrue(len(result) == len(expected), f'{test_name} test failed: length not equal!')
        for i in range(len(result)):
            if expected[i]['level'] == 'none':
                expected_rgx = '^' + expected[i]['regex'] + '$'
            else:
                if expected[i]['level'] == 'trace':
                    prefix = '\033[34m'
                    postfix = '\033[0m'
                elif expected[i]['level'] == 'debug':
                    prefix = '\033[32m'
                    postfix = '\033[0m'
                elif expected[i]['level'] == 'info':
                    prefix = ''
                    postfix = ''
                elif expected[i]['level'] == 'warn':
                    prefix = '\033[33m'
                    postfix = '\033[0m'
                elif expected[i]['level'] == 'error':
                    prefix = '\033[31m'
                    postfix = '\033[0m'
                elif expected[i]['level'] == 'fatal':
                    prefix = '\033[31m'
                    postfix = '\033[0m'
                else:
                    assertTrue(False, f'{test_name} expected result incorrect!')

                expected_rgx = '^' + r'\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2} \[' + expected[i]['level'] + r'\] ' + expected[i]['regex'] + '$'
                
                if not isPlatformWindows():
                    assertTrue(result[i].startswith(prefix) and result[i].endswith(postfix), f'{test_name} test failed at line {i + 1}: color not correct!')
                    if len(postfix) != 0:
                        result[i] = result[i][len(prefix):-len(postfix)]

            assertTrue(re.match(expected_rgx, result[i]) != None, f'{test_name} test failed at line {i + 1}: expected: {expected_rgx}, result: {result[i]}!')
        print(f'Passed!')

if __name__ == '__main__':
    main()
