import pyfiglet
from termcolor import colored


# ANSI escape codes for bold and color
BOLD = '\033[1m'
RED = '\033[91m'
RESET = '\033[0m'

# Generate ASCII art using pyfiglet
ascii_art = pyfiglet.figlet_format("perpass")

# Print the banner in bold red
print(BOLD + RED + ascii_art + RESET)
