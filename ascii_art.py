import pyfiglet
from termcolor import colored

ascii_banner = pyfiglet.figlet_format("perpass")
print(colored(ascii_banner, 'green'))
