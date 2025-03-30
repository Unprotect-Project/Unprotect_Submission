import os

os.execvp('echo', ['ARGV[0]', 'Hello, world!'])
