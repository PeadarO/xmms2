import Common, Object, Utils, Node, Params
import sys, os
import gzip
from misc import copyobj

def gzip_func(task):
    env = task.m_env
    infile = task.m_inputs[0].abspath(env)
    outfile = task.m_outputs[0].abspath(env)

    input = open(infile, 'r')
    output = gzip.GzipFile(outfile, mode='w')
    output.write(input.read())

    return 0

class manobj(copyobj):
    def __init__(self, section=1, type='none'):
        copyobj.__init__(self, type)
        self.fun = gzip_func
        self.files = []
        self.section = section

    def apply(self):
        for file in self.files:
            node = self.m_current_path.find_node(
                Utils.split_path(file) )
            if not node: fatal('cannot find input file %s for processing' % file)

            target = self.target
            if not target or len(lst)>1: target = node.m_name

            newnode = self.m_current_path.search_existing_node(Utils.split_path(file+'.gz'))
            if not newnode:
                newnode = Node.Node(file+'.gz', self.m_current_path)
                self.m_current_path.append_build(newnode)

            task = self.create_task('copy', self.env, 8)
            task.set_inputs(node)
            task.set_outputs(newnode)
            task.m_env = self.env
            task.fun = self.fun

            if Params.g_commands['install'] or Params.g_commands['uninstall']:
                Common.install_files('MANDIR', 'man' + str(self.section), newnode.abspath(self.env))

def setup(env):
    Object.register('man', manobj)

def detect(conf):
    return 1
