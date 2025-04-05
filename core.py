# Writing a prototype of the core language in python so I don't spend forever
# fiddling with C++ stuff
from collections import defaultdict
import sys
# builtin stuff: ( ),
# inject default ops: !, $, [, ], #, |, _


class Env:
    def __init__(self, parent=None):
        self.parent = parent
        self.bindings = defaultdict(None)

    def lookup(self, name):
        if name in self.bindings:
            return self.bindings[name]
        elif self.parent is not None:
            return self.parent.lookup(name)
        else:
            raise NameError(f"NameError: name '{name}' is not defined")

    def bind(self, name, value):
        self.bindings[name] = value

    def __str__(self):
        return f"Env({self.bindings})"


class L_Block:
    # A block has an environment, a list of expressions, a parameter, access to
    # the caller's continuation
    def __init__(self, env: Env, exprs, param, cont):
        self.env = env
        self.exprs = exprs
        self.param = param
        self.cont = cont


class BindingTrie:
    # Each node is either a character or an object with some set of properties to
    # be matched against. If a node is the last in a binding definition, it is a
    # terminal node. A node will have children (dict of other nodes) if it's not a
    # terminal node, or if another binding uses this path and keeps going.

    class Node:
        type Value = str | object

        def __init__(self, value: (Value | None) = None):
            self.value = value
            self.children = defaultdict(BindingTrie.Node)
            self.is_terminal = False

    def __init__(self):
        self.root: BindingTrie.Node | None = None

    def _get_key(self, value):
        if isinstance(value, str):
            return value

    def lookup(self, remaining_value: list):
        if name in self.bindings:
            return self.bindings[name]
        else:
            raise NameError(f"NameError: name '{name}' is not defined")

    def bind(self, value):
        pass

    def __str__(self):
        return f"BindingTrie({self.bindings})"


class Expr:
    def __init__(self, op, args):
        self.op = op
        self.args = args
        # TODO: validity of arity depends on the current environment upon definition
        self.arity = len(args)
        self.check_arity(op, self.arity)


def repl():
    pass


def main():

    pass


if __name__ == "__main__":
    main()
