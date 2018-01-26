# Packages to install in order for the scraping to work

import pip

def install(package):
    pip.main(['install', package])

# Run script to install all the needed packages
if __name__ == '__main__':
    install('requests')
    install('pandas')
    install('git+https://github.com/seemethere/nba_py.git')