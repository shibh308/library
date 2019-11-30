#!/usr/bin/python3
import os
import sys

def expand(origin_path, lines):
    out_lines = []
    for line in lines:
        if line.startswith('#include'):
            path = (line.split('"'))
            if len(path) == 1:
                path = line.split('<')[1].split('>')[0]
            else:
                path = path[-2]
            if path.endswith('.cpp'):
                path = os.path.join(os.path.dirname(origin_path), path)
                with open(path, 'r') as f:
                    out_lines += f.readlines()
                continue
        out_lines.append(line)

    write_path = os.path.join('expand', os.path.basename(origin_path))
    with open(write_path, 'w') as f:
        for line in out_lines:
            f.write(line)
    print('expand:  {}  =>  {}'.format(origin_path, write_path))


def run():
    assert len(sys.argv) >= 2, 'a number of arguments is not match'
    pathes = sys.argv[1:]
    for path in pathes:
        with open(path, 'r') as f:
            expand(path, f.readlines())


if __name__ == '__main__':
    run()
