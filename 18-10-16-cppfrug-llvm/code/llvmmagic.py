from IPython.core.magic import (register_line_magic, register_cell_magic,
                                register_line_cell_magic)

from IPython.core.display import display, HTML

from pygments import highlight
from pygments.lexers import LlvmLexer
from pygments.formatters import HtmlFormatter

import subprocess
import shlex
import codecs

@register_cell_magic
def llvmbc(line, cell):
    cell = codecs.encode(cell, "utf8")
    p = subprocess.Popen(["clang-7","-x","c","-S","-emit-llvm","-o","-","/dev/stdin"] + shlex.split(line),stdin=subprocess.PIPE,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
    ir = codecs.decode(p.communicate(cell)[0], "utf8")
    if p.returncode != 0:
        print(ir)
        return None
    css = HtmlFormatter().get_style_defs('.highlight')
    ir = highlight(ir, LlvmLexer(), HtmlFormatter())
    out = '''
    <style>
    %s
    </style>
    %s
    ''' % (css, ir)
    display(HTML(data=out))
