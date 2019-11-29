import os
import glob
from xml.sax.saxutils import escape
from jinja2 import Environment

save_path = os.path.join(os.path.dirname(__file__), "compro_library.xml")
template = '  <template name="{{ name }}" value="{{ code }}" discription="" toReformat="false" toShortenFQNames="true">\n    <context>\n      <option name="cpp" value="true" />\n    </context>\n  </template>\n\n'


def create():
    dics = []
    pathes = glob.glob("*/*.cpp")
    for load_path in pathes:
        with open(load_path, 'r') as f:
            name = os.path.splitext(load_path.split('/')[-1])[0]
            s = f.read()
            dics.append({"name": escape(name), "code": escape(s).replace('\n', '&#10;')})
    
    with open(save_path, 'w') as f:
        f.write('<templateSet group="compro_library">\n')
        for dic in dics:
            f.write(Environment().from_string(template).render(**dic))
        f.write('</templateSet>')


if __name__ == '__main__':
    create()
